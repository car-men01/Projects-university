#include "AdoptionList.h"


AdoptionList::AdoptionList()
{
	this->current = 0;
}

AdoptionList::~AdoptionList() {}

Dog AdoptionList::getCurrentDog()
{
	if (this->dogs.size() == 0)
		return Dog{};
	return this->dogs[this->current];
}

vector <Dog> AdoptionList::getDogs()
{
	return this->dogs;
}

void AdoptionList::add(const Dog& d)
{
	this->dogs.push_back(d);
}

void AdoptionList::remove(int pos)
{
	this->dogs.erase(this->dogs.begin() + pos);
}

void AdoptionList::show()
{
	if (this->dogs.size() == 0)
		return;
	this->current = 0;
	Dog current_dog = this->getCurrentDog();
	current_dog.show_photo();
}

void AdoptionList::next()
{
	if (this->dogs.size() == 0)
		return;
	this->current++;
	Dog current_dog = this->getCurrentDog();
	current_dog.show_photo();
}

int AdoptionList::size()
{
	return this->dogs.size();
}

bool AdoptionList::isEmpty()
{
	return this->dogs.size() == 0;
}
