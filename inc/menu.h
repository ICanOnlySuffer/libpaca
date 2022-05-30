
# ifndef PGE_MENU_H
# define PGE_MENU_H
# include "log.h"

typedef struct {
	str name;
	nil (* activate) ();
	nil (* deactivate) ();
	u08 activated;
} menu_t;

ext nil menu_activate (menu_t * menu);
ext nil menu_deactivate (menu_t * menu);
inl nil menu_log (menu_t * menu, str string) {
	LOG ("\033[35m<%s> %s", (u64) menu -> name, (u64) string);
}

# endif // PGE_MENU_H

