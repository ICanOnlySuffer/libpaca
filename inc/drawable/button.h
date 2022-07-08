
# ifndef LIBPACA_DRAWABLE_BUTTON_H
# define LIBPACA_DRAWABLE_BUTTON_H
# include "../drawable.h"
# include "../font.h"

typedef struct {
	DRAWABLE_STRUCT;
	texture_t * texture;
	str string;
	color_t * color [2];
	font_t * font;
	proc_t proc;
	u08 debug;
} button_t;

ext nil button_draw (button_t * button);
ext nil button_free (button_t * button);
ext u08 button_press (button_t * button);
ext nil button_select (button_t * button);
ext nil button_unselect (button_t * button);

ext button_t * button_new (button_t button);
# define BUTTON_NEW(string_, ...) \
	button_new ( \
		(button_t) { \
			DRAWABLE_DEFAULT, \
			.font = FONT_DEFAULT, \
			.string = string_, \
			.debug = false, \
			__VA_ARGS__ \
		} \
	)

# endif // LIBPACA_DRAWABLE_BUTTON_H

