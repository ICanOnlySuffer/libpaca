# include "../../inc/drawable/image.h"

surface_t * image_load (str path) {
	surface_t * surface = IMG_Load (path);
	if (not surface) {
		LOG_ERR ("image_load: %s", (u64) SDL_GetError ());
	}
	return surface;
}

texture_t * image_load_texture (str path) {
	surface_t * surface = image_load (path);
	if (not surface) {
		LOG_ERR ("image_load_texture: surface == NIL", 0);
		return NIL;
	}
	texture_t * texture = texture_from_surface (surface);
	surface_free (surface);
	return texture;
}

nil image_draw (drawable_t * image) {
	render_copy_f (image -> data [0], frect_from_drawable (image));
}

nil image_free (ptr * data) {
	texture_free (data [0]);
}

drawable_t * image_new_ (str path, drawable_t params) {
	drawable_t * image = drawable_new ();
	image -> data = malloc (sizeof (ptr));
	
	image -> draw = image_draw;
	image -> free = image_free;
	image -> dx = params.dx;
	image -> dy = params.dy;
	
	surface_extract (
		image_load (path),
		(texture_t **) &image -> data [0],
		&image -> w,
		&image -> h
	);
	drawable_set_position (image, .x = params.x, .y = params.y);
	
	return image;
}

