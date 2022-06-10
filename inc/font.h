
# ifndef PGE_FONT_H
# define PGE_FONT_H
# define SDL_MAIN_HANDLED
# include <SDL2/SDL_ttf.h>
# include <pul/cor.h>
# include "proc.h"

typedef TTF_Font font_t;

ext font_t * FONT_DEFAULT;

ext nil font_close (font_t * font);
ext font_t * font_open (str path, u64 size);
ext proc_t font_init;

# endif // PGE_FONT_H

