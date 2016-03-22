#include "cement.hpp"
#include "entity.hpp"
#include "actor.hpp"

#include <libtcod/libtcod.hpp>

#include <vector>
#include <queue>

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

// Execute the actor at the top of the queue
void update_game(std::priority_queue<ActorC *> *world) {
	ActorC *current = world->top();
	const Action *action = current->think();
	// If the actor didn't take an action, render a frame and try again
	// This should only happen if current->actor is a ProxyActorC
	if(action == NULL) {
		return;
	}
	// If there is an element left in the queue, use it as the base time
	// This way, stuff happens chronologically
	/*int base = 0;
	world->pop();
	if(!world->empty()) {
		ActorC *next = world->top();
		base = next->priority;
	}
	action->execute(current->getParent(), base);*/
	action->execute(current->getParent());
	world->push(current);
	return;
}

int main(void) {
	// This will all mostly get moved 
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

	// Create a mindless mob
	Entity *mob = new Entity();
	mob->display = new DisplayC(mob, 'c', TCODColor::yellow);
	mob->actor = new CircleActorC(mob);
	mob->x = 20;
	mob->y = 20;
	
	// Initialize the world
	std::priority_queue<ActorC *> actors;
	actors.push(player->actor);
	actors.push(mob->actor);
	
	// Main loop
	while(!TCODConsole::isWindowClosed()) {
		TCOD_key_t key;
		TCOD_event_t ev = TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS, &key, NULL);
		InputResult result = handle_input(&key, NULL, playerActor);

		if(result == InputResult::EXIT) {
			return 0;
		}
		
		update_game(&actors);

		TCODConsole::root->clear();
		player->display->draw(TCODConsole::root, 0, 0);
		mob->display->draw(TCODConsole::root, 0, 0);
		TCODConsole::flush();
	}
	return 0;
}
