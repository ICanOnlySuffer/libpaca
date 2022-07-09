
# ifndef LIBPACA_DRAWABLE_IMAGE_H
# define LIBPACA_DRAWABLE_IMAGE_H
# include "../drawable.h"

typedef struct {
	DRAWABLE_STRUCT;
	texture_t * texture;
} image_t;

ext nil image_draw (image_t * image);
ext nil image_free (image_t * image);

ext surface_t * image_load (str path);
ext texture_t * image_load_texture (str path);

ext image_t * image_new (str path, image_t image);
# define IMAGE_NEW(path_, ...) \
	image_new ( \
		path_, \
		(image_t) { \
			DRAWABLE_DEFAULT, \
			__VA_ARGS__ \
		} \
	)

# endif // LIBPACA_DRAWABLE_IMAGE_H

