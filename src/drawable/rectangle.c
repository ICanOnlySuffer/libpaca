# include "../../inc/drawable/rectangle.h"

nil rectangle_draw_lines (rectangle_t * rectangle) {
	render_set_draw_color (rectangle -> color);
	render_draw_frect_lines (frect_from_drawable (rectangle));
}

nil rectangle_draw_full (rectangle_t * rectangle) {
	render_set_draw_color (rectangle -> color);
	render_draw_frect_full (frect_from_drawable (rectangle));
}

nil rectangle_free (rectangle_t * rectangle) {
	(void) rectangle; // nothing to free
}

rectangle_t * rectangle_new (rectangle_t rectangle) {
	rectangle.free = (prc) rectangle_free;
	ret DRAWABLE_NEW (rectangle);
}

