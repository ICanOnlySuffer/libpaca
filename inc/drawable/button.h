
# ifndef PGE_DRAWABLE_BUTTON_H
# define PGE_DRAWABLE_BUTTON_H
# include "../drawable.h"
# include "../font.h"

struct button {
	struct drawable_t;
	texture_t * texture;
	str string;
	color_t * color_active;
	color_t * color_inactive;
	font_t * font;
	nil (* function) ();
};

ext nil button_draw (drawable_t * button);
ext nil button_free (drawable_t * button);
ext nil button_press (struct button * button);
ext nil button_select (struct button * button);
ext nil button_unselect (struct button * button);

ext drawable_t * button_new (struct button button);
# define BUTTON_NEW(string_, ...) \
	button_new ( \
		(struct button) { \
			DRAWABLE_DEFAULT, \
			__VA_ARGS__ \
		} \
	)

# endif // PGE_DRAWABLE_BUTTON_H

