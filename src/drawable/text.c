# include "../../inc/drawable/text.h"

nil text_draw (drawable_t * text) {
	SDL_Rect rect = {text -> x, text -> y, text -> w, text -> h};
	render_copy (text -> data [0], &rect);
}

nil text_free (ptr * data) {
	SDL_DestroyTexture (data [0]);
	free (data);
}

nil text_renew (drawable_t * text, str string, u08 color) {
	SDL_Surface * surface = render_text (string, color);
	text -> data = malloc (sizeof (SDL_Texture * [1]));
	text -> data [0] = texture_from_surface (surface);
	text -> w = surface -> w;
	text -> h = surface -> h;
	SDL_FreeSurface (surface);
}

drawable_t * text_new (str string, u08 color) {
	drawable_t * text = malloc (sizeof (drawable_t));
	text_renew (text, string, color);
	text -> draw = text_draw;
	text -> free = text_free;
	return text;
}

nil shadowed_text_draw (drawable_t * text) {
	SDL_Rect rect = {text -> x + 1, text -> y, text -> w, text -> h};
	render_copy (text -> data [0], &rect);
	rect.x--;
	rect.y++;
	render_copy (text -> data [0], &rect);
	rect.x--;
	rect.y--;
	render_copy (text -> data [0], &rect);
	rect.x++;
	rect.y--;
	render_copy (text -> data [0], &rect);
	rect.y++;
	render_copy (text -> data [1], &rect);
}

nil shadowed_text_free (ptr * data) {
	SDL_DestroyTexture (data [0]);
	SDL_DestroyTexture (data [1]);
	free (data);
}

drawable_t * shadowed_text_new (str string, u08 bg, u08 fg) {
	drawable_t * shadowed_text = malloc (sizeof (drawable_t));
	shadowed_text -> data = malloc (sizeof (SDL_Texture * [2]));
	SDL_Surface * surface;
	surface = render_text (string, bg);
	shadowed_text -> data [0] = texture_from_surface (surface);
	SDL_FreeSurface (surface);
	surface = render_text (string, fg);
	shadowed_text -> data [1] = texture_from_surface (surface);
	shadowed_text -> w = surface -> w;
	shadowed_text -> h = surface -> h;
	SDL_FreeSurface (surface);
	shadowed_text -> draw = shadowed_text_draw;
	shadowed_text -> free = shadowed_text_free;
	return shadowed_text;
}

