
# ifndef LIBPACA_DRAWABLE_TEXT_H
# define LIBPACA_DRAWABLE_TEXT_H
# include "../drawable.h"
# include "../font.h"

typedef struct {
	DRAWABLE_STRUCT;
	texture_t * texture;
	str string;
	font_t * font;
	color_t * color;
} text_t;

inl surface_t * text_render (
	str string,
	font_t * font,
	color_t * color
) {
	ret TTF_RenderText_Blended (font, string, *color);
}

ext nil text_draw (text_t * text);
ext nil text_free (text_t * text);
ext nil text_renew (text_t * text);

ext text_t * text_new (text_t text);
# define TEXT_NEW(string_, ...) \
	text_new ( \
		(text_t) { \
			DRAWABLE_DEFAULT, \
			.font = FONT_DEFAULT, \
			.string = string_, \
			__VA_ARGS__ \
		} \
	)

# endif // LIBPACA_DRAWABLE_TEXT_H

