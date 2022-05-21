# include "../../inc/drawable/rectangle.h"

nil rectangle_draw_lines (drawable_t * rectangle) {
	render_set_draw_color ((color_t *) rectangle -> data [0]);
	render_draw_frect_lines (frect_from_drawable (rectangle));
}

nil rectangle_draw_full (drawable_t * rectangle) {
	render_set_draw_color ((color_t *) rectangle -> data [0]);
	render_draw_frect_full (frect_from_drawable (rectangle));
}

nil rectangle_free (ptr * data) {
	// nothing to free
}

drawable_t * rectangle_new_ (color_t * color, drawable_t params) {
	drawable_t * rectangle = drawable_new ();
	rectangle -> data = malloc (sizeof (ptr));
	rectangle -> data [0] = color;
	
	rectangle -> free = rectangle_free;
	rectangle -> draw = params.draw;
	rectangle -> w = params.w;
	rectangle -> h = params.h;
	
	rectangle -> dx = params.dx;
	rectangle -> dy = params.dy;
	
	drawable_set_position (rectangle, .x = params.x, .y = params.y);
	return rectangle;
}

