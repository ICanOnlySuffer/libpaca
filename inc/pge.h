
# ifndef ENGINE_H
# define ENGINE_H

# define SDL_MAIN_HANDLED
# include <SDL2/SDL_image.h>
# include <SDL2/SDL_main.h>
# include <SDL2/SDL_ttf.h>
# include <SDL2/SDL.h>
# include <pul/vec.h>
# include <pul/put.h>

# define KEY_ARROW_UP    1073741906
# define KEY_ARROW_DOWN  1073741905
# define KEY_ARROW_LEFT  1073741904
# define KEY_ARROW_RIGTH 1073741903

# define KEY_CONTROL     1073742048
# define KEY_ENTER       13

extern SDL_Window * WINDOW;
extern SDL_Renderer * RENDERER;
extern SDL_Texture * TEXTURE;
extern TTF_Font * FONT;

extern struct window {
	u16 width;
	u16 height;
} window;

extern vec ON_UPDATE;
extern vec ON_EVENT;
extern vec AT_EXTI;
extern vec KEYS;

extern u08 run;

extern nil init (str title, u16 width, u16 height);
extern nil quit ();
extern nil mainloop ();

# define LOG(...) \
	PUT_ARR ("\e[36m", __VA_ARGS__, "\e[0m\n")

# define LOG_ERR(...) \
	PUT_ERR_ARR ("\e[31m", __VA_ARGS__, "\e[0m\n")

stainl SDL_Texture * texture_from_surface (SDL_Surface * surface) {
	return SDL_CreateTextureFromSurface (RENDERER, surface);
}

stainl nil set_render_target (SDL_Texture * texture) {
	SDL_SetRenderTarget (RENDERER, texture);
}

stainl nil render_clear () {
	SDL_RenderClear (RENDERER);
}

stainl nil render_copy (SDL_Texture * texture, SDL_Rect * rect) {
	SDL_RenderCopy (RENDERER, texture, NIL, rect);
}

stainl nil render () {
	SDL_RenderPresent (RENDERER);
}

# endif // ENGINE_H

