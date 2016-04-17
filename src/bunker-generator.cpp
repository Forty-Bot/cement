#include "bunker-generator.hpp"

#include "entity.hpp"
#include "map.hpp"
#include "world.hpp"

#include "mersenne.hpp"

#include <Eigen/Core>
#include <Eigen/Geometry>

// Define constants such as pi
#define _USE_MATH_DEFINES
#include <cmath>

using Eigen::Vector2i;
using namespace bunker;

Digger::Digger(Map *map, int p_x, int p_y, int d_x, int d_y, TCODRandom *rand): map(map), rand(rand) {
	Vector2i pos(p_x, p_y);
	Vector2i dir(d_x, d_y);
	init(pos, dir);
}

void Digger::init(Vector2i pos_in, Vector2i dir_in) {
	// Returns max(abs(a), abs(b))
	auto abs_max = [](int a, int b) { a = abs(a); b = abs(b); return a > b ? a : b;};
	// Set dir to be the cardinal direction most closely aligned with dir_in
	dir.x() = (int) ((float) dir_in.x()) / abs_max(dir_in.x(), dir_in.y());
	dir.y() = (int) ((float) dir_in.y()) / abs_max(dir_in.x(), dir_in.y());
	// Prevent diagonals when abs(dir.x)==abs(dir.y)
	if(dir.x() != 0 && dir.y() != 0) {
		// Bias towards horizontal
		dir.y() = 0;
	}
	pos = pos_in;
}

bool Tunneler::tick() {
	if(dead) {
		return false;
	}
	
	// The point opposite our pos in the square we want to dig
	// width-1 because our original pos already includes 1
	Vector2i opp = pos + dir * (width - 1);
	// The point with the smaller magnitude
	//Vector2i less = pos.norm() < opp.norm() ? pos : opp;
	// 90 degree rotation ccw
	// Dir rotated 90 degrees ccw
	Vector2i dir_rot = rotCardinal90(dir);
	// Make it negative
	//dir_rot = -dir_rot.cwiseAbs();
	// Add it to less
	// Everything commented out combined below for optimization
	Vector2i top_left = (pos.cast<float>().norm() < opp.cast<float>().norm() ? pos : opp)
		- (dir_rot.cwiseAbs() * (width / 2));
	// Make sure the coords are valid; everything is empty
	if(!map->unwalkable(top_left.x(), top_left.y(), width, width)) {
		dead = true;
		return false;
	}
	map->makeRectangle(top_left.x(), top_left.y(), width, width, &Tile::Floor);
	pos = opp + dir;
	return true;
}

World *bunker::generate(Entity *player, int x, int y, int seed) {
	TCODRandom *rng = new TCODRandom(seed);
	std::vector<Tile> *tiles = new std::vector<Tile>(x * y, Tile::Wall);
	Map *map = new Map(x, y, tiles->data());
	
	// Make sure the entrance/exit are at least half the diagonal distance of the map away
	Vector2i entr_v, exit_v, min_v;
	min_v.x() = x;
	min_v.y() = y;
	int min = min_v.norm() / 2;
	do {
		entr_v.x() = rng->get(1, x-1);
		entr_v.y() = rng->get(1, y-1);
		exit_v.x() = rng->get(1, x-1);
		exit_v.y() = rng->get(1, y-1);
	} while((entr_v - exit_v).norm() < min);
	// Create the first diggers
	std::vector<Digger *> living;
	// Create the entrance/exit facing inwards
	Tunneler *entr = new Tunneler(map, entr_v.x(), entr_v.y(), x - 2*entr_v.x(), y - 2*entr_v.y(), 3, rng);
	Tunneler *exit = new Tunneler(map, exit_v.x(), exit_v.y(), x - 2*exit_v.x(), y - 2*exit_v.y(), 3, rng);
	living.push_back(entr);
	living.push_back(exit);
	Vector2i player_v = entr_v + entr->getDir();
	player->x = player_v.x();
	player->y = player_v.y();

	while(!living.empty()) {
		for(auto i = living.begin(); i != living.end();) {
			if((*i)->tick()) {
				i++;
			} else {
				i = living.erase(i);
			}
		}
	}

	delete entr;
	delete exit;
	
	return new World(player, map); 
}


Vector2i bunker::rotCardinal90(Vector2i v) {
	Vector2i result(-v.y(), v.x());
	return result;
}
