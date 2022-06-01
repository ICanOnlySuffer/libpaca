# include "../../inc/drawable/button.h"
# include "../../inc/drawable/text.h"

nil button_draw (drawable_t * button) {
	render_copy_f (
		((struct button *) button) -> texture,
		frect_from_drawable (button)
	);
}

nil button_free (drawable_t * button) {
	texture_free (((struct button *) button) -> texture);
}

static nil button_set_color (struct button * button, color_t color) {
	if (button -> texture) {
		texture_free (button -> texture);
	}
	surface_extract (
		text_render (button -> string, button -> font, &color),
		&button -> texture,
		&button -> w,
		&button -> h
	);
}

nil button_select (struct button * button) {
	button_set_color (button, *button -> color [1]);
}

nil button_unselect (struct button * button) {
	button_set_color (button, *button -> color [0]);
}

nil button_press (struct button * button) {
	((struct button *) button) -> function ();
}

struct button * button_new (struct button button) {
	button.texture = NIL;
	button_unselect (&button);
	button.draw = button_draw;
	button.free = button_free;
	ret (struct button *) DRAWABLE_NEW (button);
}

