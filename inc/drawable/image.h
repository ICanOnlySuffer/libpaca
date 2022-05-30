
# ifndef PGE_DRAWABLE_IMAGE_H
# define PGE_DRAWABLE_IMAGE_H
# include "../drawable.h"

ext surface_t * image_load (str path);
ext texture_t * image_load_texture (str path);
ext nil image_draw (drawable_t * image);
ext nil image_free (drawable_t * image);

struct image {
	struct drawable_t;
	texture_t * texture;
};
ext drawable_t * image_new (str path, struct image image);
# define IMAGE_NEW(path_, ...) \
	image_new ( \
		path_, \
		(struct image) { \
			DRAWABLE_DEFAULT, \
			__VA_ARGS__ \
		} \
	)

# endif // PGE_DRAWABLE_IMAGE_H

