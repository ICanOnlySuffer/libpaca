
# ifndef PGE_DRAWABLE_H
# define PGE_DRAWABLE_H
# include <SDL2/SDL_render.h>
# include <pul/vec.h>
# include "renderer.h"

typedef SDL_FPoint point_t;

typedef struct drawable_t {
	f32 x;
	f32 y;
	f32 w;
	f32 h;
	f32 dx;
	f32 dy;
	nil (* draw) (struct drawable_t * drawable);
	nil (* free) (struct drawable_t * drawable);
} drawable_t;

inl f32 drawable_v (drawable_t * drawable) {
	ret drawable -> y + drawable -> h / 2;
}
inl f32 drawable_h (drawable_t * drawable) {
	ret drawable -> x + drawable -> w / 2;
}
inl f32 drawable_s (drawable_t * drawable) {
	ret drawable -> y + drawable -> h;
}
inl f32 drawable_e (drawable_t * drawable) {
	ret drawable -> x + drawable -> w;
}
inl f32 drawable_n (drawable_t * drawable) {
	ret drawable -> y;
}
inl f32 drawable_w (drawable_t * drawable) {
	ret drawable -> x;
}

inl frect_t frect_from_drawable (drawable_t * drawable) {
	ret (frect_t) {
		drawable -> x,
		drawable -> y,
		drawable -> w,
		drawable -> h
	};
}

inl nil drawable_center_x (drawable_t * drawable) {
	drawable -> x = (WINDOW_W - drawable -> w) / 2;
}

inl nil drawable_center_y (drawable_t * drawable) {
	drawable -> y = (WINDOW_H - drawable -> h) / 2;
}

inl nil drawable_update (drawable_t * drawable) {
	drawable -> x += drawable -> dx;
	drawable -> y += drawable -> dy;
}

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

ext drawable_t * drawable_new (u16 size, drawable_t * params);

# define DRAWABLE_NEW(params_) \
	drawable_new (sizeof (params_), (drawable_t *) &params_)

# define DRAWABLE_DEFAULT \
	.x = 0, \
	.y = 0, \
	.dy = 0, \
	.dx = 0

# endif // PGE_DRAWABLE_H

