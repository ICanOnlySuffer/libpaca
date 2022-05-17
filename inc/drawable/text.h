
# ifndef PGE_DRAWABLE_TEXT_H
# define PGE_DRAWABLE_TEXT_H
# include "../drawable.h"
# include "../font.h"

inl SDL_Surface * text_render (
	str string,
	TTF_Font * font,
	SDL_Color * color
) {
	return TTF_RenderText_Blended (font, string, *color);
}

ext nil text_draw (drawable_t * text);
ext nil text_free (ptr * data);
ext nil text_renew (
	drawable_t * text,
	str string,
	TTF_Font * font,
	SDL_Color * color
);

typedef struct {
	font_t * font;
	SDL_Color * color;
	s16 x;
	s16 y;
} text_new_params;
ext drawable_t * text_new_ (str string, text_new_params);
# define text_new(string_, ...) \
	text_new_ ( \
		string_, \
		(text_new_params) { \
			.x = 0, \
			.y = 0, \
			__VA_ARGS__ \
		} \
	)

# endif // PGE_DRAWABLE_TEXT_H

