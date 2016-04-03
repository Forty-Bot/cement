#include "map.hpp"

#include "libtcod.hpp"

#include <vector>

Tile const Tile::Floor(true , TCODColor( 50,  50, 150));
Tile const Tile::Wall (false, TCODColor(  0,   0, 100));

void Map::draw(TCODConsole *con, int offset_x, int offset_y) {
	for(int i = 0; i < width; i++) {
		for(int j = 0; j < height; j++) {
			get(i, j)->draw(con, i + offset_x, j + offset_y);
		}
	}
}

Map::~Map() {
	for(int i = 0; i < width; i++) {
		for(int j = 0; j < height; j++) {
			delete get(i, j);
		}
	}
	delete[] tiles;
}

Map *BareMap(int x, int y) {
	std::vector<Tile> *tiles = new std::vector<Tile>(x * y, Tile::Floor);
	return new Map(x, y, tiles->data());
}
