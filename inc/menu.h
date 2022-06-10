
# ifndef PGE_MENU_H
# define PGE_MENU_H
# include <pul/cor.h>

typedef struct {
	str name;
	nil (* activate) ();
	nil (* deactivate) ();
	u08 activated;
} menu_t;

ext nil menu_activate (menu_t * menu);
ext nil menu_deactivate (menu_t * menu);

# endif // PGE_MENU_H

