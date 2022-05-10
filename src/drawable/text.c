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
	TTF_Font * font,
	SDL_Color * color
) {
	text -> data = malloc (sizeof (ptr));
	surface_extract (
		text_render (string, font, color),
		&text -> w,
		&text -> h,
		(SDL_Texture **) &text -> data [0]
	);
}

drawable_t * text_new (
	str string,
	TTF_Font * font,
	SDL_Color * color,
	s16 x,
	s16 y
) {
	drawable_t * text = malloc (sizeof (drawable_t));
	text_renew (text, string, font, color);
	text -> draw = text_draw;
	text -> free = text_free;
	drawable_set_position (text, x, y);
	
	return text;
}

