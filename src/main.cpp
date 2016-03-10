#include <libtcod/libtcod.hpp>

int main(void) {
	// Initialize the console
	TCODConsole::setCustomFont("res/dejavu16x16_gs_tc.png", TCOD_FONT_LAYOUT_TCOD | TCOD_FONT_TYPE_GREYSCALE);
	TCODConsole::initRoot(80, 50, "Cement");
	TCODSystem::setFps(20);
	
	// Position of player
	int x = 40;
	int y = 25;
	
	// Main loop
	while(!TCODConsole::isWindowClosed()) {
		TCOD_key_t key;
		TCOD_event_t ev = TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS, &key, NULL);
		
		if(ev == TCOD_EVENT_KEY_PRESS) {
			if(key.vk == TCODK_CHAR){
				switch(key.c) {
					case 'h':
							x--; break;
					case 'j':
							y++; break;
					case 'k':
							y--; break;
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
		}
		
		TCODConsole::root->clear();
		TCODConsole::root->setChar(x, y, '@');
		TCODConsole::flush();
	}
	return 0;
}
