
# ifndef PGE_DRAWABLE_IMAGE_H
# define PGE_DRAWABLE_IMAGE_H
# include "../drawable.h"

extern nil image_draw (drawable_t * image);
extern nil image_free (ptr * data);
extern drawable_t * image_new (str path);

# endif // PGE_DRAWABLE_IMAGE_H

