# include "../inc/renderer.h"
# include "../inc/drawable.h"
# include "../inc/vectors.h"
# include "../inc/font.h"
# include "../inc/pge.h"

# include <SDL2/SDL_image.h>
# include <SDL2/SDL_ttf.h>
# include <SDL2/SDL.h>
# include <pul/vec.h>
# include <pul/put.h>

u08 run = true;

static nil _quit () {
	log_proc (&vectors_at_quit);
	LOG ("SDL.quit", 0);
	SDL_Quit ();
}
static proc_t quit = PROC (
	"quit",
	_quit
);

static u08 _pge_init () {
	LOG ("SDL.init", 0);
	if (SDL_Init (SDL_INIT_VIDEO)) {
		LOG_ERR ("SDL.init: %s", (u64) SDL_GetError ());
		ret false;
	}
	
	log_proc (&vectors_init);
	log_proc (&drawable_init);
	log_proc (&font_init);
	if (not log_proc (&window_init)) {
		log_proc (&quit);
		ret false;
	}
	
	ret true;
}
static proc_t pge_init = PROC (
	"pge.init",
	_pge_init
);

u08 init (str title, u16 width, u16 height, u08 delay) {
	WINDOW_TITLE = title;
	WINDOW_W = width;
	WINDOW_H = height;
	WINDOW_DELAY = delay;
	ret log_proc (&pge_init);
}

nil loop () {
	event_t event;
	
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
	
	log_proc (&quit);
}

