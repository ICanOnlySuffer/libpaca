
# ifndef PGE_DRAWABLE_TEXT_H
# define PGE_DRAWABLE_TEXT_H
# include "../drawable.h"
# include "../font.h"

inl surface_t * text_render (
	str string,
	font_t * font,
	color_t * color
) {
	return TTF_RenderText_Blended (font, string, *color);
}

ext nil text_draw (drawable_t * text);
ext nil text_free (ptr * data);
ext nil text_renew (
	drawable_t * text,
	str string,
	font_t * font,
	color_t * color
);

typedef struct {
	struct drawable_t;
	font_t * font;
	color_t * color;
} text_new_params;
ext drawable_t * text_new_ (str string, text_new_params params);
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

