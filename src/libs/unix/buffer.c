#include <unistd.h>
#include <errno.h>

#include <libs/byte/str.h>
#include <libs/byte/byte.h>

#include "buffer.h"


#define BUFFER_INIT(op,fd,buf,len) { (buf), 0, (len), (fd), (op) }
#define BUFFER_INSIZE 8192
#define BUFFER_OUTSIZE 8192

typedef int (*read_op)(int, char *, unsigned int);
typedef int (*write_op)(int, const char *, unsigned int);

void buffer_init(buffer *s, null_op op, int fd, char *buf, unsigned int len)
{
	s->x = buf;
	s->fd = fd;
	s->op = op;
	s->p = 0;
	s->n = len;
}

static int oneread(null_op op, int fd, char *buf, unsigned int len)
{
	int r;

	for (;;) {
		r = ((read_op)op)(fd, buf, len);
		if ((r == -1) && (errno == EINTR))
			continue;
		return r;
	}
}

static int getthis(buffer *s, char *buf, unsigned int len)
{
	if (len > s->p)
		len = s->p;

	s->p -= len;
	byte_copy(buf, len, s->x + s->n);
	s->n += len;

	return len;
}

int buffer_feed(buffer *s)
{
	int r;

	if (s->p)
		return s->p;

	r = oneread(s->op, s->fd, s->x, s->n);

	if (r <= 0)
		return r;

	s->p = r;
	s->n -= r;

	if (s->n > 0)
		byte_copyr(s->x + s->n, r, s->x);

	return r;
}

int buffer_bget(buffer *s, char *buf, unsigned int len)
{
	int r;

	if (s->p > 0)
		return getthis(s, buf, len);

	if (s->n <= len)
		return oneread(s->op, s->fd, buf, s->n);

	r = buffer_feed(s);
	if (r <= 0)
		return r;

	return getthis(s, buf, len);
}

int buffer_get(buffer *s, char *buf, unsigned int len)
{
	int r;

	if (s->p > 0) return
		getthis(s, buf, len);

	if (s->n <= len)
		return oneread(s->op, s->fd, buf, len);

	r = buffer_feed(s);
	if (r <= 0)
		return r;

	return getthis(s, buf, len);
}

char *buffer_peek(buffer *s)
{
	return s->x + s->n;
}

void buffer_seek(buffer *s, unsigned int len)
{
	s->n += len;
	s->p -= len;
}

static int allwrite(null_op op, int fd, const char *buf, unsigned int len)
{
	int w;

	while (len) {
		w = ((write_op)op)(fd, buf, len);
		if (w == -1) {
			if (errno == EINTR)
				continue;
			/* note that some data may have been written */
			return -1;
		}
		if (w == 0) {} /* luser's fault */
		buf += w;
		len -= w;
	}

	return 0;
}

int buffer_flush(buffer *s)
{
	int p = s->p;
	if (!p)
		return 0;

	s->p = 0;

	return allwrite(s->op, s->fd, s->x, p);
}

int buffer_putalign(buffer *s, char const *buf, unsigned int len)
{
	unsigned int n;

	while (len > (n = s->n - s->p)) {
		byte_copy(s->x + s->p, n, buf);
		s->p += n;
		buf += n;
		len -= n;
		if (buffer_flush(s) == -1)
			return -1;
	}

	/* now len <= s->n - s->p */
	byte_copy(s->x + s->p, len, buf);
	s->p += len;

	return 0;
}

int buffer_put(buffer *s, const char *buf, unsigned int len)
{
	unsigned int n = s->n;

	if (len > n - s->p) {
		if (buffer_flush(s) == -1)
			return -1;

		/* now s->p == 0 */
		if (n < BUFFER_OUTSIZE)
			n = BUFFER_OUTSIZE;

		while (len > s->n) {
			if (n > len)
				n = len;

			if (allwrite(s->op, s->fd, buf, n) == -1)
				return -1;

			buf += n;
			len -= n;
		}
	}

	/* now len <= s->n - s->p */
	byte_copy(s->x + s->p, len, buf);
	s->p += len;

	return 0;
}

int buffer_putflush(buffer *s, const char *buf, unsigned int len)
{
	if (buffer_flush(s) == -1)
		return -1;

	return allwrite(s->op, s->fd, buf, len);
}

int buffer_putsalign(buffer *s, const char *buf)
{
	return buffer_putalign(s, buf, str_len(buf));
}

int buffer_puts(buffer *s, const char *buf)
{
	return buffer_put(s, buf, str_len(buf));
}

int buffer_putsflush(buffer *s, const char *buf)
{
	return buffer_putflush(s, buf, str_len(buf));
}

int buffer_unixread(int fd, char *buf, unsigned int len)
{
	return read(fd, buf, len);
}

int buffer_unixwrite(int fd, const char *buf, unsigned int len)
{
	return write(fd, buf, len);
}

int buffer_0_read(int fd, char *buf, int len)
{
	if (buffer_flush(buffer_1) == -1)
		return -1;

	return buffer_unixread(fd,buf,len);
}

char buffer_0_space[BUFFER_INSIZE];

static buffer it_0 = BUFFER_INIT(
	(int (*)(void))buffer_0_read,
	0, buffer_0_space, sizeof buffer_0_space);

buffer *buffer_0 = &it_0;

char buffer_1_space[BUFFER_OUTSIZE];

static buffer it_1 = BUFFER_INIT(
	(int (*)(void))buffer_unixwrite,
	1, buffer_1_space, sizeof buffer_1_space);

buffer *buffer_1 = &it_1;

char buffer_2_space[256];

static buffer it_2 = BUFFER_INIT(
	(int (*)(void))buffer_unixwrite,
	2, buffer_2_space, sizeof buffer_2_space);

buffer *buffer_2 = &it_2;
