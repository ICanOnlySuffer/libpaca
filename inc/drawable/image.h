
# ifndef PGE_DRAWABLE_IMAGE_H
# define PGE_DRAWABLE_IMAGE_H
# include "../drawable.h"

ext nil image_draw (drawable_t * image);
ext nil image_free (ptr * data);
ext drawable_t * image_new (str path, s16 x, s16 y);


# endif // PGE_DRAWABLE_IMAGE_H

