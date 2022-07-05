
# ifndef LIBPACA_LOG_H
# define LIBPACA_LOG_H
# include <pocha/cor.h>
# include "proc.h"

ext chr LOG_SPACES [];
ext nil log_format (u08 error, str format, ...);
ext u08 log_proc (proc_t * proc);

# define LOG(...) \
	log_format (false, __VA_ARGS__)

# define ERR(...) \
	log_format (true, __VA_ARGS__)

# endif // LIBPACA_LOG_H

