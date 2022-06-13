# include "../inc/log.h"
# include <pul/put.h>

static chr SPACES [] = "\0                               ";
static u08 n_spaces = 0;

# ifdef __linux__
# define ERR_STR "\033[31m"
# define PRC_STR "\033[36m"
# define END_STR "\033[0m"
# else
# define ERR_STR "err: "
# define PRC_STR ""
# define END_STR ""
# endif

nil log_format (u08 error, str format, u64 pointers []) {
	chr buffer [128];
	str_frm_fmt (buffer, format, pointers);
	PUT (SPACES, error ? ERR_STR : "", buffer, END_STR "\n");
}

u08 log_proc (proc_t * proc) {
	PUT (SPACES, PRC_STR, proc -> name, " {" END_STR "\n");
	SPACES [n_spaces * 2] = ' ';
	SPACES [++n_spaces * 2] = 0;
	
	u08 output = ((u08 (*) ()) proc -> proc) ();
	
	SPACES [n_spaces * 2] = ' ';
	SPACES [--n_spaces * 2] = 0;
	PUT (SPACES, PRC_STR "} ", proc -> name, END_STR "\n");
	
	ret output;
}

