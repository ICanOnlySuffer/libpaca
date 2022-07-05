# include "../inc/drawable.h"
# include "../inc/vectors.h"
# include <pocha/str.h>

prv vector_t DRAWABLES;

nil drawable_center_x (ptr drawable) {
	((drawable_t *) drawable) -> x = (s16) (
		WINDOW_W - ((drawable_t *) drawable) -> w
	) / 2;
}

nil drawable_center_y (ptr drawable) {
	((drawable_t *) drawable) -> y = (s16) (
		WINDOW_H - ((drawable_t *) drawable) -> h
	) / 2;
}

nil drawable_center (ptr drawable) {
	drawable_center_x (drawable);
	drawable_center_y (drawable);
}

nil drawable_stick_x (ptr drawable) {
	((drawable_t *) drawable) -> x = (s16) (
		WINDOW_W - ((drawable_t *) drawable) -> w
	);
}

nil drawable_stick_y (ptr drawable) {
	((drawable_t *) drawable) -> y = (s16) (
		WINDOW_H - ((drawable_t *) drawable) -> h
	);
}

nil drawable_stick (ptr drawable) {
	drawable_stick_x (drawable);
	drawable_stick_y (drawable);
}

nil drawable_draw (ptr drawable) {
	((drawable_t *) drawable) -> draw ((drawable_t *) drawable);
}

nil drawable_free (ptr drawable) {
	LOG ("DRAWABLES.free %x", drawable);
	if (vec_includes ((vec *) &DRAWABLES, drawable)) {
		((drawable_t *) drawable) -> free (drawable);
		if (run) {
			vector_remove (&DRAWABLES, drawable);
		}
		free (drawable);
	} else {
		ERR ("not DRAWABLES.includes %x", drawable);
	}
}

prv u08 _drawable_quit () {
	LOG ("DRAWABLES.for_each &:free", 0);
	vec_for_all ((vec *) &DRAWABLES, (prc) drawable_free);
	ret true;
}
prv proc_t drawable_quit = {"Drawable_quit", _drawable_quit};

prv u08 _drawable_init () {
	DRAWABLES = vector_new ("DRAWABLES", 4);
	at_quit_push (&drawable_quit);
	ret true;
}
proc_t drawable_init = {"Drawable.init", _drawable_init};

drawable_t * drawable_new (u16 size, drawable_t * params) {
	drawable_t * drawable = malloc (size);
	memcpy (drawable, params, size);
	
	if (drawable -> x == FLT_MAX) {
		drawable_center_x (drawable);
	} else if (drawable -> x == FLT_MIN) {
		drawable_stick_x (drawable);
	}
	if (drawable -> y == FLT_MAX) {
		drawable_center_y (drawable);
	} else if (drawable -> y == FLT_MIN) {
		drawable_stick_y (drawable);
	}
	
	vector_push (&DRAWABLES, (ptr) drawable);
	ret drawable;
}

