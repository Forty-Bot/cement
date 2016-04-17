#ifndef BUNKER_HPP
#define BUNKER_HPP

#include "entity.hpp"
#include "map.hpp"
#include "world.hpp"

#include "mersenne.hpp"

#include <Eigen/Core>

using Eigen::Vector2i;

namespace bunker {
	class Digger {
	public:
		Digger(Map *map, Vector2i pos, Vector2i dir, TCODRandom *rand):
			map(map), rand(rand) { init(pos, dir);}
		Digger(Map *map, int p_x, int p_y, int d_x, int d_y, TCODRandom *rand);
		// Dig or w/e
		// Returns false if the digger is dead
		virtual bool tick() = 0;
		
		Vector2i &getPos() {return pos;}
		Vector2i &getDir() {return dir;}
		virtual ~Digger() {}
	protected:
		Map *map;
		Vector2i pos;
		Vector2i dir;
		TCODRandom *rand;
	private:
		void init(Vector2i pos, Vector2i dir);
	};

	class Tunneler: public Digger {
	public:
		Tunneler(Map *map, Vector2i pos, Vector2i dir, int width, TCODRandom *rand):
			Digger(map, pos, dir, rand), width(width) {}
		Tunneler(Map *map, int p_x, int p_y, int d_x, int d_y, int width, TCODRandom *rand):
			Digger(map, p_x, p_y, d_x, d_y, rand), width(width) {}
		int getWidth() {return width;}
		virtual bool tick();
	private:
		int width;
		bool started = false;
		bool dead = false;
	};
	
	// Only works on cardinals
	Vector2i rotCardinal90(Vector2i v);
	World *generate(Entity *player, int x, int y, int seed);
}

#endif // BUNKER_HPP
