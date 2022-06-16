
# ifndef LIBPACA_MENU_H
# define LIBPACA_MENU_H
# include <pocha/cor.h>

typedef struct {
	str name;
	u08 (* activate) ();
	u08 (* deactivate) ();
	u08 activated;
} menu_t;

ext nil menu_activate (menu_t * menu);
ext nil menu_deactivate (menu_t * menu);

# endif // LIBPACA_MENU_H

