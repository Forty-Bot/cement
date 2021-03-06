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
	virtual void execute(Entity *e) const = 0;
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
	virtual void execute(Entity *e) const;
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
	void update(int delta);
	// The priority (low numbers==high priority) this entity has in the actors queue
	int priority;
protected:
	ActorC(Entity *parent): Component(parent),priority(0)  {}
};

/*
 * This actor does nothing.
 */
class NullActorC: public ActorC {
public:
	virtual const Action *think();
	NullActorC(Entity *parent): ActorC(parent) {}
};

/*
 * This actor runs in circles forever
 */
class CircleActorC: public ActorC {
public:
	virtual const Action *think();
	CircleActorC(Entity *parent): ActorC(parent) {}
private:
	// What direction we are running
	int state = -1;
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
	Action const *next = NULL;
};

#endif // ACTOR_HPP
