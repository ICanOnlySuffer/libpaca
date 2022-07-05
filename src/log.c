# include "../inc/log.h"
# include <pocha/ioe.h>
# include <stdarg.h>

prv chr SPACES [] = "\0                               ";
prv u08 n_spaces = 0;
prv chr BUFFER [128];

# ifdef __linux__
# define ERR_STR "\033[31m"
# define PRC_STR "\033[36m"
# define END_STR "\033[0m"
# else
# define ERR_STR "err: "
# define PRC_STR ""
# define END_STR ""
# endif

nil log_format (u08 error, str format, ...) {
	va_list values;
	va_start (values, format);
	
	str_format_va (BUFFER, format, values);
	PUT (SPACES, error ? ERR_STR : "", BUFFER, END_STR "\n");
	
	va_end (values);
}

u08 log_proc (proc_t * proc) {
	u08 output;
	
	PUT (SPACES, PRC_STR, proc -> name, " {" END_STR "\n");
	SPACES [n_spaces * 2] = ' ';
	SPACES [++n_spaces * 2] = 0;
	
	output = ((u08 (*) ()) proc -> proc) ();
	
	SPACES [n_spaces * 2] = ' ';
	SPACES [--n_spaces * 2] = 0;
	PUT (SPACES, PRC_STR "} ", proc -> name, END_STR "\n");
	
	ret output;
}

