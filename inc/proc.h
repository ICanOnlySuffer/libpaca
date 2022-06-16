
# ifndef LIBPACA_PROC_H
# define LIBPACA_PROC_H
# include <pocha/cor.h>

typedef struct {
	str name;
	u08 (*proc) ();
} proc_t;

# endif // LIBPACA_PROC_H

