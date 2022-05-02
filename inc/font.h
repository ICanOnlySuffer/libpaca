
# ifndef PGE_FONT_H
# define PGE_FONT_H
# define SDL_MAIN_HANDLED
# include <SDL2/SDL_ttf.h>
# include "vectors.h"
# include "log.h"

extern nil font_close (TTF_Font * font);
extern nil font_quit ();
extern nil font_init ();
extern TTF_Font * font_open (str path, u08 size);

# endif // PGE_FONT_H

