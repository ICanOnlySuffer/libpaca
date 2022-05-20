
# ifndef PGE_BOX_H
# define PGE_BOX_H
# include "../drawable.h"

typedef struct {
	drawable_t; // anonymous struct
	f32 x;
	f32 y;
	f32 dx;
	f32 dy;
	nil (*original_draw) (drawable_t * drawable);
} box_t;

inl f32 box_v (box_t * box) {
	return box -> y + box -> rect.h / 2;
}
inl f32 box_h (box_t * box) {
	return box -> x + box -> rect.w / 2;
}
inl f32 box_s (box_t * box) {
	return box -> y + box -> rect.h;
}
inl f32 box_e (box_t * box) {
	return box -> x + box -> rect.w;
}
inl f32 box_n (box_t * box) {
	return box -> y;
}
inl f32 box_w (box_t * box) {
	return box -> x;
}

ext nil box_update (box_t * box);
ext nil box_draw (drawable_t * drawable);
ext nil box_set_position_ (box_t * box, SDL_FRect r);
# define box_set_position(box_, ...) \
	box_set_position_ ( \
		box_, \
		(frect_t) { \
			.x = box_ -> x, \
			.y = box_ -> y, \
			__VA_ARGS__ \
		} \
	)

typedef struct {
	f32 dx;
	f32 dy;
} box_new_params;
ext box_t * box_new_ (drawable_t * drawable, box_new_params);
# define box_new(drawable_, ...) \
	box_new_ ( \
		drawable_, \
		(box_new_params) { \
			.dx = 0, \
			.dy = 0, \
			__VA_ARGS__ \
		} \
	)

# endif // PGE_BOX_H

