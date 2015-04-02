//static AppSync s_sync;
//static uint8_t* s_sync_buf;
//static size_t s_sync_buf_size;

/*
static void on_change(const uint32_t key, const Tuple* new, const Tuple* old, void* context) {
	char* ptr;
	TextLayer* tl;
	switch (key) {
		case K_ARTIST: ptr = s8_artist; tl = st_artist; break;
		case K_ALBUM:  ptr = s8_album;  tl = st_album;  break;
		case K_TRACK:  ptr = s8_track;  tl = st_track;  break;
		default:
			ptr = NULL;
			tl = NULL;
	}

	APP_LOG(APP_LOG_LEVEL_DEBUG, "%p %p", ptr, tl);
	APP_LOG(APP_LOG_LEVEL_DEBUG, "%lu", key);
	APP_LOG(APP_LOG_LEVEL_DEBUG, "%s", new->value->cstring);

//	strncpy(ptr, new->value->cstring, MAX_LABEL);
//	layer_mark_dirty((Layer*) tl);
}
*/

/*
static void on_error(DictionaryResult dict_res, AppMessageResult app_res, void* context) {
	static char* dcode = "123456789";
	static char* acode = "123456789ab";
	switch (dict_res) {
		case DICT_OK:                     dcode = "no error "; break;
		case DICT_NOT_ENOUGH_STORAGE:     dcode = "storage  "; break;
		case DICT_INVALID_ARGS:           dcode = "args     "; break;
		case DICT_INTERNAL_INCONSISTENCY: dcode = "inconsist"; break;
		case DICT_MALLOC_FAILED:          dcode = "malloc   "; break;
		default:                          dcode = "unknown  ";
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
		default;                                  acode = "unknown    ";
	}
		APP_LOG(APP_LOG_LEVEL_WARNING, "%9s %11s", dcode, acode);
}
*/

/*
	Tuplet init_dict[] = {
		TupletCString(K_ARTIST, ""),
		TupletCString(K_ALBUM,  ""),
		TupletCString(K_TRACK,  ""),
	};
	s_sync_buf_size = dict_calc_buffer_size_from_tuplets(init_dict, ARRAY_LENGTH(init_dict)) - 1;
	s_sync_buf = (uint8_t*) malloc(s_sync_buf_size + 1);
*/

//	app_sync_init(&s_sync, s_sync_buf, s_sync_buf_size, init_dict, ARRAY_LENGTH(init_dict), on_change, on_error, NULL); //uint16_t

//	app_sync_deinit(&s_sync);
//	free(s_sync_buf);
