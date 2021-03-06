#include <pebble.h>
#include "magic.h"

static Layers* get_layers (Layers* layers) {
	static Layers* stored;
	if (layers) stored = layers;
	return stored;
}

static void send_code(uint8_t code) {
	DictionaryIterator* di = NULL;
	app_message_outbox_begin(&di);
	dict_write_uint8(di, K_PEBBLE, code);
	dict_write_end(di);
	app_message_outbox_send();
}

static void on_tick(struct tm* tick, TimeUnits units) {
	Layers* layers = get_layers(NULL);
	clock_copy_time_string((char*) text_layer_get_text(layers->header), 8);
	layer_mark_dirty((Layer*) layers->header);
}

static void on_tap(AccelAxisType axis, int32_t value) {
	vibes_short_pulse();
	send_code(C_TAP);
}

static TextLayer* init_text_layer(Window* w, char* str, int16_t margin, int16_t height, GFont font, GTextAlignment align, GColor back, GColor front) {
	TextLayer* layer = text_layer_create(GRect(0, margin, 144, height));
	text_layer_set_text(layer, str);
	text_layer_set_font(layer, font);
	text_layer_set_text_alignment(layer, align);
	text_layer_set_background_color(layer, back);
	text_layer_set_text_color(layer, front);
	layer_add_child(window_get_root_layer(w), text_layer_get_layer(layer));
	return layer;
}

/*
static void app_error(AppMessageResult res, char* error) {
	char* buf = "123456789012345";
	switch (res) {
		case APP_MSG_OK:                          buf = "no error"; break;
		case APP_MSG_SEND_TIMEOUT:                buf = "timeout"; break;
		case APP_MSG_SEND_REJECTED:               buf = "rejected"; break;
		case APP_MSG_NOT_CONNECTED:               buf = "not connected"; break;
		case APP_MSG_APP_NOT_RUNNING:             buf = "not running"; break;
		case APP_MSG_INVALID_ARGS:                buf = "invalid args"; break;
		case APP_MSG_BUSY:                        buf = "busy"; break;
		case APP_MSG_BUFFER_OVERFLOW:             buf = "overflow"; break;
		case APP_MSG_ALREADY_RELEASED:            buf = "released"; break;
		case APP_MSG_CALLBACK_ALREADY_REGISTERED: buf = "registered"; break;
		case APP_MSG_CALLBACK_NOT_REGISTERED:     buf = "not registered"; break;
		case APP_MSG_OUT_OF_MEMORY:               buf = "out of memory"; break;
		case APP_MSG_CLOSED:                      buf = "closed"; break;
		case APP_MSG_INTERNAL_ERROR:              buf = "internal"; break;
		default:                                  buf = "unknown";
	}
	snprintf(error, strlen(buf) + 1, "%s", buf);
}
*/

static void on_receive(DictionaryIterator* di, void* context) {
	Layers* layers = (Layers*) context;
	TextLayer* layer = NULL;
	Tuple* tup = dict_read_first(di);
	while(tup) {
		switch (tup->key) {
			case K_ARTIST: layer = layers->artist; break;
			case K_ALBUM:  layer = layers->album;  break;
			case K_TRACK:  layer = layers->track;  break;
			default: APP_LOG(APP_LOG_LEVEL_WARNING, "unknown key %lu", tup->key);
		}
		if (layer) {
			snprintf((char*) text_layer_get_text(layer), MAX_LABEL, "%s", tup->value->cstring);
			layer_mark_dirty((Layer*) layer);
		}
		tup = dict_read_next(di);
	}
}

int main() {
	Window* win = window_create();
	GFont font = fonts_get_system_font(FONT_KEY_ROBOTO_CONDENSED_21);
	char buf_header[MAX_LABEL + 1] = "";
	char buf_artist[MAX_LABEL + 1] = "";
	char buf_album[MAX_LABEL + 1] = "";
	char buf_track[MAX_LABEL + 1] = "";
	Layers layers = {
		.header = init_text_layer(win, buf_header,   0, 24, font, GTextAlignmentCenter, GColorBlack, GColorWhite),
		.artist = init_text_layer(win, buf_artist,  24, 48, font, GTextAlignmentCenter, GColorWhite, GColorBlack),
		.album  = init_text_layer(win, buf_album,   72, 48, font, GTextAlignmentCenter, GColorWhite, GColorBlack),
		.track  = init_text_layer(win, buf_track,  120, 48, font, GTextAlignmentCenter, GColorWhite, GColorBlack),
	};
	get_layers(&layers);

	window_stack_push(win, true);

	app_message_register_inbox_received(on_receive);
	app_message_set_context(&layers);
	app_message_open(app_message_inbox_size_maximum(), app_message_outbox_size_maximum());

	tick_timer_service_subscribe(MINUTE_UNIT, on_tick);
	on_tick(NULL, MINUTE_UNIT);
	accel_tap_service_subscribe(on_tap);

//snprintf(buf_header, 11, "%p", layers.track);
//layer_mark_dirty((Layer*) layers.header);

	send_code(C_OPEN);
	app_event_loop();
	send_code(C_STOP);
	accel_tap_service_unsubscribe();
	tick_timer_service_unsubscribe();
	app_message_deregister_callbacks();
	text_layer_destroy(layers.track);
	text_layer_destroy(layers.album);
	text_layer_destroy(layers.artist);
	text_layer_destroy(layers.header);
	window_destroy(win);
}
