# include "../inc/vectors.h"
# include "../inc/window.h"

prv color_t window_default_color = {0, 0, 0, 255};

window_t * WINDOW = NIL;
renderer_t * RENDERER = NIL;
texture_t * TEXTURE = NIL;
str WINDOW_TITLE;
u16 WINDOW_W;
u16 WINDOW_H;
u08 WINDOW_DELAY;
color_t * WINDOW_COLOR = &window_default_color;

prv u08 _window_destroy () {
	if (WINDOW) {
		LOG ("WINDOW.destroy");
		SDL_DestroyWindow (WINDOW);
	}
	if (RENDERER) {
		LOG ("RENDERER.destroy");
		SDL_DestroyRenderer (RENDERER);
	}
	if (TEXTURE) {
		LOG ("TEXTURE.destroy");
		texture_free (TEXTURE);
	}
	ret true;
}
prv proc_t window_destroy = {"Window.destroy", _window_destroy};

prv u08 _window_init () {
	at_quit_push (&window_destroy);
	
	LOG (
		"WINDOW = Window.new \"%s\", %u, %u",
		WINDOW_TITLE, WINDOW_W, WINDOW_H
	);
	WINDOW = window_new (WINDOW_TITLE, WINDOW_W, WINDOW_H);
	if (not WINDOW) {
		ERR ("Window.new: %s", SDL_GetError ());
		ret false;
	}
	
	LOG ("RENDERER = Renderer.new WINDOW", 0);
	RENDERER = renderer_new (WINDOW);
	if (not RENDERER) {
		ERR ("Renderer.new: %s", SDL_GetError ());
		ret false;
	}
	
	LOG (
		"TEXTURE = Texture.new RENDERER, %u, %u",
		WINDOW_W, WINDOW_H
	);
	TEXTURE = texture_new (RENDERER, WINDOW_W, WINDOW_H);
	if (not TEXTURE) {
		ERR ("Texture.new: %s", SDL_GetError ());
		ret false;
	}
	
	ret true;
}
proc_t window_init = {"Window.init", _window_init};

/* renderer */

/* texture */
nil texture_free (ptr texture) {
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
		ERR ("surface_extract: surface == NIL");
		ret false;
	}
}

nil surface_replace (
	surface_t * surface,
	color_t * to_replace,
	color_t * replacement
) {
	if (not surface) {
		ERR ("surface_replace: surface == NIL");
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

