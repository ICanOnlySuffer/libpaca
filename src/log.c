# include "../inc/vectors.h"
# include "../inc/log.h"
# include <pul/put.h>
# include <pul/vec.h>

chr LOG_SPACES [] = "\0                               ";
static u08 n_spaces = 0;

static nil inc_spaces () {
	LOG_SPACES [n_spaces * 2] = ' ';
	LOG_SPACES [++n_spaces * 2] = 0;
}

static nil dec_spaces () {
	LOG_SPACES [n_spaces * 2] = ' ';
	LOG_SPACES [--n_spaces * 2] = 0;
}

# ifdef __linux__
# define ERR_STR "\e[31m"
# define LOG_STR "\e[1;36m"
# define PRC_STR "\e[36m"
# define END_STR "\e[0m"
# else
# define ERR_STR "err: "
# define LOG_STR "log: "
# define PRC_STR ""
# define END_STR ""
# endif

nil log_format (u08 error, str format, u64 pointers []) {
	chr buffer [128];
	str_frm_fmt (buffer, format, pointers);
	PUT (LOG_SPACES, error ? ERR_STR : LOG_STR, buffer, END_STR "\n");
}

nil proc_init (str name) {
	PUT (LOG_SPACES, PRC_STR, name, " {" END_STR "\n");
	inc_spaces ();
}

nil proc_quit (str name) {
	dec_spaces ();
	PUT (LOG_SPACES, PRC_STR "} ", name, END_STR "\n");
}

