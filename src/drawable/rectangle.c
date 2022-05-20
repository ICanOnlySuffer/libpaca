# include "../../inc/drawable/rectangle.h"

nil rectangle_draw_lines (drawable_t * rectangle) {
	render_set_draw_color ((color_t *) rectangle -> data [0]);
	render_draw_rect_lines (&rectangle -> rect);
}

nil rectangle_draw_full (drawable_t * rectangle) {
	render_set_draw_color ((color_t *) rectangle -> data [0]);
	render_draw_rect_full (&rectangle -> rect);
}

nil rectangle_free (ptr * data) {
	// nothing to free
}

drawable_t * rectangle_new_ (color_t * color, frect_t rect) {
	drawable_t * rectangle = malloc (sizeof (drawable_t));
	rectangle -> data = malloc (sizeof (ptr [2]));
	rectangle -> data [0] = color;
	rectangle -> draw = rectangle_draw_full;
	rectangle -> free = rectangle_free;
	rectangle -> rect.w = rect.w;
	rectangle -> rect.h = rect.h;
	drawable_set_position (rectangle, rect.x, rect.y);
	return rectangle;
}

