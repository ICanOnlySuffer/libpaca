# include "../../inc/drawable/button_list.h"

nil button_list_draw (button_list_t * button_list) {
	for (u08 i = 0; i < button_list -> n_buttons; i++) {
		button_draw (&(button_list -> buttons [i]));
	}
}

nil button_list_free (button_list_t * button_list) {
	for (u08 i = 0; i < button_list -> n_buttons; i++) {
		button_free (&(button_list -> buttons [i]));
	}
}

nil button_list_next (button_list_t * button_list) {
	button_unselect (&button_list -> buttons [button_list -> index]);
	if (button_list -> index == button_list -> n_buttons - 1) {
		button_list -> index = 0;
	} else {
		button_list -> index++;
	}
	button_select (&button_list -> buttons [button_list -> index]);
}

nil button_list_previous (button_list_t * button_list) {
	button_unselect (&button_list -> buttons [button_list -> index]);
	if (button_list -> index) {
		button_list -> index--;
	} else {
		button_list -> index = button_list -> n_buttons - 1;
	}
	button_select (&button_list -> buttons [button_list -> index]);
}

nil button_list_press (button_list_t * button_list) {
	button_press (&button_list -> buttons [button_list -> index]);
}

nil button_list_row (
	button_list_t * button_list,
	f32 x,
	f32 y,
	f32 separation
) {
	for (u08 i = 0; i < button_list -> n_buttons; i++) {
		button_list -> buttons [i].y = y;
		drawable_update_pos (
			(drawable_t *)&(button_list -> buttons [i])
		);
		button_list -> buttons [i].x = x + separation * i;
	}
}

nil button_list_column (
	button_list_t * button_list,
	f32 x,
	f32 y,
	f32 separation
) {
	for (u08 i = 0; i < button_list -> n_buttons; i++) {
		button_list -> buttons [i].x = x;
		drawable_update_pos (&button_list -> buttons [i]);
		button_list -> buttons [i].y = y + separation * i;
	}
}

button_list_t * button_list_new (button_list_params_t params) {
	button_list_t button_list = {
		.buttons = malloc (sizeof (button_t) * params.n_buttons),
		.n_buttons = params.n_buttons,
		.index = 0,
		.draw = (prc) button_list_draw,
		.free = (prc) button_list_free
	};
	
	for (u08 i = 0; i < params.n_buttons; i++) {
		button_list.buttons [i] = (button_t) {
			.string = params.procs [i].name,
			.font = params.font,
			.proc = params.procs [i],
			.texture = NIL
		};
		button_list.buttons [i].color [0] = params.color [0];
		button_list.buttons [i].color [1] = params.color [1];
		button_unselect (&(button_list.buttons [i]));
	}
	button_select (button_list.buttons);
	
	ret DRAWABLE_NEW (button_list);
}

