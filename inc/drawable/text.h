
# ifndef PGE_DRAWABLE_TEXT_H
# define PGE_DRAWABLE_TEXT_H
# include "../drawable.h"
# include "../color.h"

stainl SDL_Surface * render_text (str string, u08 color) {
	return TTF_RenderText_Blended (FONT, string, COLORS [color]);
}

extern nil text_draw (drawable_t * text);
extern nil text_free (ptr * data);
extern nil text_renew (drawable_t * text, str string, u08 color);
extern drawable_t * text_new (str string, u08 color);

extern nil shadowed_text_draw (drawable_t * text);
extern nil shadowed_text_free (ptr * data);
extern drawable_t * shadowed_text_new (str string, u08 bg, u08 fg);

# endif // PGE_DRAWABLE_TEXT_H

