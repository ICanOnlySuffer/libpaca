# include "../inc/vectors.h"
# include "../inc/font.h"
# include "../inc/log.h"

prv vector_t FONTS;
font_t * FONT_DEFAULT = NIL;

font_t * font_open (str path, u16 size) {
	font_t * font = TTF_OpenFont (path, size);
	LOG ("%x = Font.open \"%s\", %u", font, path, (u64) size);
	if (font) {
		vector_push (&FONTS, font);
	} else {
		ERR ("font_open: %s", SDL_GetError ());
	}
	ret font;
}

nil font_close (font_t * font) {
	LOG ("Font.close %x", font);
	TTF_CloseFont (font);
}

// quit
prv u08 _font_quit () {
	vec_for_all ((vec *) &FONTS, (prc) font_close);
	LOG ("FONTS.free");
	free (FONTS.items);
	TTF_Quit ();
	ret true;
}
prv proc_t font_quit = {"Font.quit", _font_quit};

// init
prv u08 _font_init () {
	if (TTF_Init ()) { // 0 == success for some reason
		LOG ("font_init: %s", (u64) SDL_GetError ());
		ret false;
	}
	FONTS = vector_new ("FONTS", 4);
	at_quit_push (&font_quit);
	ret true;
}
proc_t font_init = {"Font.init", _font_init};

