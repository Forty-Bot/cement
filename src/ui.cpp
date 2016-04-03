#include "ui.hpp"

#include "actor.hpp"

#include "libtcod.hpp"

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
			case '.':
				playerActor->setAction(&MoveAction::Wait); return InputResult::MOVED;
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
