# include "../inc/vectors.h"
# include "../inc/font.h"
# include "../inc/log.h"

static vector_t FONTS;

nil font_close (TTF_Font * font) {
	LOG ("Font.close %x", (u64) font);
	TTF_CloseFont (font);
}

nil font_quit () {
	str proc = "Font.quit";
	proc_init (proc);
	
	vec_for_all ((vec *) &FONTS, (prc) font_close);
	LOG ("FONTS.free", 0);
	free (FONTS.items);
	TTF_Quit ();
	
	proc_quit (proc);
}

u08 font_init () {
	str proc = "Font.init";
	proc_init (proc);
	
	if (TTF_Init ()) { // 0 == success for some reason
		LOG ("font_init: %s", (u64) SDL_GetError ());
		proc_quit (proc);
		ret false;
	}
	FONTS = vector_new ("FONTS", 4);
	at_quit_psh (font_quit);
	
	proc_quit (proc);
	ret true;
}

font_t * font_open (str path, u64 size) {
	font_t * font = TTF_OpenFont (path, size);
	LOG ("%x = Font.open \"%s\", %u", (u64) font, (u64) path, size);
	if (font) {
		vector_psh (&FONTS, font);
	} else {
		LOG_ERR ("font_open: %s", (u64) SDL_GetError ());
	}
	ret font;
}

