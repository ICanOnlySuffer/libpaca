
# ifndef PGE_SURFACE_H
# define PGE_SURFACE_H
# include <SDL2/SDL_surface.h>
# include <SDL2/SDL_render.h>
# include <pul/vec.h>
# include "window.h"
# include "pge.h"

typedef SDL_Surface surface_t;
typedef SDL_Texture texture_t;
typedef SDL_Color color_t;
typedef SDL_Rect rect_t;

inl nil surface_free (surface_t * surface) {
	SDL_FreeSurface (surface);
}

inl nil texture_free (texture_t * texture) {
	SDL_DestroyTexture (texture);
}

inl nil texture_free_arr (u08 n_textures, texture_t * textures []) {
	for (u08 i = 0; i < n_textures; i++) {
		texture_free (textures [i]);
	}
}

# define TEXTURE_FREE(...) \
	texture_free_arr ( \
		ARR_LEN (((texture_t * []) {__VA_ARGS__})), \
		(texture_t * []) {__VA_ARGS__} \
	)

inl texture_t * texture_from_surface (surface_t * surface) {
	return SDL_CreateTextureFromSurface (WINDOW.renderer, surface);
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

