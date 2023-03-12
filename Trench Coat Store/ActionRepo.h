#pragma once
#include "Repository.h"

class Action
{
public:
	Action();
	virtual void executeUndo() = 0;
	virtual void executeRedo() = 0;
};

class ActionAdd : public Action
{
private:
	TrenchCoat addedCoat;
	Repo& repo;
public:
	ActionAdd(TrenchCoat _addedCoat, Repo& _repo) : Action(), addedCoat{ _addedCoat }, repo{ _repo } {}
	void executeUndo() override;
	void executeRedo() override;
};

class ActionRemove : public Action
{
private:
	TrenchCoat removedCoat;
	Repo& repo;
public:
	ActionRemove(TrenchCoat _removedCoat, Repo& _repo) : Action(), removedCoat{ _removedCoat }, repo{ _repo } {}
	void executeUndo() override;
	void executeRedo() override;
};

class ActionUpdate : public Action
{
private:
	TrenchCoat oldForm;
	TrenchCoat updatedForm;
	Repo& repo;
public:
	ActionUpdate(TrenchCoat _oldForm, TrenchCoat _updatedForm, Repo& _repo) : Action(), oldForm{ _oldForm }, updatedForm{ _updatedForm }, repo{ _repo } {}
	void executeUndo() override;
	void executeRedo() override;
};

