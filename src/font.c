# include "../inc/vectors.h"
# include "../inc/font.h"
# include "../inc/log.h"

static vector_t FONTS;
font_t * FONT_DEFAULT = NIL;

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

nil font_close (TTF_Font * font) {
	LOG ("Font.close %x", (u64) font);
	TTF_CloseFont (font);
}

// quit
static u08 _font_quit () {
	vec_for_all ((vec *) &FONTS, (prc) font_close);
	LOG ("FONTS.free", 0);
	free (FONTS.items);
	TTF_Quit ();
	ret true;
}
static proc_t font_quit = {"Font.quit", _font_quit};

// init
static u08 _font_init () {
	if (TTF_Init ()) { // 0 == success for some reason
		LOG ("font_init: %s", (u64) SDL_GetError ());
		ret false;
	}
	FONTS = vector_new ("FONTS", 4);
	at_quit_psh (&font_quit);
	ret true;
}
proc_t font_init = {"Font.init", _font_init};

