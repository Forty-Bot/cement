#include "map.hpp"

#include "libtcod.hpp"

#include <vector>

Tile const Tile::Floor(true , TCODColor( 50,  50, 150));
Tile const Tile::Wall (false, TCODColor(  0,   0, 100));

void Tile::operator delete(void *ptr, std::size_t sz) {
	if(ptr != &Tile::Floor || ptr != &Tile::Wall) {
		::operator delete(ptr);
	}
}

bool Map::valid(int x, int y, int w, int h) {
	if(!valid(x, y) || w < 1 || h < 1) {
		return false;
	}
	if(!valid(x + w - 1, y + h - 1)) {
		return false;
	}
	return true;
}

bool Map::unwalkable(int x, int y, int w, int h) {
	if(!valid(x, y, w, h)) {
		return false;
	}

	for(int i = x; i < x + w; i++) {
		for(int j = y; j < y + h; j++) {
			if(get(i, j).walkable) {
				return false;
			}
		}
	}
	return true;
}

bool Map::makeRectangle(int x, int y, int w, int h, const Tile *t) {
	if(!valid(x, y, w, h)) {
		return false;
	}

	for(int i = x; i < x + w; i++) {
		for(int j = y; j < y + h; j++) {
			new (&get(i, j)) Tile(t);
		}
	}
	return true;
}

void Map::draw(TCODConsole *con, int offset_x, int offset_y) {
	for(int i = 0; i < width; i++) {
		for(int j = 0; j < height; j++) {
			get(i, j).draw(con, i + offset_x, j + offset_y);
		}
	}
}

Map::~Map() {
	for(int i = 0; i < width; i++) {
		for(int j = 0; j < height; j++) {
			delete &get(i, j);
		}
	}
	delete[] tiles;
}

Map *BareMap(int x, int y) {
	std::vector<Tile> *tiles = new std::vector<Tile>(x * y, Tile::Floor);
	return new Map(x, y, tiles->data());
}
