#ifndef MAP_HPP
#define MAP_HPP

#include "libtcod.hpp"

#include <cstddef>

/*
 * A tile in a map
 */
struct Tile {
	const bool walkable;
	const TCODColor color;

	static Tile const Wall;
	static Tile const Floor;
	void draw(TCODConsole *con, int x, int y) {con->setCharBackground(x, y, color);}
	static void operator delete(void *ptr, std::size_t sz) {};
	Tile(const bool walkable, const TCODColor color): walkable(walkable), color(color) {}
};

class Map {
public:
	const int width, height;
	Tile *get(int x, int y) {return &tiles[x + width * y];}
	void draw(TCODConsole *con, int offset_x, int offset_y);
	~Map();
	Map(int width, int height, Tile *tiles): width(width), height(height), tiles(tiles) {}
private:
	Tile *tiles;
};

Map *BareMap(int x, int y);

#endif // MAP_HPP
