
# ifndef PGE_DRAWABLE_H
# define PGE_DRAWABLE_H
# include <SDL2/SDL_render.h>
# include <pul/vec.h>
# include "surface.h"

# define CENTER -32768

typedef struct drawable_t {
	ptr * data;
	rect_t rect;
	nil (* draw) (struct drawable_t * drawable);
	nil (* free) (ptr * data);
} drawable_t;

ext nil drawable_set_position (drawable_t * drawable, s16 x, s16 y);
ext nil drawable_draw (drawable_t * drawable);
ext nil drawable_free (drawable_t * drawable);

# define DRAWABLE_DRAW(...) \
	arr_for_all ( \
		(ARR_LEN (((drawable_t * []) {__VA_ARGS__}))), \
		(ptr []) {__VA_ARGS__}, \
		(nil (*) (ptr)) drawable_draw \
	)

# define DRAWABLE_FREE(...) \
	arr_for_all ( \
		(ARR_LEN ((drawable_t * []) {__VA_ARGS__})), \
		(drawable_t * []) {__VA_ARGS__}, \
		(nil (*) (ptr)) drawable_free \
	)

# endif // PGE_DRAWABLE_H

