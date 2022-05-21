# include "../inc/drawable.h"
# include "../inc/vectors.h"
# include <pul/str.h>

static vec DRAWABLES;

nil drawable_set_position_ (drawable_t * drawable, point_t point) {
	drawable -> x = point.x == FLT_MAX ?
		(WINDOW_W - drawable -> w) / 2 : point.x;
	drawable -> y = point.y == FLT_MAX ?
		(WINDOW_W - drawable -> h) / 2 : point.y;
}

frect_t frect_from_drawable (drawable_t * drawable) {
	return (frect_t) {
		drawable -> x,
		drawable -> y,
		drawable -> w,
		drawable -> h
	};
}

nil drawable_draw (drawable_t * drawable) {
	drawable -> draw (drawable);
}

nil drawable_free (drawable_t * drawable) {
	LOG ("DRAWABLES.free %u", (u64) drawable);
	if (vec_inc (&DRAWABLES, drawable)) {
		chr buffer [21];
		str_frm_u64 (buffer, (u64) drawable);
		drawable -> free (drawable -> data);
		free (drawable -> data);
		free (drawable);
	} else {
		LOG_ERR ("not DRAWABLES.inc %x", (u64) drawable);
	}
}

nil drawable_quit () {
	str proc = "Drawable.quit";
	proc_init (proc);
	LOG ("DRAWABLES.size == %u", (u64) DRAWABLES.size);
	LOG ("DRAWABLES.for_each &:free", 0);
	vec_for_all (&DRAWABLES, (nil (*) (ptr)) drawable_free);
	LOG ("DRAWABLES.size == %u", (u64) DRAWABLES.size);
	proc_quit (proc);
}

nil drawable_init () {
	str proc = "Drawable.init";
	proc_init (proc);
	DRAWABLES = vector_new ("DRAWABLES", 4);
	at_quit_psh ("Drawable.quit", drawable_quit);
	proc_quit (proc);
}

drawable_t * drawable_new () {
	drawable_t * drawable = malloc (sizeof (drawable_t));
	chr buffer [21];
	str_frm_u64 (buffer, (u64) drawable);
	vector_psh ("DRAWABLES", &DRAWABLES, buffer, drawable);
	return drawable;
}

