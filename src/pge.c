# include "../inc/renderer.h"
# include "../inc/vectors.h"
# include "../inc/font.h"
# include "../inc/pge.h"

# include <SDL2/SDL_image.h>
# include <SDL2/SDL_ttf.h>
# include <SDL2/SDL.h>
# include <pul/vec.h>
# include <pul/put.h>

nil arr_for_all (u08 length, ptr array [], nil (*function) (ptr)) {
	for (u08 i = 0; i < length; i++) {
		function (array [i]);
	}
}

u08 run = true;

u08 init (str title, u16 width, u16 height, u08 delay) {
	str proc = "init";
	proc_init (proc);
	
	LOG ("SDL.init", 0);
	if (SDL_Init (SDL_INIT_VIDEO)) {
		LOG_ERR ("SDL.init: %s", (u64) SDL_GetError ());
		proc_quit (proc);
		return false;
	}
	
	vectors_init ();
	font_init ();
	if (not window_init (title, width, height, delay)) {
		proc_quit (proc);
		quit ();
		return false;
	}
	
	proc_quit (proc);
	return true;
}

nil quit () {
	str proc = "quit";
	proc_init (proc);
	vectors_at_quit ();
	LOG ("SDL.quit", 0);
	SDL_Quit ();
	proc_quit (proc);
}

nil loop () {
	str proc = "loop";
	proc_init (proc);
	SDL_Event event;
	
	do {
		render_set_target (TEXTURE);
		render_set_draw_color (WINDOW_COLOR);
		render_clear ();
		
		while (SDL_PollEvent (&event)) {
			vectors_on_event (&event);
		}
		vectors_on_update ();
		
		render_set_target (NIL);
		render_copy (TEXTURE, NIL);
		render_present ();
		
		SDL_Delay (WINDOW_DELAY);
	} while (run);
	
	proc_quit (proc);
	quit ();
}

