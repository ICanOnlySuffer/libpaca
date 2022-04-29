# include "../inc/menu.h"

nil menu_log (menu_t * menu, str string) {
	PUT_ARR ("\e[35m<menu::", menu -> name, ">", string, "\e[0m\n");
}

nil menu_activate (menu_t * menu) {
	if (menu -> constructor) {
		menu -> constructor (menu);
		menu -> constructor = NIL;
	}
	menu_log (menu, "activating...");
	menu -> activate ();
	menu_log (menu, "activated");
}

nil menu_deactivate (menu_t * menu) {
	menu_log (menu, "deactivating...");
	menu -> deactivate ();
	menu_log (menu, "deactivated");
}

nil menu_clear (menu_t * menu) {
	for (u16 i = menu -> drawables.size; i; ) {
		drawable_free (menu -> drawables.items [--i]);
	}
}

