# include "../inc/vectors.h"
# include "../inc/log.h"

prv vector_t ON_UPDATE;
prv vector_t ON_EVENT;
prv vector_t AT_QUIT;

vector_t vector_new (str name, u16 capacity) {
	LOG ("%s = Vector.new %u", name, (u64) capacity);
	ret (vector_t) {
		.items = malloc (sizeof (ptr) * capacity),
		.capacity = capacity,
		.size = 0,
		.name = name
	};
}

nil vector_free (vector_t * vector) {
	LOG ("%s.items.free", vector -> name);
	free (vector -> items);
}

u08 vector_push (vector_t * vector, ptr item) {
	LOG ("%s.push %x", vector -> name, item);
	if (vec_push ((vec *) vector, item)) {
		ret true;
	}
	ERR ("not %s.push %x", vector -> name, item);
	ret false;
}

u08 vector_remove (vector_t * vector, ptr item) {
	LOG ("%s.remove %x", vector -> name, item);
	if (vec_includes ((vec *) vector, item)) {
		vec_remove ((vec *) vector, item);
		ret true;
	}
	ERR ("not %s.includes %x", vector -> name, item);
	ret false;
}

u08 on_update_push (proc_t * proc) {
	ret vector_push (&ON_UPDATE, (ptr) proc);
}
u08 on_event_push (proc_t * proc) {
	ret vector_push (&ON_EVENT, (ptr) proc);
}
u08 at_quit_push (proc_t * proc) {
	ret vector_push (&AT_QUIT, (ptr) proc);
}

u08 on_update_remove (proc_t * proc) {
	ret vector_remove (&ON_UPDATE, (ptr) proc);
}
u08 on_event_remove (proc_t * proc) {
	ret vector_remove (&ON_EVENT, (ptr) proc);
}
u08 at_quit_remove (proc_t * proc) {
	ret vector_remove (&AT_QUIT, (ptr) proc);
}

nil vectors_on_update () {
	for (u08 i = 0; i < ON_UPDATE.size; i++) {
		((u08 (*) ()) ((proc_t *) ON_UPDATE.items [i]) -> proc) ();
	}
}

nil vectors_on_event (event_t * event) {
	for (u08 i = 0; i < ON_EVENT.size; i++) {
		(
			(u08 (*) (event_t *)) (
				(proc_t *) ON_EVENT.items [i]
			) -> proc
		) (event);
	}
}

prv u08 _vectors_at_quit () {
	for (u08 i = AT_QUIT.size - 1; i; i--) {
		((u08 (*) ()) ((proc_t *) AT_QUIT.items [i]) -> proc) ();
	}
	ret true;
}
proc_t vectors_at_quit = {"Vectors.at_quit", _vectors_at_quit};

prv u08 _vectors_quit () {
	vector_free (&ON_UPDATE);
	vector_free (&ON_EVENT);
	vector_free (&AT_QUIT);
	ret true;
}
prv proc_t vectors_quit = {"Vectors.quit", _vectors_quit};

prv u08 _vectors_init () {
	ON_UPDATE = vector_new ("ON_UPDATE", 4);
	ON_EVENT = vector_new ("ON_EVENT", 4);
	AT_QUIT = vector_new ("AT_QUIT", 4);
	at_quit_push (&vectors_quit);
	ret true;
}
proc_t vectors_init = {"Vectors.init", _vectors_init};

