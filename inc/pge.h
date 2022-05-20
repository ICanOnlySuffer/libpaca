
# ifndef PGE_H
# define PGE_H
# define SDL_MAIN_HANDLED
# include <pul/cor.h>

ext nil arr_for_all (u08 length, ptr array [], nil (*function) (ptr));
ext u08 run;
ext u08 init (str title, u16 width, u16 height, u08 delay);
ext nil loop ();
ext nil quit ();

# endif // PGE_H

