#ifndef UI_HPP
#define UI_HPP

#include "actor.hpp"

#include "libtcod.hpp"

/* 
 * This enum is returned by handle_input
 */
enum InputResult {
	// The player did nothing
	NONE,
	// The user requested to exit
	EXIT,
	// The player made a move
	MOVED,
};

InputResult handle_input(TCOD_key_t *key, TCOD_mouse_t *mouse, ProxyActorC *playerActor);

#endif // UI_HPP
