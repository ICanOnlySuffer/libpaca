# include "../../inc/drawable/image.h"

surface_t * image_load (str path) {
	surface_t * surface = IMG_Load (path);
	if (not surface) {
		LOG_ERR ("IMG_Load: %s", (u64) SDL_GetError ());
		run = false;
	}
	return surface;
}

texture_t * image_load_texture (str path) {
	surface_t * surface = image_load (path);
	texture_t * texture = texture_from_surface (surface);
	SDL_FreeSurface (surface);
	return texture;
}

nil image_draw (drawable_t * image) {
	SDL_Rect rect = {image -> x, image -> y, image -> w, image -> h};
	render_copy (image -> data [0], &rect);
}

nil image_free (ptr * data) {
	SDL_DestroyTexture (data [0]);
}

drawable_t * image_new (str path, s16 x, s16 y) {
	drawable_t * image = malloc (sizeof (drawable_t));
	image -> data = malloc (sizeof (ptr));
	surface_extract (
		image_load (path),
		&image -> w,
		&image -> h,
		(texture_t **) &image -> data [0]
	);
	drawable_set_position (image, x, y);
	image -> draw = image_draw;
	image -> free = image_free;
	return image;
}

