
# ifndef LIBPACA_BUTTON_LIST_H
# define LIBPACA_BUTTON_LIST_H
# include "../color.h"
# include "../proc.h"
# include "button.h"

typedef struct {
	DRAWABLE_STRUCT;
	button_t * buttons;
	u08 n_buttons;
	u08 index;
} button_list_t;

ext nil button_list_draw (button_list_t * button_list);
ext nil button_list_free (button_list_t * button_list);

ext nil button_list_next (button_list_t * button_list);
ext nil button_list_previous (button_list_t * button_list);

ext nil button_list_press (button_list_t * button_list);

ext nil button_list_row (
	button_list_t * button_list,
	f32 x,
	f32 y,
	f32 separation
);
ext nil button_list_column (
	button_list_t * button_list,
	f32 x,
	f32 y,
	f32 separation
);

typedef struct {
	u08 n_buttons;
	proc_t * procs;
	color_t * color [2];
	font_t * font;
} button_list_params_t;

ext button_list_t * button_list_new (button_list_params_t params);

# define BUTTON_LIST_NEW(procs_, ...) \
	button_list_new ( \
		(button_list_params_t) { \
			.n_buttons = ARR_LEN (procs_), \
			.procs = procs_, \
			.font = FONT_DEFAULT, \
			.color = {COLORS [1], COLORS [2]}, \
			__VA_ARGS__ \
		} \
	)

# endif // LIBPACA_BUTTON_LIST_H

