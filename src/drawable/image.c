# include "../../inc/drawable/image.h"

nil image_draw (drawable_t * image) {
	SDL_Rect rect = {image -> x, image -> y, image -> w, image -> h};
	render_copy (image -> data [0], &rect);
}

nil image_free (ptr * data) {
	SDL_DestroyTexture (data [0]);
}

drawable_t * image_new (str path, s16 x, s16 y) {
	drawable_t * image = malloc (sizeof (drawable_t));
	SDL_Surface * surface = IMG_Load (path);
	if (not surface) {
		LOG_ERR ("image_new: %s", (u64) SDL_GetError ());
		quit ();
	}
	image -> data = malloc (sizeof (ptr));
	surface_extract (
		surface,
		&image -> w,
		&image -> h,
		(SDL_Texture **) &image -> data [0]
	);
	drawable_set_position (image, x, y);
	image -> draw = image_draw;
	image -> free = image_free;
	return image;
}

