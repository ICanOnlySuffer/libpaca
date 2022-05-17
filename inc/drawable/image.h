
# ifndef PGE_DRAWABLE_IMAGE_H
# define PGE_DRAWABLE_IMAGE_H
# include "../drawable.h"

ext surface_t * image_load (str path);
ext texture_t * image_load_texture (str path);
ext nil image_draw (drawable_t * image);
ext nil image_free (ptr * data);

typedef struct {
	s16 x;
	s16 y;
} image_new_params;
ext drawable_t * image_new_ (str path, image_new_params);
# define image_new(path_, ...) \
	image_new_ ( \
		path_, \
		(image_new_params) { \
			.x = 0, \
			.y = 0, \
			__VA_ARGS__ \
		} \
	)

# endif // PGE_DRAWABLE_IMAGE_H

