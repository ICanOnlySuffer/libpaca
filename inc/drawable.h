
# ifndef PGE_DRAWABLE_H
# define PGE_DRAWABLE_H
# include "pge.h"

typedef struct drawable_t {
	ptr * data;
	s16 x;
	s16 y;
	u16 w;
	u16 h;
	nil (* draw) (struct drawable_t * drawable);
	nil (* free) (ptr * data);
} drawable_t;

extern nil drawable_center_x (drawable_t * drawable);
extern nil drawable_center_y (drawable_t * drawable);
stainl nil drawable_draw (drawable_t * drawable) {
	drawable -> draw (drawable);
}
extern nil drawable_free (drawable_t * drawable);
extern nil drawable_free_vec (vec * drawables);
extern nil drawable_free_arr (u08 length, drawable_t * drawables []);
extern nil drawable_extract (
	drawable_t * drawable,
	u08 index,
	SDL_Surface * surface
);
extern nil drawable_render (drawable_t * drawable, u08 index);

# endif // PGE_DRAWABLE_H

