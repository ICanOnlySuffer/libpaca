# include "../inc/vectors.h"

vec ON_UPDATE;
vec ON_EVENT;
vec AT_QUIT;

vec vector_new (str name, u08 size) {
	chr buffer [4];
	str_frm_u64 (buffer, (u64) size);
	LOG (name, " = Vector.new ", buffer);
	return VEC (size);
}

nil vector_free (str name, vec * vector) {
	LOG (name, ".items.free");
	free (vector -> items);
}

nil vector_psh (str vec_name, vec * vector, str fun_name, ptr fun) {
	LOG (vec_name, ".psh ", fun_name);
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
	LOG (vec_name, ".rmv ", fun_name);
	if (vec_inc (vector, fun)) {
		vec_rmv (vector, fun);
	} {
		LOG_ERR ("not ", vec_name, ".inc ", fun_name);
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
	proc_init ("Vector.at_quit");
	for (u08 i = 0; i < AT_QUIT.size; i++) {
		((nil (*) ()) AT_QUIT.items [i]) ();
	}
	proc_quit ();
}

nil vectors_init () {
	proc_init ("Vector.init");
	
	ON_UPDATE = vector_new ("ON_UPDATE", 4);
	ON_EVENT = vector_new ("ON_EVENT", 4);
	AT_QUIT = vector_new ("AT_EXIT", 4);
	
	proc_quit ();
}

nil vectors_quit () {
	proc_init ("Vector.quit");
	
	vector_free ("ON_UPDATE", &ON_UPDATE);
	vector_free ("ON_EVENT", &ON_EVENT);
	vector_free ("AT_QUIT", &AT_QUIT);
	
	proc_quit ();
}

