#include "world.hpp"

#include "entity.hpp"
#include "actor.hpp"

#include <algorithm>
#include <vector>

std::vector<Entity *> World::getEnts(int x, int y) {
	std::vector<Entity *> results;
	for(Entity * i: ents) {
		if(i->x == x && i->y == y) {
			results.push_back(i);
		}
	}
	return results;
}

// Execute the actor at the top of the queue
void World::update() {
	Entity *current = *ents.begin();
	const Action *action = current->actor->think();
	// If the actor didn't take an action, render a frame and try again
	// This should only happen if current->actor is a ProxyActorC
	if(action == NULL) {
		return;
	}	
	ents.erase(ents.begin());
	action->execute(current);
	ents.insert(current);
	return;
}

bool World::remove(Entity *e) {
	for(auto i = ents.begin(); i != ents.end(); i++) {
		if(e == *i) {
			ents.erase(i);
			return true;
		}
	}
	return false;
}
