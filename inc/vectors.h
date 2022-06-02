
# ifndef PGE_VECTORS_H
# define PGE_VECTORS_H
# define SDL_MAIN_HANDLED
# include <SDL2/SDL_events.h>
# include <pul/vec.h>

typedef SDL_Event event_t;

typedef struct {
	ptr * items;
	u16 capacity;
	u16 size;
	str name;
} vector_t;

typedef struct {
	prc proc;
	str name;
} proc_t;

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
ext nil vectors_at_quit ();

ext nil vectors_init ();

# endif // PGE_VECTORS_H

