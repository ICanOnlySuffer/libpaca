# include "../inc/drawable.h"
# include "../inc/vectors.h"
# include <pul/str.h>

static vector_t DRAWABLES;

nil drawable_draw (drawable_t * drawable) {
	drawable -> draw (drawable);
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

static nil drawable_quit_proc () {
	str proc = "Drawable.quit";
	proc_init (proc);
	LOG ("DRAWABLES.for_each &:free", 0);
	vec_for_all ((vec *) &DRAWABLES, (prc) drawable_free);
	proc_quit (proc);
}

static proc_t drawable_quit = {
	.proc = (prc) drawable_quit_proc,
	.name = "Drawable.quit"
};

nil drawable_init () {
	str proc = "Drawable.init";
	proc_init (proc);
	DRAWABLES = vector_new ("DRAWABLES", 4);
	at_quit_psh (&drawable_quit);
	proc_quit (proc);
}

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

