
# ifndef PGE_DRAWABLE_H
# define PGE_DRAWABLE_H
# include <SDL2/SDL_render.h>
# include <pul/vec.h>
# include "renderer.h"

typedef SDL_FPoint point_t;

typedef struct drawable_t {
	ptr * data;
	f32 x;
	f32 y;
	f32 w;
	f32 h;
	f32 dx;
	f32 dy;
	nil (* draw) (struct drawable_t * drawable);
	nil (* free) (ptr * data);
} drawable_t;

inl f32 drawable_v (drawable_t * drawable) {
	return drawable -> y + drawable -> h / 2;
}
inl f32 drawable_h (drawable_t * drawable) {
	return drawable -> x + drawable -> w / 2;
}
inl f32 drawable_s (drawable_t * drawable) {
	return drawable -> y + drawable -> h;
}
inl f32 drawable_e (drawable_t * drawable) {
	return drawable -> x + drawable -> w;
}
inl f32 drawable_n (drawable_t * drawable) {
	return drawable -> y;
}
inl f32 drawable_w (drawable_t * drawable) {
	return drawable -> x;
}

ext frect_t frect_from_drawable (drawable_t * drawable);

inl nil drawable_update (drawable_t * drawable) {
	drawable -> x += drawable -> dx;
	drawable -> y += drawable -> dy;
}

ext nil drawable_set_position_ (drawable_t * drawable, point_t point);
# define drawable_set_position(drawable_, ...) \
	drawable_set_position_ ( \
		drawable_, \
		(point_t) { \
			.x = drawable_ -> x, \
			.y = drawable_ -> y, \
			__VA_ARGS__ \
		} \
	)

ext nil drawable_draw (drawable_t * drawable);
# define DRAWABLE_DRAW(...) \
	arr_for_all ( \
		(ARR_LEN (((drawable_t * []) {__VA_ARGS__}))), \
		(ptr []) {__VA_ARGS__}, \
		(nil (*) (ptr)) drawable_draw \
	)

ext nil drawable_free (drawable_t * drawable);
# define DRAWABLE_FREE(...) \
	arr_for_all ( \
		(ARR_LEN (((drawable_t * []) {__VA_ARGS__}))), \
		(ptr []) {__VA_ARGS__}, \
		(nil (*) (ptr)) drawable_free \
	)

ext nil drawable_quit ();
ext nil drawable_init ();

ext drawable_t * drawable_new ();

# endif // PGE_DRAWABLE_H

