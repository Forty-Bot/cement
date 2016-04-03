#include "cement.hpp"
#include "entity.hpp"
#include "actor.hpp"
#include "world.hpp"
#include "map.hpp"

#include "libtcod.hpp"

#include "lua.hpp"

typedef TCODConsole con;
typedef TCODSystem sys;

InputResult handle_input(TCOD_key_t *key, TCOD_mouse_t *mouse, ProxyActorC *playerActor) {
	if(key->vk == TCODK_CHAR){
		switch(key->c) {
			case 'h':
				playerActor->setAction(&MoveAction::West); return InputResult::MOVED;
			case 'j':
				playerActor->setAction(&MoveAction::South); return InputResult::MOVED;
			case 'k':
				playerActor->setAction(&MoveAction::North); return InputResult::MOVED;
			case 'l':
				playerActor->setAction(&MoveAction::East); return InputResult::MOVED;
			case 'u':
				playerActor->setAction(&MoveAction::NorthEast); return InputResult::MOVED;
			case 'n':
				playerActor->setAction(&MoveAction::SouthEast); return InputResult::MOVED;
			case 'b':
				playerActor->setAction(&MoveAction::SouthWest); return InputResult::MOVED;
			case 'y':
				playerActor->setAction(&MoveAction::NorthWest); return InputResult::MOVED;
			default:
				return InputResult::NONE;
		}
	} else {
		switch(key->vk) {
			case TCODK_ESCAPE:
				return InputResult::EXIT;
			default:
				return InputResult::NONE;
		}
	}
}

int main(void) {
	// This will all mostly get moved 
	// Initialize the console
	con::setCustomFont("res/dejavu16x16_gs_tc.png", TCOD_FONT_LAYOUT_TCOD | TCOD_FONT_TYPE_GREYSCALE);
	con::initRoot(80, 50, "Cement");
	sys::setFps(20);
	
	// Create a player
	Entity *player = new Entity();
	player->display = new EntityDisplayC(player, '@', TCODColor::white);
	ProxyActorC *playerActor = new ProxyActorC(player);
	player->actor = playerActor;
	player->x = 40;
	player->y = 25;

	// Create a mindless mob
	Entity *mob = new Entity();
	mob->display = new EntityDisplayC(mob, 'c', TCODColor::yellow);
	mob->actor = new CircleActorC(mob);
	mob->x = 20;
	mob->y = 20;
	
	// Initialize the world
	World world;
	world.add(player);
	world.add(mob);

	// Create the map
	Map *map = BareMap(80, 50);
	
	// Main loop
	while(!con::isWindowClosed()) {
		TCOD_key_t key;
		TCOD_event_t ev = sys::checkForEvent(TCOD_EVENT_KEY_PRESS, &key, NULL);
		InputResult result = handle_input(&key, NULL, playerActor);

		if(result == InputResult::EXIT) {
			return 0;
		}
		
		world.update();

		con::root->clear();
		map->draw(con::root, 0, 0);
		player->display->draw(con::root);
		mob->display->draw(con::root);
		con::flush();
	}
	return 0;
}
