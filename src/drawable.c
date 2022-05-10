# include "../inc/drawable.h"

nil drawable_set_position (drawable_t * drawable, s16 x, s16 y) {
	drawable -> x = x == CENTER ? (WINDOW.w - drawable -> w) / 2 : x;
	drawable -> y = y == CENTER ? (WINDOW.h - drawable -> h) / 2 : y;
}

nil drawable_free (drawable_t * drawable) {
	drawable -> free (drawable -> data);
	free (drawable -> data);
	free (drawable);
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

nil surface_extract (
	SDL_Surface * surface,
	u16 * width,
	u16 * height,
	SDL_Texture ** texture
) {
	*texture = texture_from_surface (surface);
	*width = surface -> w;
	*height = surface -> h;
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

