# include "../inc/pge.h"

struct window window;

TTF_Font * FONT;
vec ON_UPDATE;
vec ON_EVENT;
vec AT_QUIT;

u08 run = true;

nil init (str title, u16 width, u16 height, u08 delay) {
	log_init ("init");
	LOG ("SDL_Init");
	if (SDL_Init (SDL_INIT_VIDEO)) {
		LOG_ERR ("SDL_Init: ", (str) SDL_GetError ());
		log_quit ();
		exit (1);
	}
	
	LOG ("SDL_CreateWindow");
	window.window = SDL_CreateWindow (
		title,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		width,
		height,
		0
	);
	if (not window.window) {
		LOG_ERR ("SDL_CreateWindow: ", (str) SDL_GetError ());
		log_quit ();
		SDL_Quit ();
		exit (1);
	}
	
	LOG ("SDL_CreateRenderer");
	window.renderer = SDL_CreateRenderer (window.window, -1, 2);
	if (not window.renderer) {
		LOG_ERR ("SDL_CreateRenderer: ", (str) SDL_GetError ());
		SDL_DestroyWindow (window.window);
		log_quit ();
		SDL_Quit ();
		exit (1);
	}
	
	LOG ("SDL_CreateTexture");
	window.texture = SDL_CreateTexture (
		window.renderer,
		SDL_PIXELFORMAT_RGBA8888,
		SDL_TEXTUREACCESS_TARGET,
		width,
		height
	);
	if (not window.texture) {
		LOG_ERR ("SDL_CreateTexture: ", (str) SDL_GetError ());
		SDL_DestroyRenderer (window.renderer);
		SDL_DestroyWindow (window.window);
		log_quit ();
		SDL_Quit ();
		exit (1);
	}
	
	LOG ("TTF_Init");
	TTF_Init ();
	
	ON_UPDATE = VEC (4);
	ON_EVENT = VEC (4);
	AT_QUIT = VEC (4);
	
	window.width = width;
	window.height = height;
	window.delay = delay;
	
	log_quit ();
}

nil quit () {
	log_init ("quit");
	LOG ("destroying renderer...");
	SDL_DestroyRenderer (window.renderer);
	LOG ("destroying texture...");
	SDL_DestroyTexture (window.texture);
	LOG ("destroying window...");
	SDL_DestroyWindow (window.window);
	LOG ("running at_quit...");
	log_init ("at_quit");
	for (u08 i = 0; i < AT_QUIT.size; i++) {
		((nil (*) (nil)) AT_QUIT.items [i]) ();
	}
	log_quit ();
	LOG ("freeing vectors...");
	free (ON_UPDATE.items);
	free (ON_EVENT.items);
	free (AT_QUIT.items);
	LOG ("quitting SDL...");
	SDL_Quit ();
	TTF_Quit ();
	log_quit ();
	free (log_mods.items);
}

nil loop () {
	log_init ("mainloop");
	SDL_Event event;
	do {
		set_render_target (window.texture);
		render_clear ();
		while (SDL_PollEvent (&event)) {
			for (u08 i = 0; i < ON_EVENT.size; i++) {
				((nil (*) (SDL_Event *)) ON_EVENT.items [i]) (&event);
			}
		}
		for (u08 i = 0; i < ON_UPDATE.size; i++) {
			((nil (*) ()) ON_UPDATE.items [i]) ();
		}
		set_render_target (NIL);
		render_copy (window.texture, NIL);
		render ();
		SDL_Delay (window.delay);
	} while (run);
	log_quit ();
	quit ();
}

