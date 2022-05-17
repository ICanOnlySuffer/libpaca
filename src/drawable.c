# include "../inc/drawable.h"

nil drawable_set_position (drawable_t * drawable, s16 x, s16 y) {
	if (x == DRAWABLE_CENTER) {
		drawable -> rect.x = (WINDOW.w - drawable -> rect.w) / 2;
	} else {
		drawable -> rect.x = x;
	}
	if (y == DRAWABLE_CENTER) {
		drawable -> rect.y = (WINDOW.h - drawable -> rect.h) / 2;
	} else {
		drawable -> rect.y = y;
	}
}

nil drawable_free (drawable_t * drawable) {
	drawable -> free (drawable -> data);
	free (drawable -> data);
	free (drawable);
}

