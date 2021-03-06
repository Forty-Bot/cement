#include "actor.hpp"

#include "entity.hpp"
#include "world.hpp"

void MoveAction::execute(Entity *e) const {	
	int x = e->x + this->d_x;
	int y = e->y + this->d_y;

	if(e->world->map->get(x, y).walkable) {
		e->x = x;
		e->y = y;
	}
		
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

void ActorC::update(int delta) {
	priority -= delta;
}

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
