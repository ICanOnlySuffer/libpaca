# include "../../inc/drawable/image.h"

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

nil image_draw (drawable_t * image) {
	render_copy_f (
		((struct image *) image) -> texture,
		frect_from_drawable (image)
	);
}

nil image_free (drawable_t * image) {
	texture_free (((struct image *) image) -> texture);
}

struct image * image_new (str path, struct image image) {
	surface_extract (
		image_load (path),
		&image.texture,
		&image.w,
		&image.h
	);
	ret (struct image *) DRAWABLE_NEW (image);
}

