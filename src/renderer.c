# include "../inc/renderer.h"
# include "../inc/vectors.h"

static color_t window_default_color = {0, 0, 0, 255};

window_t * WINDOW;
renderer_t * RENDERER;
texture_t * TEXTURE;
u16 WINDOW_W;
u16 WINDOW_H;
u08 WINDOW_DELAY;
color_t * WINDOW_COLOR = &window_default_color;

static nil window_destroy_proc () {
	LOG ("WINDOW.destroy", 0);
	SDL_DestroyWindow (WINDOW);
}

static nil renderer_destroy_proc () {
	LOG ("RENDERER.destroy", 0);
	SDL_DestroyRenderer (RENDERER);
}

static nil texture_destroy_proc () {
	LOG ("TEXTURE.destroy", 0);
	texture_free (TEXTURE);
}

static proc_t window_destroy = {
	.proc = (prc) window_destroy_proc,
	.name = "WINDOW.destroy"
};

static proc_t renderer_destroy = {
	.proc = (prc) renderer_destroy_proc,
	.name = "RENDERER.destroy"
};

static proc_t texture_destroy = {
	.proc = (prc) texture_destroy_proc,
	.name = "TEXTURE.destroy"
};

u08 window_init (str name, u64 w, u64 h, u08 delay) {
	str proc = "Window.init";
	proc_init (proc);
	
	LOG ("WINDOW = Window.new \"%s\", %u, %u", (u64) name, w, h);
	WINDOW = window_new (name, w, h);
	if (not WINDOW) {
		LOG_ERR ("Window.new: %s", (u64) SDL_GetError ());
		proc_quit (proc);
		ret false;
	}
	at_quit_psh (&window_destroy);
	
	LOG ("RENDERER = Renderer.new WINDOW", 0);
	RENDERER = SDL_CreateRenderer (
		WINDOW,
		-1,
		SDL_RENDERER_PRESENTVSYNC
	);
	if (not RENDERER) {
		LOG_ERR ("Renderer.new: %s", (u64) SDL_GetError ());
		proc_quit (proc);
		ret false;
	}
	at_quit_psh (&renderer_destroy);
	
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
		ret false;
	}
	at_quit_psh (&texture_destroy);
	
	WINDOW_W = w;
	WINDOW_H = h;
	WINDOW_DELAY = delay;
	
	proc_quit (proc);
	ret true;
}

/* renderer */

/* texture */
nil texture_free (texture_t * texture) {
	SDL_DestroyTexture (texture);
}

/* surface */
u08 surface_extract (
	surface_t * surface,
	texture_t ** texture,
	f32 * w,
	f32 * h
) {
	if (surface) {
		*texture = texture_from_surface (surface);
		*w = (f32) surface -> w;
		*h = (f32) surface -> h;
		surface_free (surface);
		ret true;
	} else {
		LOG_ERR ("surface_extract: surface == NIL", 0);
		ret false;
	}
}

nil surface_replace (
	surface_t * surface,
	color_t * to_replace,
	color_t * replacement
) {
	if (not surface) {
		LOG_ERR ("surface_replace: surface == NIL", 0);
		ret;
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

