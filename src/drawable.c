# include "../inc/drawable.h"

nil drawable_center_x (drawable_t * drawable) {
	drawable -> x = (window.width - drawable -> w) / 2;
}

nil drawable_center_y (drawable_t * drawable) {
	drawable -> y = (window.height - drawable -> h) / 2;
}

nil drawable_free (drawable_t * drawable) {
	drawable -> free (drawable -> data);
	free (drawable -> data);
	free (drawable);;
}

nil drawable_free_vec (vec * drawables) {
	for (u08 i = 0; i < drawables -> size; i++) {
		drawable_free (drawables -> items [i]);
	}
}

nil drawable_free_arr (u08 length, drawable_t * drawables []) {
	for (u08 i = 0; i < length; i++) {
		drawable_free (drawables [i]);
	}
}

nil drawable_extract (
	drawable_t * drawable,
	u08 index,
	SDL_Surface * surface
) {
	drawable -> data [index] = texture_from_surface (surface);
	drawable -> w = surface -> w;
	drawable -> h = surface -> h;
	SDL_FreeSurface (surface);
}

nil drawable_render (drawable_t * drawable, u08 index) {
	SDL_Rect rect = {
		drawable -> x,
		drawable -> y,
		drawable -> w,
		drawable -> h
	};
	render_copy (drawable -> data [index], &rect);
}

