# include "../../inc/drawable/text.h"

nil text_draw (drawable_t * text) {
	drawable_render (text, 0);
}

nil text_free (ptr * data) {
	SDL_DestroyTexture (data [0]);
}

nil text_renew (
	drawable_t * text,
	str string,
	font_t * font,
	SDL_Color * color
) {
	surface_extract (
		text_render (string, font, color),
		&text -> w,
		&text -> h,
		(texture_t **) &text -> data [0]
	);
}

drawable_t * text_new_ (str string, text_new_params params) {
	drawable_t * text = malloc (sizeof (drawable_t));
	text -> data = malloc (sizeof (ptr));
	text -> draw = text_draw;
	text -> free = text_free;
	text_renew (text, string, params.font, params.color);
	drawable_set_position (text, params.x, params.y);
	
	return text;
}

