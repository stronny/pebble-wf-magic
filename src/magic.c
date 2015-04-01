#include <pebble.h>

#define K_ARTIST 1
#define K_ALBUM  2
#define K_TRACK  3

static GFont s_font;
static Window* sw_main;

static char* s8_artist;
static char* s8_album;
static char* s8_track;

static TextLayer* st_artist;
static TextLayer* st_album;
static TextLayer* st_track;

//static AppSync sync;
//static uint8_t* sync_buf;
//static size_t sync_buf_size;

static void init_text_layer(TextLayer* layer, char* str, int16_t margin) {
	str = (char*) malloc(129);
	snprintf(str, 128, "some name or whatever");
	layer = text_layer_create(GRect(0, margin, 144, 56));
	text_layer_set_text(layer, str);
	text_layer_set_font(layer, s_font);
	text_layer_set_text_alignment(layer, GTextAlignmentCenter);
	layer_add_child(window_get_root_layer(sw_main), text_layer_get_layer(layer));
}

static void on_tap(AccelAxisType axis, int32_t value) {
	vibes_short_pulse();
//	layer_mark_dirty((Layer*) st_artist);
//	layer_mark_dirty((Layer*) st_album);
//	layer_mark_dirty((Layer*) st_track);
}

static void on_load(Window* w) {
	init_text_layer(st_artist, s8_artist, 0);
	init_text_layer(st_album,  s8_album,  56);
	init_text_layer(st_track,  s8_track,  112);
	accel_tap_service_subscribe(on_tap);
}

static void on_unload(Window* w) {
	accel_tap_service_unsubscribe();
	text_layer_destroy(st_track);
	text_layer_destroy(st_album);
	text_layer_destroy(st_artist);
	free(s8_track);
	free(s8_album);
	free(s8_artist);
}


/*
static void on_change(const uint32_t key, const Tuple* new_tuple, const Tuple* old_tuple, void* context) {
	
}

static void on_error(DictionaryResult dict_res, AppMessageResult app_res, void* context) {
	static char* dcode = "123456789";
	static char* acode = "123456789ab";
	switch (dict_res) {
		case DICT_OK:                     dcode = "no error "; break;
		case DICT_NOT_ENOUGH_STORAGE:     dcode = "storage  "; break;
		case DICT_INVALID_ARGS:           dcode = "args     "; break;
		case DICT_INTERNAL_INCONSISTENCY: dcode = "inconsist"; break;
		case DICT_MALLOC_FAILED:          dcode = "malloc   "; break;
		else                              dcode = "unknown  ";
	}
	switch (app_res) {
		case APP_MSG_OK:                          acode = "no error   "; break;
		case APP_MSG_SEND_TIMEOUT:                acode = "timeout    "; break;
		case APP_MSG_SEND_REJECTED:               acode = "rejected   "; break;
		case APP_MSG_NOT_CONNECTED:               acode = "!connected "; break;
		case APP_MSG_APP_NOT_RUNNING:             acode = "!running   "; break;
		case APP_MSG_INVALID_ARGS:                acode = "args       "; break;
		case APP_MSG_BUSY:                        acode = "busy       "; break;
		case APP_MSG_BUFFER_OVERFLOW:             acode = "buffer     "; break;
		case APP_MSG_ALREADY_RELEASED:            acode = "released   "; break;
		case APP_MSG_CALLBACK_ALREADY_REGISTERED: acode = "registered "; break;
		case APP_MSG_CALLBACK_NOT_REGISTERED:     acode = "!registered"; break;
		case APP_MSG_OUT_OF_MEMORY:               acode = "memory     "; break;
		case APP_MSG_CLOSED:                      acode = "closed     "; break;
		case APP_MSG_INTERNAL_ERROR:              acode = "internal   "; break;
		else                                      acode = "unknown    ";
	}
		APP_LOG(APP_LOG_LEVEL_WARNING, "%9s %11s", dcode, acode);
}
*/

int main() {
	s_font = fonts_get_system_font(FONT_KEY_ROBOTO_CONDENSED_21);
	sw_main = window_create();
	window_set_window_handlers(sw_main, (WindowHandlers) { .load = on_load, .unload = on_unload });
	window_stack_push(sw_main, true);

//	Tuplet init_dict[] = {
//		TupletBytes(K_ARTIST, , ),
//		TupletBytes(K_ALBUM, , ),
//		TupletBytes(K_TRACK, , ),
//	};
//	
//	app_message_open(app_message_inbox_size_maximum(), app_message_outbox_size_maximum());
//	app_sync_init(sync, sync_buf, sync_buf_size, init_dict, ARRAY_LENGTH(init_dict), on_change, on_error, NULL); //uint16_t

	app_event_loop();

	window_destroy(sw_main);
}
