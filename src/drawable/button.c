# include "../../inc/drawable/text.h"

nil button_draw (drawable_t * button) {
	drawable_render (button, 0);
}

nil button_free (ptr * data) {
	SDL_DestroyTexture (data [0]);
}

drawable_t * button_new (
	str string,
	TTF_Font * font,
	nil (* function) (),
	SDL_Color * color_inactive,
	SDL_Color * color_active,
	s16 x,
	s16 y
) {
	drawable_t * button = malloc (sizeof (drawable_t));
	
	button -> data = malloc (sizeof (ptr [6]));
	button -> data [1] = string;
	button -> data [2] = font;
	button -> data [3] = color_inactive;
	button -> data [4] = color_active;
	button -> data [5] = function;
	
	surface_extract (
		text_render (string, font, color_inactive),
		&button -> w,
		&button -> h,
		(SDL_Texture **) &button -> data [0]
	);
	// unselect
	drawable_set_position (button, x, y);
	button -> draw = button_draw;
	button -> free = button_free;
	return button;
}

nil button_select (drawable_t * button) {
	u16 buffer;
	SDL_DestroyTexture (button -> data [0]);
	surface_extract (
		text_render (
			button -> data [1],
			button -> data [2],
			button -> data [4]
		),
		&buffer,
		&buffer,
		(SDL_Texture **) &button -> data [0]
	);
}

nil button_unselect (drawable_t * button) {
	u16 buffer;
	SDL_DestroyTexture (button -> data [0]);
	surface_extract (
		text_render (
			button -> data [1],
			button -> data [2],
			button -> data [3]
		),
		&buffer,
		&buffer,
		(SDL_Texture **) &button -> data [0]
	);
}

nil button_press (drawable_t * button) {
	((nil (*) ()) button -> data [5]) ();
}

