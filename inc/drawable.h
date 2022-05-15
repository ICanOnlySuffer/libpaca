
# ifndef PGE_DRAWABLE_H
# define PGE_DRAWABLE_H
# include <SDL2/SDL_surface.h>
# include <SDL2/SDL_render.h>
# include <pul/vec.h>
# include "window.h"
# include "pge.h"

# define CENTER -32768

typedef SDL_Surface surface_t;
typedef SDL_Texture texture_t;

typedef struct drawable_t {
	ptr * data;
	s16 x;
	s16 y;
	u16 w;
	u16 h;
	nil (* draw) (struct drawable_t * drawable);
	nil (* free) (ptr * data);
} drawable_t;

inl nil drawable_draw (drawable_t * drawable) {
	drawable -> draw (drawable);
}
ext nil drawable_set_position (drawable_t * drawable, s16 x, s16 y);
ext nil drawable_free (drawable_t * drawable);
ext nil drawable_free_vec (vec * drawables);
ext nil drawable_free_arr (u08 length, drawable_t * drawables []);
ext nil surface_extract (
	surface_t * surface,
	u16 * width,
	u16 * height,
	texture_t ** texture
);
ext nil drawable_render (drawable_t * drawable, u08 index);

# endif // PGE_DRAWABLE_H

