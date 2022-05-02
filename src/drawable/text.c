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
	text -> data = malloc (sizeof (SDL_Texture * [1]));
	drawable_extract (text, 0, text_render (string, font, color));
}

drawable_t * text_new (
	str string,
	TTF_Font * font,
	SDL_Color * color
) {
	drawable_t * text = malloc (sizeof (drawable_t));
	text_renew (text, string, font, color);
	text -> draw = text_draw;
	text -> free = text_free;
	return text;
}

