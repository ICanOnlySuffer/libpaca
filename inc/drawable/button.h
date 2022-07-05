
# ifndef LIBPACA_DRAWABLE_BUTTON_H
# define LIBPACA_DRAWABLE_BUTTON_H
# include "../drawable.h"
# include "../font.h"

struct button {
	DRAWABLE_STRUCT;
	texture_t * texture;
	str string;
	color_t * color [2];
	font_t * font;
	proc_t proc;
	u08 debug;
};

ext nil button_draw (drawable_t * button);
ext nil button_free (drawable_t * button);
ext u08 button_press (struct button * button);
ext nil button_select (struct button * button);
ext nil button_unselect (struct button * button);

ext struct button * button_new (struct button button);
# define BUTTON_NEW(string_, ...) \
	button_new ( \
		(struct button) { \
			DRAWABLE_DEFAULT, \
			.font = FONT_DEFAULT, \
			.string = string_, \
			.debug = false, \
			__VA_ARGS__ \
		} \
	)

# endif // LIBPACA_DRAWABLE_BUTTON_H

