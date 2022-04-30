
# ifndef PGE_MENU_H
# define PGE_MENU_H
# include "debug.h"
# include <pul/put.h>

typedef struct {
	str name;
	nil (* activate) ();
	nil (* deactivate) ();
} menu_t;

extern nil menu_log (menu_t * menu, str string);
extern nil menu_activate (menu_t * menu);
extern nil menu_deactivate (menu_t * menu);

# endif // PGE_MENU_H

