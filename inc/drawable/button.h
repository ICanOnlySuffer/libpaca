
# ifndef PGE_DRAWABLE_BUTTON_H
# define PGE_DRAWABLE_BUTTON_H
# include "../drawable.h"
# include "../color.h"

extern nil button_draw (drawable_t * button);
extern nil button_free (ptr * data);
extern drawable_t * button_new (
	str string,
	TTF_Font * font,
	nil (* function) (),
	SDL_Color * color_inactive,
	SDL_Color * color_active
);

extern nil button_press (drawable_t * button);
extern nil button_select (drawable_t * button);
extern nil button_unselect (drawable_t * button);

# endif // PGE_DRAWABLE_BUTTON_H

