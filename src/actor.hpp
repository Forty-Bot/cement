#ifndef ACTOR_HPP
#define ACTOR_HPP

#include "entity.hpp"

#include <functional>

/*
 * An action is some sort of thing an Entity can do.
 */
class Action {
public:
	int getDuration() const {return duration;};
	virtual void execute(Entity *e, int base) const = 0;
protected:
	Action(int duration): duration(duration) {}
private:
	int duration;
};

/*
 * This class contains static instances which represent directions, similar to a java-style enum.
 */
class MoveAction: public Action {
public:
	//TODO: Add a delete operator
	virtual void execute(Entity *e, int base) const;
	// Static instances of MoveAction
	static MoveAction const North;
	static MoveAction const South;
	static MoveAction const East;
	static MoveAction const West;
	static MoveAction const Wait;
	static MoveAction const NorthEast;
	static MoveAction const SouthEast;
	static MoveAction const SouthWest;
	static MoveAction const NorthWest;
private:
	MoveAction(int duration, int d_x, int d_y): Action(duration), d_x(d_x), d_y(d_y) {}
	int d_x;
	int d_y;
};

class ActorC: public Component {
public:
	virtual const Action *think() = 0;
	void update(int delta) final;
	// The priority (low numbers==high priority) this entity has in the actors queue
	int priority;
protected:
	ActorC(Entity *parent): Component(parent),priority(0)  {}
private:
	Action const *current = &MoveAction::Wait;
};

namespace std {
	template<> struct less<ActorC> {
		bool operator()(const ActorC *a, const ActorC *b) const {return a->priority >= b->priority;}
		typedef ActorC first_argument_type;
		typedef ActorC second_argument_type;
		typedef bool result_type;
	};
}

/*
 * This actor does nothing.
 */
class NullActorC: public ActorC {
public:
	virtual const Action *think();
	NullActorC(Entity *parent): ActorC(parent) {}
};

/*
 * This actor does whatever we tell it to do. 
 * Use getAction() to see whether we need to wait for user input.
 */
class ProxyActorC: public ActorC {
public:
	virtual const Action *think();
	void setAction(Action const *a) {next = a;}
	// May be null
	Action const *getAction() {return next;}
	ProxyActorC(Entity *parent): ActorC(parent) {}
private:
	Action const *next = &MoveAction::Wait;
};


#endif // ACTOR_HPP
