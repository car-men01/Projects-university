#include "Action.h"
#include <QDebug>


ActionAdd::ActionAdd(Repository& repo, Dog addedDog) : repo{ repo }, addedDog{ addedDog } {}

ActionAdd::~ActionAdd() {}

void ActionAdd::executeUndo()
{
	vector<Dog> dogs = this->repo.get_all_repo();
	int i = 0;
	for (auto d : dogs) {
		if (d.get_name() == this->addedDog.get_name() && d.get_breed() == this->addedDog.get_breed()) {
			//qDebug() << " remove dog from repo action \n" ;
			this->repo.remove_repo(i);
			break;
		}
		i++;
	}
}

void ActionAdd::executeRedo()
{
	this->repo.add_repo(this->addedDog);
}

ActionRemove::ActionRemove(Repository& repo, Dog removedDog) : repo{ repo }, removedDog{ removedDog } {}

ActionRemove::~ActionRemove() {}

void ActionRemove::executeUndo()
{
	this->repo.add_repo(this->removedDog);
}

void ActionRemove::executeRedo()
{
	vector<Dog> dogs = this->repo.get_all_repo();
	int i = 0;
	for (auto d : dogs) {
		if (d.get_name() == this->removedDog.get_name() && d.get_breed() == this->removedDog.get_breed()) {
			this->repo.remove_repo(i);
			break;
		}
		i++;
	}
}

ActionUpdate::ActionUpdate(Repository& repo, Dog oldDog, Dog newDog) : repo{ repo }, oldDog{ oldDog }, newDog{ newDog } {}

ActionUpdate::~ActionUpdate() {}

void ActionUpdate::executeUndo()
{
	vector<Dog> dogs = this->repo.get_all_repo();
	int i = 0;
	for (auto d : dogs) {
		if (d.get_name() == this->newDog.get_name() && d.get_breed() == this->newDog.get_breed()) {
			this->repo.update_repo(this->oldDog, i);
			break;
		}
		i++;
	}
}

void ActionUpdate::executeRedo()
{ 
	vector<Dog> dogs = this->repo.get_all_repo();
	int i = 0;
	for (auto d : dogs) {
		if (d.get_name() == this->oldDog.get_name() && d.get_breed() == this->oldDog.get_breed()) {
			this->repo.update_repo(this->newDog, i);
			break;
		}
		i++;
	}	
}

