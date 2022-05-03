# include "../inc/menu.h"

nil menu_activate (menu_t * menu) {
	chr buffer [32];
	STR_CPY (buffer, menu -> name, ".activate");
	proc_init (buffer);
	menu -> activate ();
	proc_quit (buffer);
}

nil menu_deactivate (menu_t * menu) {
	chr buffer [32];
	STR_CPY (buffer, menu -> name, ".deactivate");
	proc_init (buffer);
	menu -> deactivate ();
	proc_quit (buffer);
}

