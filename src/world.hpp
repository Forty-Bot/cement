#ifndef WORLD_HPP
#define WORLD_HPP

#include "actor.hpp"

#include <queue>
#include <vector>

struct ActorCompare {
	bool operator()	(const ActorC *a, const ActorC *b) const {
		return a->priority > b->priority;
	}
};

class World {
public:
	void add(Entity *e);
	// TODO: void remove(ActorC *e);
	void update();
private:
	std::priority_queue<ActorC *, std::vector<ActorC *>, ActorCompare> actors;
};

#endif // WORLD_HPP
