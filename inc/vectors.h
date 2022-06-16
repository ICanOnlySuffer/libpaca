
# ifndef LIBPACA_VECTORS_H
# define LIBPACA_VECTORS_H
# define SDL_MAIN_HANDLED
# include <SDL2/SDL_events.h>
# include <pocha/vec.h>
# include "proc.h"

typedef SDL_Event event_t;

typedef struct {
	ptr * items;
	u16 capacity;
	u16 size;
	str name;
} vector_t;

ext vector_t vector_new (str name, u16 size);
ext nil vector_free (vector_t * vector);

ext u08 vector_psh (vector_t * vector, ptr item);
ext u08 vector_rmv (vector_t * vector, ptr item);

ext u08 on_update_psh (proc_t * proc);
ext u08 on_event_psh (proc_t * proc);
ext u08 at_quit_psh (proc_t * proc);

ext u08 on_update_rmv (proc_t * proc);
ext u08 on_event_rmv (proc_t * proc);
ext u08 at_quit_rmv (proc_t * proc);

ext nil vectors_on_update ();
ext nil vectors_on_event (event_t * event);
ext proc_t vectors_at_quit;

ext proc_t vectors_init;

# endif // LIBPACA_VECTORS_H

