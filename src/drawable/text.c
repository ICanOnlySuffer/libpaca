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

nil text_renew (
	struct text * text,
	str string,
	color_t * color,
	font_t * font
) {
	text -> color = color;
	text -> font = font;
	
	surface_extract (
		text_render (string, font, color),
		&text -> texture,
		&text -> w,
		&text -> h
	);
}

drawable_t * text_new (str string, struct text text) {
	text_renew (&text, string, text.color, text.font);
	text.free = text_free;
	text.draw = text_draw;
	ret DRAWABLE_NEW (text);
}

