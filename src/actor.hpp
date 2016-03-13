#ifndef ACTOR_HPP
#define ACTOR_HPP

#include "entity.hpp"

/* * An action is some sort of thing an Entity can do.
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

class MoveAction: public Action {
public:
	virtual void execute(Entity *e) const;
	// Static instances of MoveAction
	static MoveAction const North;
	static MoveAction const South;
	static MoveAction const East;
	static MoveAction const West;
	static MoveAction const Wait;
private:
	MoveAction(int duration, int d_x, int d_y): Action(duration), d_x(d_x), d_y(d_y) {}
	int d_x;
	int d_y;
};

class ActorC: public Component {
public:
	virtual const Action *think() = 0;
	virtual void update(int delta) final;
protected:
	ActorC(Entity *parent): Component(parent) {}
private:
	int cooldown = 0;
	Action const *current = &MoveAction::Wait;
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
 * This actor does whatever we tell it to do.
 */
class ProxyActorC: public ActorC {
public:
	virtual const Action *think();
	void setAction(Action const *a) {next = a;}
	ProxyActorC(Entity *parent): ActorC(parent) {}
private:
	Action const *next = &MoveAction::Wait;
};

#endif // ACTOR_HPP
