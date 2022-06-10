
# ifndef PGE_H
# define PGE_H
# define SDL_MAIN_HANDLED
# include <pul/cor.h>
# include "proc.h"

ext u08 run;
ext u08 pge_init (str title, u16 width, u16 height, u08 delay);
ext nil pge_loop ();
ext nil pge_quit ();

# endif // PGE_H

