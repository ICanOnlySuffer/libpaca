# include "../inc/drawable.h"

nil drawable_center_x (drawable_t * drawable) {
	drawable -> x = (window.width - drawable -> w) / 2;
}

nil drawable_center_y (drawable_t * drawable) {
	drawable -> y = (window.height - drawable -> h) / 2;
}

nil drawable_free_vec (vec * drawables) {
	for (u16 i = 0; i < drawables -> size; i++) {
		drawable_free (drawables -> items [i]);
	}
}

