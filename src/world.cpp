#include "world.hpp"

#include "entity.hpp"
#include "actor.hpp"

#include <algorithm>
#include <queue>
#include <vector>

// Execute the actor at the top of the queue
void World::update() {
	ActorC *current = peek();
	const Action *action = current->think();
	// If the actor didn't take an action, render a frame and try again
	// This should only happen if current->actor is a ProxyActorC
	if(action == NULL) {
		return;
	}
	pop();
	action->execute(current->getParent());
	push(current);
	return;
}

void World::push(ActorC *a) {
	actors.push_back(a);
	std::push_heap(actors.begin(), actors.end(), ActorCompare());
}

ActorC *World::pop() {
	ActorC *tmp = peek();
	std::pop_heap(actors.begin(), actors.end(), ActorCompare());
	actors.pop_back();
	return tmp;
}
