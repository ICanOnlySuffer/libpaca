
# ifndef PGE_DRAWABLE_BUTTON_H
# define PGE_DRAWABLE_BUTTON_H
# include "../drawable.h"
# include "../font.h"

ext nil button_draw (drawable_t * button);
ext nil button_free (ptr * data);
ext nil button_press (drawable_t * button);
ext nil button_select (drawable_t * button);
ext nil button_unselect (drawable_t * button);

typedef struct {
	font_t * font;
	SDL_Color * color_inactive;
	SDL_Color * color_active;
	nil (* function) ();
	s16 x;
	s16 y;
} button_new_params;
ext drawable_t * button_new_ (str string, button_new_params);
# define button_new(string_, ...) \
	button_new_ ( \
		string_, \
		(button_new_params) { \
			.x = 0, \
			.y = 0, \
			__VA_ARGS__ \
		} \
	)

# endif // PGE_DRAWABLE_BUTTON_H

