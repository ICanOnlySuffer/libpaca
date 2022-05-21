
# ifndef PGE_DRAWABLE_RECTANGLE_H
# define PGE_DRAWABLE_RECTANGLE_H
# include "../drawable.h"

ext nil rectangle_draw_lines (drawable_t * rectangle);
ext nil rectangle_draw_full (drawable_t * rectangle);
ext nil rectangle_free (ptr * data);

ext drawable_t * rectangle_new_ (color_t * color, drawable_t params);
# define rectangle_new(color_, ...) \
	rectangle_new_ ( \
		color_, \
		(drawable_t) { \
			.x = 0, \
			.y = 0, \
			.w = 1, \
			.h = 1, \
			.dy = 0, \
			.dx = 0, \
			.draw = rectangle_draw_full, \
			__VA_ARGS__ \
		} \
	)

# endif // PGE_DRAWABLE_RECTANGLE_H

