
# ifndef PGE_LOG_H
# define PGE_LOG_H

# include <pul/put.h>
# include <pul/vec.h>
# include "vectors.h"

extern chr LOG_SPACES [];
extern nil log_init ();
extern nil log_quit ();
extern nil proc_init (str name);
extern nil proc_quit ();

# define LOG(...) \
	PUT (LOG_SPACES, "\e[36m", __VA_ARGS__, "\e[0m\n")

# define LOG_ERR(...) \
	PUT_ERR (LOG_SPACES, "\e[31m", __VA_ARGS__, "\e[0m\n")

# endif // PGE_LOG_H

