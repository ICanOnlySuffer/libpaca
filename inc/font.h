
# ifndef PGE_FONT_H
# define PGE_FONT_H
# define SDL_MAIN_HANDLED
# include <SDL2/SDL_ttf.h>
# include <pul/cor.h>

ext nil font_close (TTF_Font * font);
ext nil font_quit ();
ext nil font_init ();
ext TTF_Font * font_open (str path, u64 size);

# endif // PGE_FONT_H

