# include "../inc/vectors.h"
# include "../inc/log.h"

static vector_t ON_UPDATE;
static vector_t ON_EVENT;
static vector_t AT_QUIT;

vector_t vector_new (str name, u16 capacity) {
	LOG ("%s = Vector.new %u", (u64) name, (u64) capacity);
	ret (vector_t) {
		.items = malloc (sizeof (ptr) * capacity),
		.capacity = capacity,
		.size = 0,
		.name = name
	};
}

nil vector_free (vector_t * vector) {
	LOG ("%s.items.free", (u64) vector -> name);
	free (vector -> items);
}

u08 vector_psh (vector_t * vector, ptr item) {
	LOG ("%s.psh %x", (u64) vector -> name, (u64) item);
	if (vec_psh ((vec *) vector, item)) {
		ret true;
	}
	LOG_ERR ("not %s.psh %x", (u64) vector -> name, (u64) item);
	ret false;
}

u08 vector_rmv (vector_t * vector, ptr item) {
	LOG ("%s.rmv %x", (u64) vector -> name, (u64) item);
	if (vec_inc ((vec *) vector, item)) {
		vec_rmv ((vec *) vector, item);
		ret true;
	}
	LOG_ERR ("not %s.inc %x", (u64) vector -> name, (u64) item);
	ret false;
}

u08 on_update_psh (proc_t * proc) {
	ret vector_psh (&ON_UPDATE, (ptr) proc);
}
u08 on_event_psh (proc_t * proc) {
	ret vector_psh (&ON_EVENT, (ptr) proc);
}
u08 at_quit_psh (proc_t * proc) {
	ret vector_psh (&AT_QUIT, (ptr) proc);
}

u08 on_update_rmv (proc_t * proc) {
	ret vector_rmv (&ON_UPDATE, (ptr) proc);
}
u08 on_event_rmv (proc_t * proc) {
	ret vector_rmv (&ON_EVENT, (ptr) proc);
}
u08 at_quit_rmv (proc_t * proc) {
	ret vector_rmv (&AT_QUIT, (ptr) proc);
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

static u08 _vectors_at_quit () {
	for (u08 i = AT_QUIT.size - 1; i; i--) {
		((u08 (*) ()) ((proc_t *) AT_QUIT.items [i]) -> proc) ();
	}
	ret true;
}
proc_t vectors_at_quit = {"Vectors.at_quit", _vectors_at_quit};

static u08 _vectors_quit () {
	vector_free (&ON_UPDATE);
	vector_free (&ON_EVENT);
	vector_free (&AT_QUIT);
	ret true;
}
static proc_t vectors_quit = {"Vectors.quit", _vectors_quit};

static u08 _vectors_init () {
	ON_UPDATE = vector_new ("ON_UPDATE", 4);
	ON_EVENT = vector_new ("ON_EVENT", 4);
	AT_QUIT = vector_new ("AT_QUIT", 4);
	at_quit_psh (&vectors_quit);
	ret true;
}
proc_t vectors_init = {"Vectors.init", _vectors_init};

