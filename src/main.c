#include <stdio.h>

#include <libtcod/libtcod.h>

int main(void) {
	// Initialize the console
	TCOD_console_set_custom_font("res/dejavu16x16_gs_tc.png", TCOD_FONT_LAYOUT_TCOD |
		TCOD_FONT_TYPE_GREYSCALE, 0, 0);
	TCOD_console_init_root(80, 50, "Cement", false, TCOD_RENDERER_SDL);
	TCOD_sys_set_fps(20);
	
	// Position of player
	int x = 40;
	int y = 25;
	
	// Main loop
	while(!TCOD_console_is_window_closed()) {
		TCOD_key_t key;
		TCOD_sys_check_for_event(TCOD_EVENT_KEY_PRESS, &key, NULL);
		
		if(key.vk == TCODK_CHAR){
			switch(key.c) {
				case 'h':
						x--; break;
				case 'j':
						y--; break;
				case 'k':
						y++; break;
				case 'l':
						x++; break;
				default:
						break;
			}
		} else {
			switch(key.vk) {
				case TCODK_ESCAPE:
					return 0;
				default:
					break;
			}
		}
		
		TCOD_console_clear(NULL);
		TCOD_console_set_char(NULL, x, y, '@');
		TCOD_console_flush();
	}
	return 0;
}
