# include "../inc/menu.h"

nil menu_log (menu_t * menu, str string) {
	put_spaces ();
	PUT ("\e[35m<", menu -> name, "> ", string, "\e[0m\n");
}

nil menu_activate (menu_t * menu) {
	menu -> activate ();
}

nil menu_deactivate (menu_t * menu) {
	menu -> deactivate ();
}

