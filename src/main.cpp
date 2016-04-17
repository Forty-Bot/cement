#include "entity.hpp"
#include "actor.hpp"
#include "world.hpp"
#include "map.hpp"
#include "ui.hpp"
#include "bunker-generator.hpp"

#include "libtcod.hpp"

#include "lua.hpp"

#include <ctime>

typedef TCODConsole con;
typedef TCODSystem sys;

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

	// Initialize the world
	World *world = bunker::generate(player, 80, 50, time(NULL));
	player->world = world;
	Map *map = world->map; 

	// Create a mindless mob
	/*Entity *mob = new Entity();
	mob->display = new EntityDisplayC(mob, 'c', TCODColor::yellow);
	mob->actor = new CircleActorC(mob);
	mob->x = 20;
	mob->y = 20;
	mob->world = world;
	world->add(mob);*/

	// Main loop
	while(!con::isWindowClosed()) {
		TCOD_key_t key;
		TCOD_event_t ev = sys::checkForEvent(TCOD_EVENT_KEY_PRESS, &key, NULL);
		InputResult result = handle_input(&key, NULL, playerActor);

		if(result == InputResult::EXIT) {
			return 0;
		}
		
		world->update();

		con::root->clear();
		map->draw(con::root, 0, 0);
		player->display->draw(con::root);
		//mob->display->draw(con::root);
		con::flush();
	}
	return 0;
}
