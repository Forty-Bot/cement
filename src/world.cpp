#include "world.hpp"

#include "entity.hpp"
#include "actor.hpp"

#include <queue>

void World::add(Entity *e) {
   actors.push(e->actor);
}   

// Execute the actor at the top of the queue
void World::update() {
	ActorC *current = actors.top();
	const Action *action = current->think();
	// If the actor didn't take an action, render a frame and try again
	// This should only happen if current->actor is a ProxyActorC
	if(action == NULL) {
		return;
	}
	actors.pop();
	action->execute(current->getParent());
	actors.push(current);
	return;
}
