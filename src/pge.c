# include "../inc/pge.h"

struct window window;

u08 run = true;

nil init (str title, u16 width, u16 height, u08 delay) {
	log_init ();
	proc_init ("init");
	font_init ();
	vectors_init ();
	
	LOG ("SDL.init");
	if (SDL_Init (SDL_INIT_VIDEO)) {
		LOG_ERR ("SDL_Init: ", (str) SDL_GetError ());
		proc_quit ();
		exit (1);
	}
	
	LOG ("window.window = SDL.create_window");
	window.window = SDL_CreateWindow (
		title,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		width,
		height,
		0
	);
	if (not window.window) {
		LOG_ERR ((str) SDL_GetError ());
		proc_quit ();
		SDL_Quit ();
		exit (1);
	}
	
	LOG ("window.renderer = SDL.create_renderer");
	window.renderer = SDL_CreateRenderer (window.window, -1, 2);
	if (not window.renderer) {
		LOG_ERR ((str) SDL_GetError ());
		SDL_DestroyWindow (window.window);
		SDL_Quit ();
		proc_quit ();
		exit (1);
	}
	
	LOG ("window.texture = SDL.create_texture");
	window.texture = SDL_CreateTexture (
		window.renderer,
		SDL_PIXELFORMAT_RGBA8888,
		SDL_TEXTUREACCESS_TARGET,
		width,
		height
	);
	if (not window.texture) {
		LOG_ERR ((str) SDL_GetError ());
		SDL_DestroyRenderer (window.renderer);
		SDL_DestroyWindow (window.window);
		SDL_Quit ();
		proc_quit ();
		exit (1);
	}
	
	window.width = width;
	window.height = height;
	window.delay = delay;
	
	proc_quit ();
}

nil quit () {
	proc_init ("quit");
	LOG ("destroying renderer...");
	SDL_DestroyRenderer (window.renderer);
	LOG ("destroying texture...");
	SDL_DestroyTexture (window.texture);
	LOG ("destroying window...");
	SDL_DestroyWindow (window.window);
	
	vectors_at_quit ();
	vectors_quit ();
	
	LOG ("quitting SDL...");
	font_quit ();
	SDL_Quit ();
	proc_quit ();
	log_quit ();
}

nil loop () {
	proc_init ("mainloop");
	SDL_Event event;
	do {
		set_render_target (window.texture);
		render_clear ();
		while (SDL_PollEvent (&event)) {
			vectors_on_event (&event);
		}
		vectors_on_update ();
		set_render_target (NIL);
		render_copy (window.texture, NIL);
		render ();
		SDL_Delay (window.delay);
	} while (run);
	proc_quit ();
	quit ();
}

