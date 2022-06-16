
# ifndef LIBPACA_DRAWABLE_H
# define LIBPACA_DRAWABLE_H
# include <SDL2/SDL_render.h>
# include <pocha/vec.h>
# include "renderer.h"
# include "proc.h"

typedef SDL_FPoint point_t;

# define DRAWABLE_STRUCT \
	f32 x; \
	f32 y; \
	f32 w; \
	f32 h; \
	f32 dx; \
	f32 dy; \
	nil (* draw) (struct drawable_t * drawable); \
	nil (* free) (struct drawable_t * drawable)

typedef struct drawable_t {
	DRAWABLE_STRUCT;
} drawable_t;

# define DRAWABLE_V(drawable_) (drawable_ -> y + drawable_ -> h / 2)
# define DRAWABLE_H(drawable_) (drawable_ -> x + drawable_ -> w / 2)
# define DRAWABLE_S(drawable_) (drawable_ -> y + drawable_ -> h)
# define DRAWABLE_E(drawable_) (drawable_ -> x + drawable_ -> w)
# define DRAWABLE_N(drawable_) (drawable_ -> y)
# define DRAWABLE_W(drawable_) (drawable_ -> x)

inl frect_t frect_from_drawable (ptr drawable) {
	ret (frect_t) {
		((drawable_t *) drawable) -> x,
		((drawable_t *) drawable) -> y,
		((drawable_t *) drawable) -> w,
		((drawable_t *) drawable) -> h
	};
}

inl nil drawable_center_x (ptr drawable) {
	((drawable_t *) drawable) -> x = (
		WINDOW_W - ((drawable_t *) drawable) -> w
	) / 2;
}

inl nil drawable_center_y (ptr drawable) {
	((drawable_t *) drawable) -> y = (
		WINDOW_H - ((drawable_t *) drawable) -> h
	) / 2;
}

inl nil drawable_center (ptr drawable) {
	drawable_center_x (drawable);
	drawable_center_y (drawable);
}

inl nil drawable_update (ptr drawable) {
	((drawable_t *) drawable) -> x += ((drawable_t *) drawable) -> dx;
	((drawable_t *) drawable) -> y += ((drawable_t *) drawable) -> dy;
}

ext nil drawable_draw (ptr drawable);
# define DRAWABLE_DRAW(...) \
	arr_for_all ( \
		ARR_LEN ((ptr []) {__VA_ARGS__}), \
		(ptr []) {__VA_ARGS__}, \
		(nil (*) (ptr)) drawable_draw \
	)

ext nil drawable_free (drawable_t * drawable);
# define DRAWABLE_FREE(...) \
	arr_for_all ( \
		ARR_LEN ((ptr []) {__VA_ARGS__}), \
		(ptr []) {__VA_ARGS__}, \
		(nil (*) (ptr)) drawable_free \
	)

ext proc_t drawable_init;

ext drawable_t * drawable_new (u16 size, drawable_t * params);

# define DRAWABLE_NEW(params_) \
	drawable_new (sizeof (params_), (drawable_t *) &params_)

# define DRAWABLE_DEFAULT \
	.x = 0, \
	.y = 0, \
	.dy = 0, \
	.dx = 0

# endif // LIBPACA_DRAWABLE_H

