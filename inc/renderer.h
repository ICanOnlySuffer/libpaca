
# ifndef LIBPACA_RENDERER_H
# define LIBPACA_RENDERER_H
# define SDL_MAIN_HANDLED
# include <SDL2/SDL_surface.h>
# include <SDL2/SDL_render.h>
# include <SDL2/SDL_video.h>
# include <SDL2/SDL_image.h>
# include <pocha/vec.h>
# include "paca.h"
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
ext str WINDOW_TITLE;
ext u16 WINDOW_W;
ext u16 WINDOW_H;
ext u08 WINDOW_DELAY;
ext color_t * WINDOW_COLOR;

/* window */
inl window_t * window_new (str name, u16 width, u16 height) {
	ret SDL_CreateWindow (
		name,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		width,
		height,
		0
	);
}

ext proc_t window_init;

/* renderer */
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

inl nil render_draw_frect_lines (frect_t frect) {
	SDL_RenderDrawRectF (RENDERER, &frect);
}

inl nil render_draw_frect_full (frect_t frect) {
	SDL_RenderFillRectF (RENDERER, &frect);
}

inl nil render_draw_rect_lines (rect_t rect) {
	SDL_RenderDrawRect (RENDERER, &rect);
}

inl nil render_draw_rect_full (rect_t rect) {
	SDL_RenderFillRect (RENDERER, &rect);
}

inl nil render_clear () {
	SDL_RenderClear (RENDERER);
}

inl nil render_copy_f (texture_t * texture, frect_t frect) {
	SDL_RenderCopyF (RENDERER, texture, NIL, &frect);
}

inl nil render_copy (texture_t * texture, rect_t * rect) {
	SDL_RenderCopy (RENDERER, texture, NIL, rect);
}

inl nil render_present () {
	SDL_RenderPresent (RENDERER);
}

inl renderer_t * renderer_new (window_t * window) {
	ret SDL_CreateRenderer (window, -1, SDL_RENDERER_PRESENTVSYNC);
}

/* texture */
inl texture_t * texture_from_surface (surface_t * surface) {
	return SDL_CreateTextureFromSurface (RENDERER, surface);
}

ext nil texture_free (texture_t * texture);

# define TEXTURE_FREE(...) \
	arr_for_all ( \
		ARR_LEN ((texture_t * []) {__VA_ARGS__}), \
		(ptr []) {__VA_ARGS__}, \
		(prc) texture_free \
	)

inl texture_t * texture_new (renderer_t * renderer, u16 w, u16 h) {
	ret SDL_CreateTexture (
		renderer,
		SDL_PIXELFORMAT_RGBA8888,
		SDL_TEXTUREACCESS_TARGET,
		w,
		h
	);
}

/* surface */
inl nil surface_free (surface_t * surface) {
	SDL_FreeSurface (surface);
}

ext u08 surface_extract (
	surface_t * surface,
	texture_t ** texture,
	f32 * width,
	f32 * height
);

ext nil surface_replace (
	surface_t * surface,
	color_t * to_replace,
	color_t * replacement
);

# endif // LIBPACA_SURFACE_H

