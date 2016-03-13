#include "actor.hpp"

#include "entity.hpp"

void MoveAction::execute(Entity *e) const {	
	// TODO: Collision checking
	e->x += this->d_x;
	e->y += this->d_y;
}

MoveAction const MoveAction::North( 0, -1, 40);
MoveAction const MoveAction::South( 0,  1, 40);
MoveAction const MoveAction::East (-1,  0, 40);
MoveAction const MoveAction::West ( 1,  0, 40);
MoveAction const MoveAction::Wait ( 0,  0, 40);

void ActorC::update(int delta) {
	cooldown -= delta;
	if(cooldown < 0) {
		current->execute(getParent());
		current = think();
		cooldown += current->getDuration();
	}
}

const Action *NullActorC::think() {
	return &MoveAction::Wait;
}

const Action *ProxyActorC::think() {
	return next;
}
