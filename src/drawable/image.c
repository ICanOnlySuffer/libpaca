# include "../../inc/drawable/image.h"

nil image_draw (image_t * image) {
	render_copy_f (image -> texture, frect_from_drawable (image));
}

nil image_free (image_t * image) {
	texture_free (image -> texture);
}

surface_t * image_load (str path) {
	surface_t * surface = IMG_Load (path);
	if (not surface) {
		ERR ("image_load: %s", SDL_GetError ());
	}
	ret surface;
}

texture_t * image_load_texture (str path) {
	surface_t * surface = image_load (path);
	if (not surface) {
		ERR ("image_load_texture: surface == NIL");
		ret NIL;
	}
	texture_t * texture = texture_from_surface (surface);
	surface_free (surface);
	ret texture;
}

image_t * image_new (str path, image_t image) {
	surface_extract (
		image_load (path),
		&image.texture,
		&image.w,
		&image.h
	);
	
	image.draw = (prc) image_draw;
	image.free = (prc) image_free;
	
	ret DRAWABLE_NEW (image);
}

