# include "../inc/menu.h"
# include "../inc/log.h"
# include <pocha/str.h>

static chr buffer [64];

nil menu_activate (menu_t * menu) {
	STR_COPY (buffer, menu -> name, ".activate");
	menu -> activated = true;
	proc_t proc = {buffer, menu -> activate};
	log_proc (&proc);
}

nil menu_deactivate (menu_t * menu) {
	if (menu -> activated) {
		STR_COPY (buffer, menu -> name, ".deactivate");
		menu -> activated = false;
		proc_t proc = {buffer, menu -> deactivate};
		log_proc (&proc);
	}
}

