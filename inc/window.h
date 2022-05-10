
# ifndef PGE_WINDOW_H
# define PGE_WINDOW_H
# define SDL_MAIN_HANDLED
# include <SDL2/SDL_video.h>
# include <SDL2/SDL_image.h>
# include "log.h"

extern struct window {
	SDL_Window * window;
	SDL_Renderer * renderer;
	SDL_Texture * texture;
	u16 w;
	u16 h;
} WINDOW;

extern nil window_init (str name, u64 width, u64 height);
extern nil window_quit ();

inl SDL_Texture * texture_from_surface (SDL_Surface * surface) {
	return SDL_CreateTextureFromSurface (WINDOW.renderer, surface);
}

inl nil set_render_target (SDL_Texture * texture) {
	SDL_SetRenderTarget (WINDOW.renderer, texture);
}

inl nil render_clear () {
	SDL_RenderClear (WINDOW.renderer);
}

inl nil render_copy (SDL_Texture * texture, SDL_Rect * rect) {
	SDL_RenderCopy (WINDOW.renderer, texture, NIL, rect);
}

inl nil render () {
	SDL_RenderPresent (WINDOW.renderer);
}

# endif // PGE_WINDOW_H

