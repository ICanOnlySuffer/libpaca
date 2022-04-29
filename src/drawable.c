# include "../inc/drawable.h"

nil drawable_center_x (drawable_t * drawable) {
	drawable -> x = (window.width - drawable -> w) / 2;
}

nil drawable_center_y (drawable_t * drawable) {
	drawable -> y = (window.height - drawable -> h) / 2;
}

