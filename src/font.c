# include "../inc/font.h"

static vec FONTS;

nil font_close (TTF_Font * font) {
	if (font) {
		LOG ("Font.close");
		TTF_CloseFont (font);
	}
}

nil font_quit () {
	proc_init ("Font.quit");
	for (u08 i = 0; i < FONTS.size; i++) {
		font_close (FONTS.items [0]);
	}
	proc_quit ();
}

nil font_init () {
	proc_init ("Font.init");
	TTF_Init ();
	FONTS = vector_new ("fonts", 4);
	at_quit_psh ("Font.quit", font_quit);
	proc_quit ();
}

TTF_Font * font_open (str path, u08 size) {
	chr buffer [64];
	chr size_str [4];
	str_frm_u64 (size_str, (u64) size);
	STR_CPY (buffer, "Font.open \"", path, "\", ", size_str);
	TTF_Font * font = TTF_OpenFont (path, size);
	vector_psh ("FONTS", &FONTS, buffer, font);
	return font;
}

