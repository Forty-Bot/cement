#include "actor.hpp"

#include "entity.hpp"

void MoveAction::execute(Entity *e) const {	
	// TODO: Collision checking
	e->x += this->d_x;
	e->y += this->d_y;
}

MoveAction const MoveAction::North(40, 0,-1);
MoveAction const MoveAction::South(40, 0, 1);
MoveAction const MoveAction::East (40, 1, 0);
MoveAction const MoveAction::West (40,-1, 0);
MoveAction const MoveAction::Wait (40, 0, 0);

void ActorC::update(int delta) {
	cooldown -= delta;
	if(cooldown < 0) {
		current = think();
		current->execute(getParent());
		cooldown += current->getDuration();
	}
}

const Action *NullActorC::think() {
	return &MoveAction::Wait;
}

const Action *ProxyActorC::think() {
	return next;
}
