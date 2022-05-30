
# ifndef PGE_DRAWABLE_RECTANGLE_H
# define PGE_DRAWABLE_RECTANGLE_H
# include "../drawable.h"

ext nil rectangle_draw_lines (drawable_t * rectangle);
ext nil rectangle_draw_full (drawable_t * rectangle);
ext nil rectangle_free (drawable_t * rectangle);

struct rectangle {
	struct drawable_t;
	color_t * color;
};

ext drawable_t * rectangle_new (struct rectangle rectangle);

# define RECTANGLE_NEW(...) \
	rectangle_new ( \
		(struct rectangle) { \
			DRAWABLE_DEFAULT, \
			.draw = rectangle_draw_full, \
			__VA_ARGS__ \
		} \
	)

# endif // PGE_DRAWABLE_RECTANGLE_H

