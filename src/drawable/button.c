# include "../../inc/drawable/text.h"

nil button_draw (drawable_t * button) {
	drawable_render (button, 0);
}

nil button_free (ptr * data) {
	// SDL_DestroyTexture (data [0]);
}

drawable_t * button_new (
	str string,
	TTF_Font * font,
	nil (* function) (),
	SDL_Color * color_inactive,
	SDL_Color * color_active
) {
	drawable_t * button = malloc (sizeof (drawable_t));
	drawable_t * text = text_new (string, font, color_inactive);
	
	button -> data = malloc (sizeof (ptr [6]));
	button -> data [0] = text -> data [0];
	button -> data [1] = string;
	button -> data [2] = font;
	button -> data [3] = color_inactive;
	button -> data [4] = color_active;
	button -> data [5] = function;
	button -> w = text -> w;
	button -> h = text -> h;
	
	button -> draw = button_draw;
	button -> free = button_free;
	return button;
}

nil button_select (drawable_t * button) {
	SDL_DestroyTexture (button -> data [0]);
	button -> data [0] = text_new (
		button -> data [1],
		button -> data [2],
		button -> data [4]
	) -> data [0];
}

nil button_unselect (drawable_t * button) {
	SDL_DestroyTexture (button -> data [0]);
	button -> data [0] = text_new (
		button -> data [1],
		button -> data [2],
		button -> data [3]
	) -> data [0];
}

nil button_press (drawable_t * button) {
	((nil (*) ()) button -> data [5]) ();
}

