#include "actor.hpp"

#include "entity.hpp"

void MoveAction::execute(Entity *e, int base) const {	
	// TODO: Collision checking
	e->x += this->d_x;
	e->y += this->d_y;
	e->actor->priority = base + this->getDuration();
}

MoveAction const MoveAction::North(40, 0,-1);
MoveAction const MoveAction::South(40, 0, 1);
MoveAction const MoveAction::East (40, 1, 0);
MoveAction const MoveAction::West (40,-1, 0);
MoveAction const MoveAction::Wait (40, 0, 0);

/* Returns true if we took an action, false if we didn't */
void ActorC::update(int delta) {
	/*cooldown -= delta;
	if(cooldown < 0) {
		current = think();
		current->execute(getParent());
		cooldown += current->getDuration();
	}*/
}

/*bool ActorCompare::operator()(const Entity *x, const Entity *y) {
	// Make sure the requisite bits are non-null
	return x && y && x->actor && y->actor && x->actor->priority >= y->actor->priority;
}*/

const Action *NullActorC::think() {
	return &MoveAction::Wait;
}

const Action *ProxyActorC::think() {
	Action const *tmp = next;
	// If we don't get update by the time think() gets called next, we will return NULL
	next = NULL;
	return tmp;
}
