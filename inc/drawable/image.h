
# ifndef PGE_DRAWABLE_IMAGE_H
# define PGE_DRAWABLE_IMAGE_H
# include "../drawable.h"

ext surface_t * image_load (str path);
ext texture_t * image_load_texture (str path);
ext nil image_draw (drawable_t * image);
ext nil image_free (ptr * data);

ext drawable_t * image_new_ (str path, drawable_t params);
# define image_new(path_, ...) \
	image_new_ ( \
		path_, \
		(drawable_t) { \
			.x = 0, \
			.y = 0, \
			.dx = 0, \
			.dy = 0, \
			__VA_ARGS__ \
		} \
	)

# endif // PGE_DRAWABLE_IMAGE_H

