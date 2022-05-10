
# ifndef PGE_DRAWABLE_BUTTON_H
# define PGE_DRAWABLE_BUTTON_H
# include "../drawable.h"
# include "../font.h"

ext nil button_draw (drawable_t * button);
ext nil button_free (ptr * data);
ext drawable_t * button_new (
	str string,
	TTF_Font * font,
	nil (* function) (),
	SDL_Color * color_inactive,
	SDL_Color * color_active,
	s16 x,
	s16 y
);

ext nil button_press (drawable_t * button);
ext nil button_select (drawable_t * button);
ext nil button_unselect (drawable_t * button);

# endif // PGE_DRAWABLE_BUTTON_H

