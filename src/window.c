# include "../inc/vectors.h"
# include "../inc/window.h"

struct window WINDOW;

nil window_quit () {
	str proc = "Window.quit";
	proc_init (proc);
	LOG ("WINDOW.renderer.destroy", 0);
	SDL_DestroyRenderer (WINDOW.renderer);
	LOG ("WINDOW.texture.destroy", 0);
	SDL_DestroyTexture (WINDOW.texture);
	LOG ("WINDOW.window.destroy", 0);
	SDL_DestroyWindow (WINDOW.window);	
	proc_quit (proc);
}

nil window_init (str name, u64 width, u64 height) {
	str proc = "Window.init";
	proc_init (proc);
	LOG (
		"WINDOW.window = SDL.create_window \"%s\", %u, %u",
		(u64) name, width, height
	);
	WINDOW.window = SDL_CreateWindow (
		name,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		width,
		height,
		0
	);
	if (not WINDOW.window) {
		LOG_ERR ("SDL.create_window: %s", (u64) SDL_GetError ());
		proc_quit (proc);
		SDL_Quit ();
		exit (1);
	}
	
	LOG ("WINDOW.renderer = SDL.create_renderer", 0);
	WINDOW.renderer = SDL_CreateRenderer (WINDOW.window, -1, 2);
	if (not WINDOW.renderer) {
		LOG_ERR ("SDL.create_renderer: %s", (u64) SDL_GetError ());
		SDL_DestroyWindow (WINDOW.window);
		SDL_Quit ();
		proc_quit (proc);
		exit (1);
	}
	
	LOG (
		"WINDOW.texture = SDL.create_texture WINDOW.renderer, %u, %u",
		width,
		height
	);
	WINDOW.texture = SDL_CreateTexture (
		WINDOW.renderer,
		SDL_PIXELFORMAT_RGBA8888,
		SDL_TEXTUREACCESS_TARGET,
		width,
		height
	);
	if (not WINDOW.texture) {
		LOG_ERR ("SDL.create_texture: %s", (u64) SDL_GetError ());
		SDL_DestroyRenderer (WINDOW.renderer);
		SDL_DestroyWindow (WINDOW.window);
		SDL_Quit ();
		proc_quit (proc);
		exit (1);
	}
	
	WINDOW.w = width;
	WINDOW.h = height;
	
	at_quit_psh ("Window.quit", window_quit);
	
	proc_quit (proc);
}

