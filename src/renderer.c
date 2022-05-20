# include "../inc/renderer.h"
# include "../inc/vectors.h"

static color_t window_default_color = {0, 0, 0, 255};

window_t * WINDOW = NIL;
renderer_t * RENDERER = NIL;
texture_t * TEXTURE = NIL;
u16 WINDOW_W;
u16 WINDOW_H;
u08 WINDOW_DELAY;
color_t * WINDOW_COLOR = &window_default_color;

nil window_quit () {
	LOG ("WINDOW.destroy", 0);
	SDL_DestroyWindow (WINDOW);
}

u08 window_init (str name, u64 w, u64 h, u08 delay) {
	str proc = "Window.init";
	proc_init (proc);
	
	LOG ("WINDOW = Window.new \"%s\", %u, %u", (u64) name, w, h);
	WINDOW = SDL_CreateWindow (
		name,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		w,
		h,
		0
	);
	if (not WINDOW) {
		LOG_ERR ("Window.new: %s", (u64) SDL_GetError ());
		proc_quit (proc);
		return false;
	}
	at_quit_psh ("WINDOW.destroy", window_quit);
	
	LOG ("RENDERER = Renderer.new WINDOW", 0);
	RENDERER = SDL_CreateRenderer (
		WINDOW,
		-1,
		SDL_RENDERER_PRESENTVSYNC
	);
	if (not RENDERER) {
		LOG_ERR ("Renderer.new: %s", (u64) SDL_GetError ());
		proc_quit (proc);
		return false;
	}
	at_quit_psh ("RENDERER.destroy", renderer_quit);
	
	LOG ("TEXTURE = Texture.new RENDERER, %u, %u", w, h);
	TEXTURE = SDL_CreateTexture (
		RENDERER,
		SDL_PIXELFORMAT_RGBA8888,
		SDL_TEXTUREACCESS_TARGET,
		w,
		h
	);
	if (not TEXTURE) {
		LOG_ERR ("Texture.new: %s", (u64) SDL_GetError ());
		proc_quit (proc);
		return false;
	}
	at_quit_psh ("TEXTURE.destroy %s", texture_quit);
	
	WINDOW_W = w;
	WINDOW_H = h;
	WINDOW_DELAY = delay;
	
	proc_quit (proc);
	return true;
}

/* renderer */
nil renderer_quit () {
	LOG ("RENDERER.destroy", 0);
	SDL_DestroyRenderer (RENDERER);
}

/* texture */
nil texture_quit () {
	LOG ("TEXTURE.destroy", 0);
	texture_free (TEXTURE);
}

nil texture_free (texture_t * texture) {
	SDL_DestroyTexture (texture);
}

/* surface */
nil surface_extract (
	surface_t * surface,
	texture_t ** texture,
	s32 * w,
	s32 * h
) {
	if (surface) {
		*texture = texture_from_surface (surface);
		*w = surface -> w;
		*h = surface -> h;
		surface_free (surface);
	} else {
		LOG_ERR ("surface_extract: surface == NIL", 0);
		*texture = NIL;
	}
}

nil surface_replace (
	surface_t * surface,
	color_t * to_replace,
	color_t * replacement
) {
	if (not surface) {
		LOG_ERR ("surface_replace: surface == NIL", 0);
		return;
	}
	u08 * pixels = surface -> pixels;
	
	for (u16 i = 0; i < surface -> h; i++) {
		for (u16 j = 0; j < surface -> w; j++) {
			u32 * pixel = (u32 *) (
				pixels +
				i * surface -> pitch +
				j * sizeof (u32)
			);
			if (*pixel == *(u32 *) to_replace) {
				*pixel = *(u32 *) replacement;
			}
		}
	}
}

