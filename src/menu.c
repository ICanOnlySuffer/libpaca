# include "../inc/menu.h"
# include "../inc/log.h"
# include <pul/str.h>

static chr buffer [64];

nil menu_activate (menu_t * menu) {
	STR_CPY (buffer, menu -> name, ".activate");
	menu -> activated = true;
	proc_t proc = PROC (buffer, menu -> activate);
	log_proc (&proc);
}

nil menu_deactivate (menu_t * menu) {
	if (menu -> activated) {
		STR_CPY (buffer, menu -> name, ".deactivate");
		menu -> activated = false;
		proc_t proc = PROC (buffer, menu -> deactivate);
		log_proc (&proc);
	}
}

