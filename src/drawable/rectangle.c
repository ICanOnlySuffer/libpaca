# include "../../inc/drawable/rectangle.h"

nil rectangle_draw (drawable_t * rectangle) {
	color_t current_color;
	SDL_GetRenderDrawColor (
		WINDOW.renderer,
		&current_color.r,
		&current_color.g,
		&current_color.b,
		&current_color.a
	);
	
	color_t * color = (color_t *) rectangle -> data [0];
	SDL_SetRenderDrawColor (
		WINDOW.renderer,
		color -> r,
		color -> g,
		color -> b,
		color -> a
	);
	SDL_RenderDrawRect (WINDOW.renderer, &rectangle -> rect);
	SDL_SetRenderDrawColor (
		WINDOW.renderer,
		current_color.r,
		current_color.g,
		current_color.b,
		current_color.a
	);
}

nil rectangle_free (ptr * data) {
	// nothing to free
}

drawable_t * rectangle_new_ (color_t * color, rect_t rect) {
	drawable_t * rectangle = malloc (sizeof (drawable_t));
	rectangle -> data = malloc (sizeof (ptr));
	rectangle -> data [0] = color;
	rectangle -> draw = rectangle_draw;
	rectangle -> free = rectangle_free;
	rectangle -> rect.w = rect.w;
	rectangle -> rect.h = rect.h;
	drawable_set_position (rectangle, rect.x, rect.y);
	return rectangle;
}

