#include "service.h"

Service::Service() {}

/// <summary>
/// The constructor of the service class
/// </summary>
/// <param name="repo"> The repository </param>
Service::Service(const Repository& repo)
{
	this->repo = repo;
}

/// <summary>
/// This function assigns a service to another service
/// </summary>
/// <param name="service"> The service to assign </param>
/// <returns> A copy of the service </returns>
Service& Service::operator=(const Service& service)
{
	if (this == &service)
		return *this;
	//delete this->repo;
	this->repo = service.repo;
	return *this;
}

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
}

/// <summary>
/// Removes a dog from the repository with the given breed and name
/// </summary>
/// <param name="breed"> The breed of the dog </param>
/// <param name="name"> The name of the dog </param>
void Service::remove(const std::string& breed, const std::string& name)
{
	DynamicVector<Dog> dogs = this->repo.get_all_repo();
	for (int i = 0; i < dogs.get_size(); i++)
	{
		if (dogs[i].get_breed() == breed && dogs[i].get_name() == name)
		{
			this->repo.remove_repo(i);
			break;
		}
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
	DynamicVector<Dog> dogs = this->repo.get_all_repo();
	for (int i = 0; i < dogs.get_size(); i++)
	{
		if (dogs[i].get_breed() == breed && dogs[i].get_name() == name)
		{
			Dog new_dog{ breed, name, age, photo };
			this->repo.update_repo(new_dog, i);
			break;}}
}

/// <summary>
/// Gets all the dogs from the repository
/// </summary>
/// <returns>
/// A dynamic array containing all the dogs from the repository
/// </returns>
DynamicVector<Dog> Service::get_all()
{
	return this->repo.get_all_repo();
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
	DynamicVector<Dog> dogs = this->get_all();

	for (int i = 0; i < dogs.get_size(); i++)
	{
		if (dogs[i].get_breed() == breed && dogs[i].get_name() == name)
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
