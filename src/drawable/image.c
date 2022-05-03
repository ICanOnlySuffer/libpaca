# include "../../inc/drawable/image.h"

nil image_draw (drawable_t * image) {
	SDL_Rect rect = {image -> x, image -> y, image -> w, image -> h};
	render_copy (image -> data [0], &rect);
}

nil image_free (ptr * data) {
	SDL_DestroyTexture (data [0]);
}

drawable_t * image_new (str path) {
	drawable_t * image = malloc (sizeof (drawable_t));
	SDL_Surface * surface = IMG_Load (path);
	
	if (not surface) {
		LOG_ERR ("IMG_Load: ", (str) SDL_GetError ());
		quit ();
	}
	
	image -> data = malloc (sizeof (SDL_Texture * [1]));
	image -> data [0] = texture_from_surface (surface);
	image -> w = surface -> w;
	image -> h = surface -> h;
	SDL_FreeSurface (surface);
	image -> draw = image_draw;
	image -> free = image_free;
	
	return image;
}

