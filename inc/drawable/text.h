
# ifndef PGE_DRAWABLE_TEXT_H
# define PGE_DRAWABLE_TEXT_H
# include "../drawable.h"
# include "../font.h"

struct text {
	struct drawable_t;
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

# endif // PGE_DRAWABLE_TEXT_H

