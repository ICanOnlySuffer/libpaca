# include "../../inc/drawable/text.h"

nil text_draw (drawable_t * text) {
	render_copy_f (text -> data [0], frect_from_drawable (text));
}

nil text_free (ptr * data) {
	texture_free (data [0]);
}

nil text_renew (
	drawable_t * text,
	str string,
	font_t * font,
	color_t * color
) {
	surface_extract (
		text_render (string, font, color),
		(texture_t **) &text -> data [0],
		&text -> w,
		&text -> h
	);
}

drawable_t * text_new_ (str string, text_new_params params) {
	drawable_t * text = drawable_new ();
	text -> data = malloc (sizeof (ptr));
	text -> draw = text_draw;
	text -> free = text_free;
	text_renew (text, string, params.font, params.color);
	drawable_set_position (text, .x = params.x, .y = params.y);
	
	return text;
}

