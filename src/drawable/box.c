# include "../../inc/drawable/box.h"

nil box_update (box_t * box) {
	box -> x += box -> dx;
	box -> y += box -> dy;
	box -> rect.x = (s32) box -> x;
	box -> rect.y = (s32) box -> y;
}

nil box_draw (drawable_t * drawable) {
	((box_t *) drawable) -> original_draw (drawable);
}

nil box_set_position_ (box_t * box, SDL_FRect r) {
	box -> x = r.x == CENTER ? (WINDOW_W - box -> rect.w) / 2 : r.x;
	box -> y = r.y == CENTER ? (WINDOW_H - box -> rect.h) / 2 : r.y;
}

box_t * box_new_ (drawable_t * drawable, box_new_params params) {
	box_t * box = malloc (sizeof (box_t));
	box -> original_draw = drawable -> draw;
	box -> draw = box_draw;
	box -> data = drawable -> data;
	box -> free = drawable -> free;
	box -> rect = drawable -> rect;
	box -> x = drawable -> rect.x;
	box -> y = drawable -> rect.y;
	box -> dx = params.dx;
	box -> dy = params.dy;
	free (drawable);
	return box;
}

