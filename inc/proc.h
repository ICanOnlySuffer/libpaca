
# ifndef PGE_PROC_H
# define PGE_PROC_H
# include <pul/cor.h>

typedef struct {
	u08 (*proc) ();
	str name;
} proc_t;

# define PROC(name_, proc_) {(u08 (*) ()) proc_, name_}

# endif // PGE_PROC_H

