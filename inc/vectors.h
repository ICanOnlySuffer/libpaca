
# ifndef PGE_VECTORS_H
# define PGE_VECTORS_H
# define SDL_MAIN_HANDLED
# include <SDL2/SDL_events.h>
# include "log.h"

extern vec ON_UPDATE;
extern vec ON_EVENT;
extern vec AT_QUIT;

extern vec vector_new (str name, u64 size);
extern nil vector_free (str name, vec * vector);

extern nil vector_psh (str vec_, vec * vector, str fun_, ptr fun);
extern nil vector_rmv (str vec_, vec * vector, str fun_, ptr fun);

extern nil on_update_psh (str fun_name, nil (* fun) ());
extern nil on_event_psh (str fun_name, nil (* fun) (SDL_Event *));
extern nil at_quit_psh (str fun_name, nil (* fun) ());

extern nil on_update_rmv (str fun_name, nil (* fun) ());
extern nil on_event_rmv (str fun_name, nil (* fun) (SDL_Event *));
extern nil at_quit_rmv (str fun_name, nil (* fun) ());

extern nil vectors_on_update ();
extern nil vectors_on_event (SDL_Event * event);
extern nil vectors_at_quit ();

extern nil vectors_init ();
extern nil vectors_quit ();

# endif // PGE_VECTORS_H

