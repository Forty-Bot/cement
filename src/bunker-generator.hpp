#ifndef BUNKER_HPP
#define BUNKER_HPP

#include "entity.hpp"
#include "world.hpp"

#include <Eigen/Core>

using Eigen::Vector2i;

namespace bunker {
	class Digger {
	public:
		Digger(Vector2i pos, Vector2i dir) { init(pos, dir);}
		Digger(int p_x, int p_y, int d_x, int d_y);
		// Dig or w/e
		// Returns false if the digger is dead
		virtual bool tick() = 0;
		
		Vector2i &getPos() {return pos;}
		Vector2i &getDir() {return dir;}
		virtual ~Digger() {}
	private:
		void init(Vector2i pos, Vector2i dir);
		Vector2i pos;
		Vector2i dir;
	};

	class Tunneler: public Digger {
	public:
		Tunneler(Vector2i pos, Vector2i dir): Digger(pos, dir) {}
		Tunneler(int p_x, int p_y, int d_x, int d_y): Digger(p_x, p_y, d_x, d_y) {}
		virtual bool tick() { return true;}
	};
	
	World *generate(Entity *player, int x, int y);
}

#endif // BUNKER_HPP
