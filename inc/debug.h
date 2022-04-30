
# ifndef PGE_DEBUG_H
# define PGE_DEBUG_H

# include <pul/put.h>
# include <pul/vec.h>

extern vec log_mods;
extern u08 debug;

extern nil put_spaces ();
extern nil log_init (str strings);
extern nil log_out (u08 n_strings, str strings []);
extern nil log_err (u08 n_strings, str strings []);
extern nil log_quit ();

# define LOG(...) \
	log_out ( \
		sizeof ((str []) {__VA_ARGS__}) / sizeof (str), \
		(str []) {__VA_ARGS__} \
	)

# define LOG_ERR(...) \
	log_err ( \
		sizeof ((str []) {__VA_ARGS__}) / sizeof (str), \
		(str []) {__VA_ARGS__} \
	)

# endif // PGE_DEBUG_H

