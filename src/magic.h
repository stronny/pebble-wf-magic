#include <pebble.h>

#define K_PEBBLE (uint32_t) 0
#define K_ARTIST (uint32_t) 1
#define K_ALBUM  (uint32_t) 2
#define K_TRACK  (uint32_t) 3

#define C_OPEN (uint8_t) 0
#define C_STOP (uint8_t) 1
#define C_TAP  (uint8_t) 2

#define MAX_LABEL (size_t) 128

typedef struct Layers {
	TextLayer* header;
	TextLayer* artist;
	TextLayer* album;
	TextLayer* track;
} Layers;
