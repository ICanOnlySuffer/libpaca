# include "../../inc/drawable/button.h"
# include "../../inc/drawable/text.h"

nil button_draw (drawable_t * button) {
	render_copy_f (button -> data [0], frect_from_drawable (button));
}

nil button_free (ptr * data) {
	SDL_DestroyTexture (data [0]);
}

drawable_t * button_new_ (str string, button_new_params params) {
	drawable_t * button = drawable_new ();
	
	button -> data = malloc (sizeof (ptr [6]));
	button -> data [0] = NIL;
	button -> data [1] = string;
	button -> data [2] = params.font;
	button -> data [3] = params.color_inactive;
	button -> data [4] = params.color_active;
	button -> data [5] = params.function;
	button -> draw = button_draw;
	button -> free = button_free;
	
	button_unselect (button);
	drawable_set_position (button, .x = params.x, .y = params.y);
	
	return button;
}

static nil button_change_color (drawable_t * button, u08 index) {
	if (button -> data [0]) {
		texture_free (button -> data [0]);
	}
	surface_extract (
		text_render (
			button -> data [1],
			button -> data [2],
			button -> data [index]
		),
		(texture_t **) &button -> data [0],
		&button -> w,
		&button -> h
	);
}

nil button_select (drawable_t * button) {
	button_change_color (button, 4);
}

nil button_unselect (drawable_t * button) {
	button_change_color (button, 3);
}

nil button_press (drawable_t * button) {
	((nil (*) ()) button -> data [5]) ();
}

