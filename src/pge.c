# include "../inc/pge.h"

struct window window;

static u08 DELAY;
u08 run = true;

nil init (str title, u16 width, u16 height, u64 delay) {
	str proc = "init";
	proc_init (proc);
	LOG ("SDL.init", NIL);
	if (SDL_Init (SDL_INIT_VIDEO)) {
		LOG_ERR ("SDL_Init: %s", (ptr) SDL_GetError ());
		proc_quit (proc);
		exit (1);
	}
	vectors_init ();
	window_init (title, width, height);
	font_init ();
	LOG ("DELAY = %u", &delay);
	DELAY = delay;
	proc_quit (proc);
}

nil quit () {
	str proc = "quit";
	proc_init (proc);
	vectors_at_quit ();
	LOG ("quitting SDL...", NIL);
	SDL_Quit ();
	proc_quit (proc);
}

nil loop () {
	str proc = "loop";
	proc_init (proc);
	SDL_Event event;
	do {
		set_render_target (WINDOW.texture);
		render_clear ();
		while (SDL_PollEvent (&event)) {
			vectors_on_event (&event);
		}
		vectors_on_update ();
		set_render_target (NIL);
		render_copy (WINDOW.texture, NIL);
		render ();
		SDL_Delay (DELAY);
	} while (run);
	proc_quit (proc);
	quit ();
}

