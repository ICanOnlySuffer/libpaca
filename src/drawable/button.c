# include "../../inc/drawable/button.h"
# include "../../inc/drawable/text.h"

nil button_draw (button_t * button) {
	render_copy_f (
		button -> texture,
		frect_from_drawable ((ptr) button)
	);
}

nil button_free (button_t * button) {
	texture_free (button -> texture);
}

prv nil button_set_color (button_t * button, color_t * color) {
	if (button -> texture) {
		texture_free (button -> texture);
	}
	surface_extract (
		text_render (button -> string, button -> font, color),
		&button -> texture,
		&button -> w,
		&button -> h
	);
}

nil button_select (button_t * button) {
	button_set_color (button, button -> color [1]);
}

nil button_unselect (button_t * button) {
	button_set_color (button, button -> color [0]);
}

u08 button_press (button_t * button) {
	if (button -> debug) {
		log_proc (&button -> proc);
	}
	ret button -> proc.proc ();
}

button_t * button_new (button_t button) {
	button.texture = NIL;
	button_unselect (&button);
	button.draw = (prc) button_draw;
	button.free = (prc) button_free;
	ret (button_t *) DRAWABLE_NEW (button);
}

