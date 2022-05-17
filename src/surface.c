# include "../inc/surface.h"

nil surface_extract (
	surface_t * surface,
	texture_t ** texture,
	s32 * w,
	s32 * h
) {
	if (surface) {
		*texture = texture_from_surface (surface);
		*w = surface -> w;
		*h = surface -> h;
		surface_free (surface);
	} else {
		LOG_ERR ("surface_extract: surface == NIL", 0);
		*texture = NIL;
	}
}

nil surface_replace (
	surface_t * surface,
	color_t * to_replace,
	color_t * replacement
) {
	if (not surface) {
		LOG_ERR ("surface_replace: surface == NIL", 0);
		return;
	}
	u08 * pixels = surface -> pixels;
	
	for (u16 i = 0; i < surface -> h; i++) {
		for (u16 j = 0; j < surface -> w; j++) {
			u32 * pixel = (u32 *) (
				pixels +
				i * surface -> pitch +
				j * sizeof (u32)
			);
			if (*pixel == *(u32 *) to_replace) {
				*pixel = *(u32 *) replacement;
			}
		}
	}
}

