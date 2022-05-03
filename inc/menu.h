
# ifndef PGE_MENU_H
# define PGE_MENU_H
# include "log.h"

typedef struct {
	str name;
	nil (* activate) ();
	nil (* deactivate) ();
} menu_t;

extern nil menu_activate (menu_t * menu);
extern nil menu_deactivate (menu_t * menu);
stainl nil menu_log (menu_t * menu, str string) {
	LOG ("\e[35m<%s> %s", menu -> name, string);
}

# endif // PGE_MENU_H

