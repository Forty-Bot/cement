#include "bunker-generator.hpp"

#include "entity.hpp"
#include "map.hpp"
#include "world.hpp"

#include "mersenne.hpp"

#include <Eigen/Core>

#include <cmath>

using Eigen::Vector2i;
using namespace bunker;

Digger::Digger(int p_x, int p_y, int d_x, int d_y) {
	Vector2i pos, dir;
	pos.x() = p_x;
	pos.y() = p_y;
	dir.x() = d_x;
	dir.y() = d_y;
	init(pos, dir);
}

void Digger::init(Vector2i pos_in, Vector2i dir_in) {
	// Returns max(abs(a), abs(b))
	auto abs_max = [](int a, int b) { a = abs(a); b = abs(b); return a > b ? a : b;};
	// Set dir to be the cardinal direction most closely aligned with dir_in
	dir.x() = (int) ((float) dir_in.x()) / abs_max(dir_in.x(), dir_in.y());
	dir.y() = (int) ((float) dir_in.y()) / abs_max(dir_in.x(), dir_in.y());
	pos = pos_in;
}

World *generate(Entity *player, int x, int y, int seed) {
	TCODRandom *rng = new TCODRandom(seed);
	std::vector<Tile> *tiles = new std::vector<Tile>(x * y, Tile::Wall);
	Map *map =  new Map(x, y, tiles->data());
	
	// Make sure the entrance/exit are at least half the diagonal distance of the map away
	Vector2i entr_v, exit_v, min_v;
	min_v.x() = x;
	min_v.y() = y;
	int min = min_v.norm() / 2;
	do {
		entr_v.x() = rng->get(0, x);
		entr_v.y() = rng->get(0, y);
		exit_v.x() = rng->get(0, x);
		exit_v.y() = rng->get(0, y);
	} while((entr_v - exit_v).norm() < min);
	// Create the first diggers
	std::vector<Digger *> living;
	// Create the entrance/exit facing inwards
	Tunneler *entrance = new Tunneler(entr_v.x(), entr_v.y(), x - 2*entr_v.x(), y - 2*entr_v.y());
	Tunneler *exit = new Tunneler(exit_v.x(), exit_v.y(), x - 2*exit_v.x(), y - 2*exit_v.y());
	living.push_back(entrance);
	living.push_back(exit);

	return new World(player, map); 
}
