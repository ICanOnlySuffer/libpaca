# include "../../inc/drawable/text.h"

nil text_draw (drawable_t * text) {
	render_copy_f (
		((struct text *) text) -> texture,
		frect_from_drawable (text)
	);
}

nil text_free (drawable_t * text) {
	texture_free (((struct text *) text) -> texture);
}

nil text_renew (struct text * text) {
	surface_extract (
		text_render (text -> string, text -> font, text -> color),
		&text -> texture,
		&text -> w,
		&text -> h
	);
}

struct text * text_new (struct text text) {
	text_renew (&text);
	text.free = text_free;
	text.draw = text_draw;
	ret (struct text *) DRAWABLE_NEW (text);
}

