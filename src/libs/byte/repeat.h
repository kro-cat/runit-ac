#ifndef REPEAT_H
#define REPEAT_H

// This is some unholy use of macros.

#define REPEAT(num,op) \
#if num>0              \
REPEAT(num-1,op)       \
op                     \
#endif

#endif
