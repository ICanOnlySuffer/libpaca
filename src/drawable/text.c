# include "../../inc/drawable/text.h"

nil text_draw (text_t * text) {
	render_copy_f (text -> texture, frect_from_drawable (text));
}

nil text_free (text_t * text) {
	texture_free (text -> texture);
}

nil text_renew (text_t * text) {
	surface_extract (
		text_render (text -> string, text -> font, text -> color),
		&text -> texture,
		&text -> w,
		&text -> h
	);
}

text_t * text_new (text_t text) {
	text_renew (&text);
	text.free = (prc) text_free;
	text.draw = (prc) text_draw;
	ret DRAWABLE_NEW (text);
}

