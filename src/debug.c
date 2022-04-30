# include "../inc/debug.h"

static chr spaces [] = "                                ";
static u08 n_spaces = 0;
vec log_mods = {.items = NIL};
u08 debug = true;

nil put_spaces () {
	spaces [n_spaces * 2] = 0;
	put (spaces);
	spaces [n_spaces * 2] = ' ';
}

nil log_init (str string) {
	if (debug) {
		if (not log_mods.items) {
			log_mods = VEC (4);
		}
		put_spaces ();
		PUT ("\e[33m", string, " {\e[0m\n");
		vec_psh (&log_mods, string);
		++n_spaces;
	}
}

nil log_out (u08 n_strings, str strings []) {
	if (debug) {
		put_spaces ();
		put ("\e[36m");
		fil_put_arr (STD_OUT, n_strings, strings);
		put ("\e[0m\n");
	}
}

nil log_err (u08 n_strings, str strings []) {
	if (debug) {
		put_spaces ();
		put_err ("\e[31m");
		fil_put_arr (STD_ERR, n_strings, strings);
		put_err ("\e[0m\n");
	}
}

nil log_quit () {
	if (debug) {
		--n_spaces;
		put_spaces ();
		PUT ("\e[33m} ", vec_pop (&log_mods), "\e[0m\n");
	}
}


