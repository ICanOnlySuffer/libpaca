# include "../../inc/drawable/rectangle.h"
# include <pul/put.h>

nil rectangle_draw_lines (drawable_t * rectangle) {
	render_set_draw_color (((struct rectangle *) rectangle) -> color);
	render_draw_frect_lines (frect_from_drawable (rectangle));
}

nil rectangle_draw_full (drawable_t * rectangle) {
	render_set_draw_color (((struct rectangle *) rectangle) -> color);
	render_draw_frect_full (frect_from_drawable (rectangle));
}

nil rectangle_free (drawable_t * rectangle) {
	// nothing to free
}

drawable_t * rectangle_new (struct rectangle rectangle) {
	rectangle.free = rectangle_free;
	ret DRAWABLE_NEW (rectangle);
}

