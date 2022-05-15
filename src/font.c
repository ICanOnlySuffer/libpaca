# include "../inc/vectors.h"
# include "../inc/font.h"
# include "../inc/log.h"

static vec FONTS;

nil font_close (TTF_Font * font) {
	LOG ("Font.close font", 0);
	TTF_CloseFont (font);
}

nil font_quit () {
	str proc = "Font.quit";
	proc_init (proc);
	vec_for_all (&FONTS, (nil (*) (ptr)) font_close);
	LOG ("FONTS.items.free", 0);
	free (FONTS.items);
	proc_quit (proc);
}

nil font_init () {
	str proc = "Font.init";
	proc_init (proc);
	TTF_Init ();
	FONTS = vector_new ("FONTS", 4);
	at_quit_psh ("Font.quit", font_quit);
	proc_quit (proc);
}

TTF_Font * font_open (str path, u64 size) {
	LOG ("font = Font.open \"%s\", %u", (u64) path, size);
	font_t * font = TTF_OpenFont (path, size);
	if (font) {
		vector_psh ("FONTS", &FONTS, "font", font);
	} else {
		LOG_ERR ("SDL: %s", (u64) SDL_GetError ());
	}
	return font;
}

