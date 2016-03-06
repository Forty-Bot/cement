#include <stdio.h>

#include <libtcod/libtcod.h>

int main(void) {
	TCOD_console_set_custom_font("res/dejavu10x10_gs_tc.png", TCOD_FONT_LAYOUT_TCOD, 0, 0);
	TCOD_console_init_root(80, 50, "Cement", false, TCOD_RENDERER_SDL);
	while(!TCOD_console_is_window_closed()) {
		TCOD_sys_check_for_event(TCOD_EVENT_KEY_PRESS, NULL, NULL);
		TCOD_console_clear(NULL);
		TCOD_console_set_char(NULL, 40, 25, '@');
		TCOD_console_flush();
	}	
	return 0;
}
