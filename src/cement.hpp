#ifndef CEMENT_HPP
#define CEMENT_HPP

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

/*
 * This class contains all the state needed to have an instance of the game open. Calling delete on this
 * class (should) put us in the same state as the beginning of the program.
 */
/*class game {
}*/	

#endif // CEMENT_HPP
