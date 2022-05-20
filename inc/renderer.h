
# ifndef PGE_RENDERER_H
# define PGE_RENDERER_H
# define SDL_MAIN_HANDLED
# include <SDL2/SDL_surface.h>
# include <SDL2/SDL_render.h>
# include <SDL2/SDL_video.h>
# include <SDL2/SDL_image.h>
# include <pul/vec.h>
# include "pge.h"
# include "log.h"

typedef SDL_Renderer renderer_t;
typedef SDL_Surface surface_t;
typedef SDL_Texture texture_t;
typedef SDL_Window window_t;
typedef SDL_Color color_t;
typedef SDL_FRect frect_t;
typedef SDL_Rect rect_t;

ext window_t * WINDOW;
ext renderer_t * RENDERER;
ext texture_t * TEXTURE;
ext u16 WINDOW_W;
ext u16 WINDOW_H;
ext u08 WINDOW_DELAY;
ext color_t * WINDOW_COLOR;

/* window */
ext nil window_quit ();
ext u08 window_init (str name, u64 w, u64 h, u08 delay);

/* renderer */
ext nil renderer_quit ();

inl nil render_set_draw_color (color_t * color) {
	SDL_SetRenderDrawColor (
		RENDERER,
		color -> r,
		color -> g,
		color -> b,
		color -> a
	);
}

inl nil render_set_target (texture_t * texture) {
	SDL_SetRenderTarget (RENDERER, texture);
}

inl nil render_draw_rect_lines (rect_t * rect) {
	SDL_RenderDrawRect (RENDERER, rect);
}

inl nil render_draw_rect_full (rect_t * rect) {
	SDL_RenderFillRect (RENDERER, rect);
}

inl nil render_clear () {
	SDL_RenderClear (RENDERER);
}

inl nil render_copy (texture_t * texture, rect_t * rect) {
	SDL_RenderCopy (RENDERER, texture, NIL, rect);
}

inl nil render_present () {
	SDL_RenderPresent (RENDERER);
}

/* texture */
ext nil texture_quit ();

inl texture_t * texture_from_surface (surface_t * surface) {
	return SDL_CreateTextureFromSurface (RENDERER, surface);
}

ext nil texture_free (texture_t * texture);

# define TEXTURE_FREE(...) \
	arr_for_all ( \
		(ARR_LEN ((texture_t * []) {__VA_ARGS__})), \
		(texture_t * []) {__VA_ARGS__}, \
		(nil (*) (ptr)) texture_free \
	)

/* surface */
inl nil surface_free (surface_t * surface) {
	SDL_FreeSurface (surface);
}

ext nil surface_extract (
	surface_t * surface,
	texture_t ** texture,
	s32 * width,
	s32 * height
);

ext nil surface_replace (
	surface_t * surface,
	color_t * to_replace,
	color_t * replacement
);

# endif // PGE_SURFACE_H

