# include "../inc/menu.h"
# include <pul/str.h>

static chr buffer [32];

nil menu_activate (menu_t * menu) {
	STR_CPY (buffer, menu -> name, ".activate");
	menu -> activated = true;
	proc_init (buffer);
	menu -> activate ();
	proc_quit (buffer);
}

nil menu_deactivate (menu_t * menu) {
	if (menu -> activated) {
		STR_CPY (buffer, menu -> name, ".deactivate");
		menu -> activated = false;
		proc_init (buffer);
		menu -> deactivate ();
		proc_quit (buffer);
	}
}

