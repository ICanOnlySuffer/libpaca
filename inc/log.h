
# ifndef PGE_LOG_H
# define PGE_LOG_H

# include <pul/put.h>
# include <pul/vec.h>
# include "vectors.h"

extern chr LOG_SPACES [];
extern nil log_format (u08 error, str format, ptr pointers []);
extern nil proc_init (str name);
extern nil proc_quit (str name);

# define LOG(format_, ...) \
	log_format (false, format_, (ptr []) {__VA_ARGS__})

# define LOG_ERR(format_, ...) \
	log_format (true, format_, (ptr []) {__VA_ARGS__})

# endif // PGE_LOG_H

