# include "../inc/font.h"

static vec FONTS;

nil font_close (TTF_Font * font) {
	LOG ("Font.close font", NIL);
	TTF_CloseFont (font);
}

nil font_quit () {
	str proc = "Font.quit";
	proc_init (proc);
	for (u08 i = 0; i < FONTS.size; i++) {
		font_close (FONTS.items [i]);
	}
	LOG ("FONT.items.free", NIL);
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
	LOG ("font = Font.open \"%s\", %u", path, &size);
	TTF_Font * font = TTF_OpenFont (path, size);
	vector_psh ("FONTS", &FONTS, "font", font);
	return font;
}

