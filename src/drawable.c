# include "../inc/drawable.h"

nil drawable_set_position (drawable_t * drawable, s16 x, s16 y) {
	if (x == CENTER) {
		drawable -> rect.x = (WINDOW_W - drawable -> rect.w) / 2;
	} else {
		drawable -> rect.x = x;
	}
	if (y == CENTER) {
		drawable -> rect.y = (WINDOW_H - drawable -> rect.h) / 2;
	} else {
		drawable -> rect.y = y;
	}
}

nil drawable_draw (drawable_t * drawable) {
	drawable -> draw (drawable);
}

nil drawable_free (drawable_t * drawable) {
	drawable -> free (drawable -> data);
	free (drawable -> data);
	free (drawable);
}

