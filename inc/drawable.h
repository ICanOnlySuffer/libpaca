
# ifndef PGE_DRAWABLE_H
# define PGE_DRAWABLE_H
# include <SDL2/SDL_render.h>
# include <pul/vec.h>
# include "surface.h"

# define DRAWABLE_CENTER -32768

typedef struct drawable_t {
	ptr * data;
	rect_t rect;
	nil (* draw) (struct drawable_t * drawable);
	nil (* free) (ptr * data);
} drawable_t;

inl nil drawable_draw (drawable_t * drawable) {
	drawable -> draw (drawable);
}
ext nil drawable_set_position (drawable_t * drawable, s16 x, s16 y);
ext nil drawable_free (drawable_t * drawable);
ext nil drawable_render (drawable_t * drawable, u08 index);

# endif // PGE_DRAWABLE_H

