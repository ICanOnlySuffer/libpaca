
# ifndef PGE_DRAWABLE_TEXT_H
# define PGE_DRAWABLE_TEXT_H
# include "../drawable.h"
# include "../color.h"
# include "../font.h"

stainl SDL_Surface * text_render (
	str string,
	TTF_Font * font,
	SDL_Color * color
) {
	return TTF_RenderText_Blended (font, string, *color);
}

extern nil text_draw (drawable_t * text);
extern nil text_free (ptr * data);
extern nil text_renew (
	drawable_t * text,
	str string,
	TTF_Font * font,
	SDL_Color * color
);
extern drawable_t * text_new (
	str string,
	TTF_Font * font,
	SDL_Color * color
);

# endif // PGE_DRAWABLE_TEXT_H

