
# ifndef PGE_LOG_H
# define PGE_LOG_H
# include <pul/cor.h>

ext chr LOG_SPACES [];
ext nil log_format (u08 error, str format, u64 pointers []);
ext nil proc_init (str name);
ext nil proc_quit (str name);

# define LOG(format_, ...) \
	log_format (false, format_, (u64 []) {__VA_ARGS__})

# define LOG_ERR(format_, ...) \
	log_format (true, format_, (u64 []) {__VA_ARGS__})

# endif // PGE_LOG_H

