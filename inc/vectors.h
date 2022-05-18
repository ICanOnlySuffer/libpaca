
# ifndef PGE_VECTORS_H
# define PGE_VECTORS_H
# define SDL_MAIN_HANDLED
# include <SDL2/SDL_events.h>
# include <pul/vec.h>

typedef SDL_Event event_t;

ext vec ON_UPDATE;
ext vec ON_EVENT;
ext vec AT_QUIT;

ext vec vector_new (str name, u64 size);
ext nil vector_free (str name, vec * vector);

ext nil vector_psh (str vec_, vec * vector, str fun_, ptr fun);
ext nil vector_rmv (str vec_, vec * vector, str fun_, ptr fun);

ext nil on_update_psh (str fun_name, nil (* fun) ());
ext nil on_event_psh (str fun_name, nil (* fun) (event_t *));
ext nil at_quit_psh (str fun_name, nil (* fun) ());

ext nil on_update_rmv (str fun_name, nil (* fun) ());
ext nil on_event_rmv (str fun_name, nil (* fun) (event_t *));
ext nil at_quit_rmv (str fun_name, nil (* fun) ());

ext nil vectors_on_update ();
ext nil vectors_on_event (event_t * event);
ext nil vectors_at_quit ();

ext nil vectors_init ();
ext nil vectors_quit ();

# endif // PGE_VECTORS_H

