#include "Service.h"
#include <iostream>
#include <QDebug>


Service::Service(const Repository& repo) : repo { repo } {}

/// <summary>
/// The constructor of the service class
/// </summary>
/// <param name="repo"> The repository </param>
Service::Service(const Repository& repo, AdoptionList* adoption_list) :
	repo{ repo }, adoption_list{ adoption_list } {}


/// <summary>
/// This function assigns a service to another service
/// </summary>
/// <param name="service"> The service to assign </param>
/// <returns> A copy of the service </returns>

/*
Service& Service::operator=(const Service& service)
{
	if (this == &service)
		return *this;
	this->repo = service.repo;
	return *this;
}
*/

/// <summary>
/// The destructor of the service class
/// </summary>
Service::~Service() {}

/// <summary>
/// Adds a dog to the repository
/// </summary>
/// <param name="breed"> The breed of the dog </param>
/// <param name="name"> The name of the dog </param>q
/// <param name="age"> The age of the dog </param>
/// <param name="photo"> The photo link of the dog </param>
void Service::add(const std::string& breed, const std::string& name, const int age, const std::string& photo)
{
	Dog dog{ breed, name, age, photo };
	this->repo.add_repo(dog);

	//this->undoActions.push_back(ActionAdd{ this->repo, dog });
	this->undoActions.push_back(make_unique<ActionAdd>(this->repo, dog));
	this->redoActions.clear();
}

/// <summary>
/// Removes a dog from the repository with the given breed and name
/// </summary>
/// <param name="breed"> The breed of the dog </param>
/// <param name="name"> The name of the dog </param>
void Service::remove(const std::string& breed, const std::string& name)
{
	int i = 0;
	for (const Dog& dog : this->repo.get_all_repo())
	{
		if (dog.get_breed() == breed && dog.get_name() == name)
		{
			this->repo.remove_repo(i);

			this->undoActions.push_back(make_unique<ActionRemove>(this->repo, dog));
			this->redoActions.clear();
			break;
		}
		i++;
	}
}

/// <summary>
/// Updates a dog from the repository with the given breed and name
/// </summary>
/// <param name="breed"> The breed of the dog </param>
/// <param name="name"> The name of the dog </param>
/// <param name="age"> The new age to update with </param>
/// <param name="photo"> The new photo link to update with </param>
void Service::update(const std::string& breed, const std::string& name, const int age, const std::string& photo)
{
	int i = 0;
	for (const Dog& dog : this->repo.get_all_repo())
	{
		if (dog.get_breed() == breed && dog.get_name() == name)
		{
			Dog new_dog{ breed, name, age, photo };
			this->repo.update_repo(new_dog, i);

			this->undoActions.push_back(make_unique<ActionUpdate>( this->repo, dog, new_dog ));
			this->redoActions.clear();
			break;
		}
		i++;
	}
}

void Service::undo()
{
	if (undoActions.empty())
		throw std::exception("No more undos!");

	/*Action* action = &this->undoActions.back();
	action->executeUndo();
	this->redoActions.push_back(*action);
	this->undoActions.pop_back();*/

	undoActions.back()->executeUndo();
	redoActions.push_back(move(undoActions.back()));
	undoActions.pop_back();
}

void Service::redo()
{
	if (redoActions.empty())
		throw std::exception("No more redos!");

	/*Action* action = &this->redoActions.back();
	action->executeRedo();
	this->undoActions.push_back(*action);
	this->redoActions.pop_back();*/

	redoActions.back()->executeRedo();
	undoActions.push_back(move(redoActions.back()));
	redoActions.pop_back();
}

std::vector<Dog> Service::get_by_breed_and_age(int age, const std::string& breed)
{
	std::vector<Dog> dogs = this->repo.get_all_repo();
	std::vector<Dog> result;

	/*for (auto dog : dogs)
	{
		if (dog->get_breed() == breed && dog->get_age() < age)
			result.push_back(dog);
	}*/

	std::copy_if(dogs.begin(), dogs.end(), std::back_inserter(result),
		[age, breed](const Dog& dog)
		{ return dog.get_breed() == breed && dog.get_age() < age; });

	return result;
}

std::map<std::string, int> Service::get_by_breed() {
	std::vector<Dog> dogs = this->repo.get_all_repo();
	std::map<std::string, int> result;

	for (const Dog& dog : dogs)
	{
		if (result.find(dog.get_breed()) == result.end())
			result[dog.get_breed()] = 1;
		else
			result[dog.get_breed()]++;
	}

	return result;
}

/// <summary>
/// Gets all the dogs from the repository
/// </summary>
/// <returns>
/// A dynamic array containing all the dogs from the repository
/// </returns>
std::vector<Dog> Service::get_all()
{
	return this->repo.get_all_repo();
}


AdoptionList* Service::get_all_adopted()
{
	return this->adoption_list;
}

void Service::add_to_adopted(const Dog& dog) {
	if (this->adoption_list == nullptr)
		return;
	this->adoption_list->add(dog);
}

void Service::remove_from_adopted(const std::string& breed, const std::string& name) {
	int i = 0;
	for (const Dog& dog : this->adoption_list->getDogs())
	{
		if (dog.get_breed() == breed && dog.get_name() == name)
		{
			this->adoption_list->remove(i);
			break;
		}
		i++;
	}
}

void Service::updateAdoptionList(FileAdoptionList* newl)
{
	/*if (this->adoption_list != nullptr)
		delete this->adoption_list;*/
	this->adoption_list = newl;
}

void Service::show_adoption_list()
{
	if (this->adoption_list == nullptr)
		return;
	this->adoption_list->show();
}

void Service::next_adoption_list()
{
	if (this->adoption_list == nullptr)
		return;
	this->adoption_list->next();
}

void Service::save_adoption_list()
{
	if (this->adoption_list == nullptr)
		return;
	/*this->adoption_list->set_filename(filename);
	this->adoption_list->save();*/

	FileAdoptionList* ad_list = dynamic_cast<FileAdoptionList*>(this->adoption_list);
	if (ad_list != nullptr)
		ad_list->writeToFile();
}

void Service::open_adoption_list()
{
	if (this->adoption_list == nullptr)
		return;

	FileAdoptionList* ad_list = dynamic_cast<FileAdoptionList*>(this->adoption_list);
	if (ad_list != nullptr)
		ad_list->displayAdoptionList();
}

/// <summary>
/// Checks if a dog with the given name and breed already exists in the repository
/// </summary>
/// <param name="breed"> The breed of the dog </param>
/// <param name="name"> The name of the dog </param>
/// <returns>
/// 1 - if the dog exists, 0 - otherwise
/// </returns>
int Service::check_name_and_breed(const std::string& breed, const std::string& name)
{
	std::vector<Dog> dogs = this->get_all();

	for (const Dog& dog : this->repo.get_all_repo())
	{
		if (dog.get_breed() == breed && dog.get_name() == name)
			return 1;
	}
	return 0;
}

/// <summary>
/// Adds 10 dogs to the repository
/// </summary>
void Service::add_generated_dogs()
{
	Dog dog1{ "Beagle", "Rex", 2, "https://forestry.com/wp/wp-content/uploads/2024/01/2-405.webp" };
	Dog dog2{ "Beagle", "Lucy", 10, "https://freerangestock.com/sample/132676/golden-retriever-in-water-.jpg" };
	Dog dog3{ "Pug", "Reggie", 1, "https://image.petmd.com/files/styles/863x625/public/2022-10/pug-dog-breed.jpeg" };
	Dog dog4{ "Labrador", "Buddy", 4, "https://upload.wikimedia.org/wikipedia/commons/d/d4/Labrador_Retriever_-_Yellow.JPG" };
	Dog dog5{ "Husky", "Kyra", 5, "https://thumbs.dreamstime.com/b/husky-4135989.jpg" };
	Dog dog6{ "Chow chow", "Apollo", 6, "https://www.zooplus.ro/ghid/wp-content/uploads/2022/06/caine-chow-chow-roscat.webp" };
	Dog dog7{ "Bulldog", "Jojo", 7, "https://cdn.britannica.com/08/234208-050-C9A21C4C/English-bulldog-dog.jpg" };
	Dog dog8{ "Chihuahua", "Logan", 8, "https://i.pngimg.me/thumb/f/720/6001911752818688.jpg" };
	Dog dog9{ "Dalmatian", "Dixie", 9, "https://upload.wikimedia.org/wikipedia/commons/6/68/Sun_Dog_Dalmatian.jpg" };
	Dog dog10{ "Dobermann", "Tux", 10, "https://cdn.britannica.com/75/234475-050-7D0C0D7E/Doberman-pinscher-dog.jpg" };

	this->repo.add_repo(dog1);
	this->repo.add_repo(dog2);
	this->repo.add_repo(dog3);
	this->repo.add_repo(dog4);
	this->repo.add_repo(dog5);
	this->repo.add_repo(dog6);
	this->repo.add_repo(dog7);
	this->repo.add_repo(dog8);
	this->repo.add_repo(dog9);
	this->repo.add_repo(dog10);
}
