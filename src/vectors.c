# include "../inc/vectors.h"

vec ON_UPDATE;
vec ON_EVENT;
vec AT_QUIT;

vec vector_new (str name, u64 size) {
	LOG ("%s = Vector.new %u", name, &size);
	return VEC ((u16) size);
}

nil vector_free (str name, vec * vector) {
	LOG ("%s.items.free", name);
	free (vector -> items);
}

nil vector_psh (str vec_name, vec * vector, str fun_name, ptr fun) {
	LOG ("%s.psh %s", vec_name, fun_name);
	vec_psh (vector, fun);
}

nil on_update_psh (str fun_name, nil (* fun) ()) {
	vector_psh ("ON_UPDATE", &ON_UPDATE, fun_name, fun);
}

nil on_event_psh (str fun_name, nil (* fun) (SDL_Event * event)) {
	vector_psh ("ON_EVENT", &ON_EVENT, fun_name, fun);
}

nil at_quit_psh (str fun_name, nil (* fun) ()) {
	vector_psh ("AT_QUIT", &AT_QUIT, fun_name, fun);
}

nil vector_rmv (str vec_name, vec * vector, str fun_name, ptr fun) {
	LOG ("%s.rmv %s", vec_name, fun_name);
	if (vec_inc (vector, fun)) {
		vec_rmv (vector, fun);
	} {
		LOG_ERR ("not %s.inc %s", vec_name, fun_name);
	}
}

nil on_update_rmv (str fun_name, nil (* fun) ()) {
	vector_rmv ("ON_UPDATE", &ON_UPDATE, fun_name, fun);
}

nil on_event_rmv (str fun_name, nil (* fun) (SDL_Event * event)) {
	vector_rmv ("ON_EVENT", &ON_EVENT, fun_name, fun);
}

nil at_quit_rmv (str fun_name, nil (* fun) ()) {
	vector_rmv ("AT_QUIT", &AT_QUIT, fun_name, fun);
}

nil vectors_on_update () {
	for (u08 i = 0; i < ON_UPDATE.size; i++) {
		((nil (*) ()) ON_UPDATE.items [i]) ();
	}
}

nil vectors_on_event (SDL_Event * event) {
	for (u08 i = 0; i < ON_EVENT.size; i++) {
		((nil (*) (SDL_Event *)) ON_EVENT.items [i]) (event);
	}
}

nil vectors_at_quit () {
	str proc = "Vectors.at_quit";
	proc_init (proc);
	for (u08 i = 0; i < AT_QUIT.size; i++) {
		((nil (*) ()) AT_QUIT.items [i]) ();
	}
	proc_quit (proc);
}

nil vectors_quit () {
	str proc = "Vectors.quit";
	proc_init (proc);
	
	vector_free ("ON_UPDATE", &ON_UPDATE);
	vector_free ("ON_EVENT", &ON_EVENT);
	vector_free ("AT_QUIT", &AT_QUIT);
	
	proc_quit (proc);
}

nil vectors_init () {
	str proc = "Vectors.init";
	proc_init (proc);
	
	ON_UPDATE = vector_new ("ON_UPDATE", 4);
	ON_EVENT = vector_new ("ON_EVENT", 4);
	AT_QUIT = vector_new ("AT_EXIT", 4);
	
	at_quit_psh ("Vectors.quit", vectors_quit);
	
	proc_quit (proc);
}

