#include "actor.hpp"

#include "entity.hpp"

void MoveAction::execute(Entity *e) const {	
	// TODO: Collision checking
	e->x += this->d_x;
	e->y += this->d_y;
	e->actor->priority += this->getDuration();
}

MoveAction const MoveAction::North(40, 0,-1);
MoveAction const MoveAction::South(40, 0, 1);
MoveAction const MoveAction::East (40, 1, 0);
MoveAction const MoveAction::West (40,-1, 0);
MoveAction const MoveAction::Wait (40, 0, 0);
MoveAction const MoveAction::NorthEast(55, 1,-1);
MoveAction const MoveAction::SouthEast(55, 1, 1);
MoveAction const MoveAction::SouthWest(55,-1, 1);
MoveAction const MoveAction::NorthWest(55,-1,-1);

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

const Action *CircleActorC::think() {
	state++;
	switch(state % 8) {
		case 0:
			return &MoveAction::North;
		case 1:
			return &MoveAction::NorthEast;
		case 2:
			return &MoveAction::East;
		case 3:
			return &MoveAction::SouthEast;
		case 4:
			return &MoveAction::South;
		case 5:
			return &MoveAction::SouthWest;
		case 6:
			return &MoveAction::West;
		case 7:
			return &MoveAction::NorthWest;
	}
}

const Action *ProxyActorC::think() {
	Action const *tmp = next;
	// If we don't get update by the time think() gets called next, we will return NULL
	next = NULL;
	return tmp;
}
