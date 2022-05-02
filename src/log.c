# include "../inc/log.h"

chr LOG_SPACES [] = "\0                               ";
static u08 n_spaces = 0;
static vec PROC_NAMES;

static nil inc_spaces () {
	LOG_SPACES [n_spaces * 2] = ' ';
	LOG_SPACES [++n_spaces * 2] = 0;
}

static nil dec_spaces () {
	LOG_SPACES [n_spaces * 2] = ' ';
	LOG_SPACES [--n_spaces * 2] = 0;
}

nil proc_init (str name) {
	vec_psh (&PROC_NAMES, name);
	PUT (LOG_SPACES, "\e[33m", name, " {\e[0m\n");
	inc_spaces ();
}

nil proc_quit () {
	dec_spaces ();
	PUT (LOG_SPACES, "\e[33m} ", vec_pop (&PROC_NAMES), "\e[0m\n");
}

nil log_init () {
	put ("Log.init {\n");
	put ("  PROC_NAMES = Vector.new 4\n");
	PROC_NAMES = VEC (4);
	put ("} Log.init\n");
}

nil log_quit () {
	put ("Log.quit {\n");
	put ("  PROC_NAMES.items.free\n");
	free (PROC_NAMES.items);
	put ("} Log.quit\n");
}

