#pragma once
#include "Repository.h"
#include "Dog.h"

class Action
{
public:
	virtual ~Action()=default;
	virtual void executeUndo() = 0;
	virtual void executeRedo() = 0;

};

class ActionAdd : public Action {
private:
	Repository& repo;
	Dog addedDog;
public:
	ActionAdd(Repository& repo, Dog addedDog);
	~ActionAdd() override;
	void executeUndo() override;
	void executeRedo() override;

};

class ActionRemove : public Action {
private:
	Repository& repo;
	Dog removedDog;
public:
	ActionRemove(Repository& repo, Dog removedDog);
	~ActionRemove() override;
	void executeUndo() override;
	void executeRedo() override;
};


class ActionUpdate : public Action {
private:
	Repository& repo;
	Dog oldDog;
	Dog newDog;
public:
	ActionUpdate(Repository& repo, Dog oldDog, Dog newDog);
	~ActionUpdate() override;
	void executeUndo() override;
	void executeRedo() override;
};

