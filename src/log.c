# include "../inc/log.h"

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

nil log_format (u08 error, str format, ptr pointers []) {
	chr buffer [64];
	str_frm_fmt (buffer, format, pointers);
	PUT (LOG_SPACES, error ? "\e[31m" : "\e[36m", buffer, "\e[0m\n");
}

nil proc_init (str name) {
	PUT (LOG_SPACES, "\e[33m", name, " {\e[0m\n");
	inc_spaces ();
}

nil proc_quit (str name) {
	dec_spaces ();
	PUT (LOG_SPACES, "\e[33m} ", name, "\e[0m\n");
}

