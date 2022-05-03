
# ifndef PGE_H
# define PGE_H

# define SDL_MAIN_HANDLED
# include <SDL2/SDL_image.h>
# include <SDL2/SDL_main.h>
# include <SDL2/SDL_ttf.h>
# include <SDL2/SDL.h>
# include <pul/vec.h>
# include <pul/put.h>
# include "vectors.h"
# include "window.h"
# include "font.h"

# define KEY_ARROW_UP    1073741906
# define KEY_ARROW_DOWN  1073741905
# define KEY_ARROW_LEFT  1073741904
# define KEY_ARROW_RIGTH 1073741903

# define KEY_CONTROL     1073742048
# define KEY_ESCAPE      27
# define KEY_ENTER       13

extern u08 run;

extern nil init (str title, u16 width, u16 height, u64 delay);
extern nil loop ();
extern nil quit ();

# endif // PGE_H

