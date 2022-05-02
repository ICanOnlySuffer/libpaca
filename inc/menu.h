
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

# define MENU_LOG(menu_, ...) \
	PUT ( \
		LOG_SPACES, \
		"\e[35m<", \
		menu_.name, \
		"> ", \
		__VA_ARGS__, \
		"\e[0m\n" \
	)

# endif // PGE_MENU_H

