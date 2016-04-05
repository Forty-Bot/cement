#ifndef MAP_HPP
#define MAP_HPP

#include "libtcod.hpp"

#include <cstddef>

/*
 * A tile in a map
 */
struct Tile {
	bool walkable;
	TCODColor color;

	static Tile const Wall;
	static Tile const Floor;
	// Draw a tile to the screen
	void draw(TCODConsole *con, int x, int y) {con->setCharBackground(x, y, color);}
	// Prevent static tiles from being deleted
	static void operator delete(void *ptr, std::size_t sz);
	Tile(const bool walkable, const TCODColor color): walkable(walkable), color(color) {}
};

class Map {
public:
	const int width, height;
	Map(int width, int height, Tile *tiles): width(width), height(height), tiles(tiles) {}
	// Get a tile at coordinates
	Tile &get(int x, int y) const {return tiles[x + width * y];}
	// Draw the whole map
	void draw(TCODConsole *con, int offset_x, int offset_y);
	~Map();
private:
	Tile *tiles;
};

Map *BareMap(int x, int y);

#endif // MAP_HPP
