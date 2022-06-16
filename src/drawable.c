# include "../inc/drawable.h"
# include "../inc/vectors.h"
# include <pocha/str.h>

static vector_t DRAWABLES;

nil drawable_draw (ptr drawable) {
	((drawable_t *) drawable) -> draw ((drawable_t *) drawable);
}

nil drawable_free (drawable_t * drawable) {
	LOG ("DRAWABLES.free %x", (u64) drawable);
	if (vec_inc ((vec *) &DRAWABLES, drawable)) {
		drawable -> free (drawable);
		if (run) {
			vector_rmv (&DRAWABLES, drawable);
		}
		free (drawable);
	} else {
		LOG_ERR ("not DRAWABLES.inc %x", (u64) drawable);
	}
}

static u08 _drawable_quit () {
	LOG ("DRAWABLES.for_each &:free", 0);
	vec_for_all ((vec *) &DRAWABLES, (prc) drawable_free);
	ret true;
}
static proc_t drawable_quit = {"Drawable_quit", _drawable_quit};

static u08 _drawable_init () {
	DRAWABLES = vector_new ("DRAWABLES", 4);
	at_quit_psh (&drawable_quit);
	ret true;
}
proc_t drawable_init = {"Drawable.init", _drawable_init};

drawable_t * drawable_new (u16 size, drawable_t * params) {
	drawable_t * drawable = malloc (size);
	memcpy (drawable, params, size);
	if (drawable -> x == FLT_MAX) {
		drawable_center_x (drawable);
	}
	if (drawable -> y == FLT_MAX) {
		drawable_center_y (drawable);
	}
	vector_psh (&DRAWABLES, (ptr) drawable);
	ret drawable;
}

