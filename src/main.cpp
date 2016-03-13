#include "entity.hpp"
#include "actor.hpp"

#include <libtcod/libtcod.hpp>

int main(void) {
	// Initialize the console
	TCODConsole::setCustomFont("res/dejavu16x16_gs_tc.png", TCOD_FONT_LAYOUT_TCOD | TCOD_FONT_TYPE_GREYSCALE);
	TCODConsole::initRoot(80, 50, "Cement");
	TCODSystem::setFps(20);
	
	// Create a player
	Entity *player = new Entity();
	player->display = new DisplayC(player, '@', TCODColor::white);
	ProxyActorC *playerActor = new ProxyActorC(player);
	player->actor = playerActor;
	player->x = 40;
	player->y = 25;
	
	// Main loop
	while(!TCODConsole::isWindowClosed()) {
		TCOD_key_t key;
		TCOD_event_t ev = TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS, &key, NULL);
		int timestep = 0; 

		if(ev == TCOD_EVENT_KEY_PRESS) {
			if(key.vk == TCODK_CHAR){
				switch(key.c) {
					case 'h':
						timestep = 40; playerActor->setAction(&MoveAction::West); break;
					case 'j':
						timestep = 40; playerActor->setAction(&MoveAction::South); break;
					case 'k':
						timestep = 40; playerActor->setAction(&MoveAction::North); break;
					case 'l':
						timestep = 40; playerActor->setAction(&MoveAction::East); break;
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
		
		player->actor->update(timestep);

		TCODConsole::root->clear();
		player->display->draw(TCODConsole::root, 0, 0);
		TCODConsole::flush();
	}
	return 0;
}
