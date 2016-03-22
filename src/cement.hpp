#ifndef CEMENT_HPP
#define CEMENT_HPP

#include <algorithm>
#include <vector>

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

#endif // CEMENT_HPP
