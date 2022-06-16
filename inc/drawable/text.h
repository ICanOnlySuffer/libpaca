
# ifndef LIBPACA_DRAWABLE_TEXT_H
# define LIBPACA_DRAWABLE_TEXT_H
# include "../drawable.h"
# include "../font.h"

struct text {
	DRAWABLE_STRUCT;
	texture_t * texture;
	str string;
	font_t * font;
	color_t * color;
};

inl surface_t * text_render (
	str string,
	font_t * font,
	color_t * color
) {
	ret TTF_RenderText_Blended (font, string, *color);
}

ext nil text_draw (drawable_t * text);
ext nil text_free (drawable_t * text);
ext nil text_renew (struct text * text);

ext struct text * text_new (struct text text);
# define TEXT_NEW(string_, ...) \
	text_new ( \
		(struct text) { \
			DRAWABLE_DEFAULT, \
			.font = FONT_DEFAULT, \
			.string = string_, \
			__VA_ARGS__ \
		} \
	)

# endif // LIBPACA_DRAWABLE_TEXT_H

