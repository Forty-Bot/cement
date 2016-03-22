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
	void add(Entity *e) { push(e->actor); }
	// TODO: void remove(ActorC *e);
	void update();
private:
	void push(ActorC *a);
	ActorC *peek() { return actors.front(); }
	ActorC *pop();
	std::vector<ActorC *> actors;
};

#endif // WORLD_HPP
