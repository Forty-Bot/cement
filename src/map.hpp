#ifndef MAP_HPP
#define MAP_HPP

#include "libtcod.hpp"

#include <cstddef>

/*
 * A tile in a map
 */
class Tile {
public:
	bool walkable;
	TCODColor color;

	static Tile const Wall;
	static Tile const Floor;
	// Draw a tile to the screen
	void draw(TCODConsole *con, int x, int y) {con->setCharBackground(x, y, color);}
	// Prevent static tiles from being deleted
	static void operator delete(void *ptr, std::size_t sz);
	Tile(const Tile *t): walkable(t->walkable), color(t->color) {}
	Tile(const bool walkable, const TCODColor color): walkable(walkable), color(color) {}
};

class Map {
public:
	const int width, height;
	Map(int width, int height, Tile *tiles): width(width), height(height), tiles(tiles) {}
	// Get a tile at coordinates
	Tile &get(int x, int y) const {return tiles[x + width * y];}
	bool valid(int x, int y) {return x >= 0 && y >= 0 && x < width && y < height;}
	bool valid(int x, int y, int w, int h);
	// Returns true if all tiles in the range are unwalkable
	bool unwalkable(int x, int y, int w, int h);
	// Set all tiles in a rectangle to a tile, returns false if out of bounds
	bool makeRectangle(int x, int y, int w, int h, const Tile *t);
	// Draw the whole map
	void draw(TCODConsole *con, int offset_x, int offset_y);
	~Map();
private:
	Tile *tiles;
};

Map *BareMap(int x, int y);

#endif // MAP_HPP
