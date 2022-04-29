
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
stainl nil drawable_free (drawable_t * drawable) {
	drawable -> free (drawable -> data);
	free (drawable);
}

# endif // PGE_DRAWABLE_H

