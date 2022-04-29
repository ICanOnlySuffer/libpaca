# include "../inc/pge.h"

SDL_Window * WINDOW;
SDL_Renderer * RENDERER;
SDL_Texture * TEXTURE;
TTF_Font * FONT;

struct window window;

vec ON_UPDATE;
vec ON_EVENT;
vec AT_QUIT;
vec KEYS;

u08 DELAY = 1000 / 30;
u08 run = true;

static nil on_event (SDL_Event * event) {
	u64 key = (u64) event -> key.keysym.sym;
	switch (event -> type) {
	case SDL_KEYDOWN:
		if (vec_idx (&KEYS, (ptr) key) == KEYS.size) {
			vec_psh (&KEYS, (ptr) key);
		}
		switch (key) {
		case 'q':
			if (vec_idx (&KEYS, (ptr) KEY_CONTROL) != KEYS.size) {
				run = false;
				break;
			}
			break;
		}
		break;
	}
}

nil init (str title, u16 width, u16 height) {
	LOG ("(init): initalizing...");
	if (SDL_Init (SDL_INIT_VIDEO) < 0) {
		LOG_ERR ("(init): ", (str) SDL_GetError ());
		exit (1);
	}
	TTF_Init ();
	
	LOG ("(init): creating window...");
	WINDOW = SDL_CreateWindow (
		title,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		width,
		height,
		0
	);
	if (not WINDOW) {
		LOG_ERR ("(init): ", (str) SDL_GetError ());
		SDL_Quit ();
		exit (1);
	}
	
	LOG ("(init): creating renderer...");
	RENDERER = SDL_CreateRenderer (WINDOW, -1, 2);
	if (not RENDERER) {
		LOG_ERR ("(init): ", (str) SDL_GetError ());
		SDL_DestroyWindow (WINDOW);
		SDL_Quit ();
		exit (1);
	}
	
	LOG ("(init): creating texture...");
	TEXTURE = SDL_CreateTexture (
		RENDERER,
		SDL_PIXELFORMAT_RGBA8888,
		SDL_TEXTUREACCESS_TARGET,
		width,
		height
	);
	if (not TEXTURE) {
		LOG_ERR ("(init): ", (str) SDL_GetError ());
		SDL_DestroyRenderer (RENDERER);
		SDL_DestroyWindow (WINDOW);
		SDL_Quit ();
		exit (1);
	}
	
	ON_UPDATE = VEC (4);
	ON_EVENT = VEC (4);
	AT_QUIT = VEC (4);
	KEYS = VEC (4);
	
	vec_psh (&ON_EVENT, on_event);
	
	window.width = width;
	window.height = height;
	LOG ("(init): success");
}

nil quit () {
	LOG ("(quit): quitting...");
	LOG ("(quit): destroying renderer...");
	SDL_DestroyRenderer (RENDERER);
	LOG ("(quit): destroying texture...");
	SDL_DestroyTexture (TEXTURE);
	LOG ("(quit): destroying window...");
	SDL_DestroyWindow (WINDOW);
	LOG ("(quit): running at_quit...");
	for (u08 i = 0; i < AT_QUIT.size; i++) {
		((nil (*) (nil)) AT_QUIT.items [i]) ();
	}
	LOG ("(quit): freeing vectors...");
	free (ON_UPDATE.items);
	free (ON_EVENT.items);
	free (AT_QUIT.items);
	free (KEYS.items);
	LOG ("(quit): quitting SDL...");
	SDL_Quit ();
	TTF_Quit ();
	LOG ("(quit): success");
}

nil mainloop () {
	SDL_Event event;
	do {
		set_render_target (TEXTURE);
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
		render_copy (TEXTURE, NIL);
		render ();
		SDL_Delay (DELAY);
	} while (run);
	quit ();
}

