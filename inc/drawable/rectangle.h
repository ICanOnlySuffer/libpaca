
# ifndef LIBPACA_DRAWABLE_RECTANGLE_H
# define LIBPACA_DRAWABLE_RECTANGLE_H
# include "../drawable.h"

typedef struct {
	DRAWABLE_STRUCT;
	color_t * color;
} rectangle_t;

ext nil rectangle_draw_lines (rectangle_t * rectangle);
ext nil rectangle_draw_full (rectangle_t * rectangle);
ext nil rectangle_free (rectangle_t * rectangle);

ext rectangle_t * rectangle_new (rectangle_t rectangle);

# define RECTANGLE_NEW(...) \
	rectangle_new ( \
		(rectangle_t) { \
			DRAWABLE_DEFAULT, \
			.draw = (prc) rectangle_draw_full, \
			__VA_ARGS__ \
		} \
	)

# endif // LIBPACA_DRAWABLE_RECTANGLE_H

