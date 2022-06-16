# include "../inc/renderer.h"
# include "../inc/vectors.h"

static color_t window_default_color = {0, 0, 0, 255};

window_t * WINDOW = NIL;
renderer_t * RENDERER = NIL;
texture_t * TEXTURE = NIL;
str WINDOW_TITLE;
u16 WINDOW_W;
u16 WINDOW_H;
u08 WINDOW_DELAY;
color_t * WINDOW_COLOR = &window_default_color;

static u08 _window_destroy () {
	if (WINDOW) {
		LOG ("WINDOW.destroy", 0);
		SDL_DestroyWindow (WINDOW);
	}
	if (RENDERER) {
		LOG ("RENDERER.destroy", 0);
		SDL_DestroyRenderer (RENDERER);
	}
	if (TEXTURE) {
		LOG ("TEXTURE.destroy", 0);
		texture_free (TEXTURE);
	}
	ret true;
}
static proc_t window_destroy = {"Window.destroy", _window_destroy};

static u08 _window_init () {
	at_quit_psh (&window_destroy);
	
	LOG (
		"WINDOW = Window.new \"%s\", %u, %u",
		(u64) WINDOW_TITLE, WINDOW_W, WINDOW_H
	);
	WINDOW = window_new (WINDOW_TITLE, WINDOW_W, WINDOW_H);
	if (not WINDOW) {
		LOG_ERR ("Window.new: %s", (u64) SDL_GetError ());
		ret false;
	}
	
	LOG ("RENDERER = Renderer.new WINDOW", 0);
	RENDERER = renderer_new (WINDOW);
	if (not RENDERER) {
		LOG_ERR ("Renderer.new: %s", (u64) SDL_GetError ());
		ret false;
	}
	
	LOG (
		"TEXTURE = Texture.new RENDERER, %u, %u",
		WINDOW_W, WINDOW_H
	);
	TEXTURE = texture_new (RENDERER, WINDOW_W, WINDOW_H);
	if (not TEXTURE) {
		LOG_ERR ("Texture.new: %s", (u64) SDL_GetError ());
		ret false;
	}
	
	ret true;
}
proc_t window_init = {"Window.init", _window_init};

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

