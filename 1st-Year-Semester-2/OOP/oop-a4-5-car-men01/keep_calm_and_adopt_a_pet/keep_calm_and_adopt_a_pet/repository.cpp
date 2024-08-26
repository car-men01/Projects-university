#include "repository.h"

Repository::Repository() {}

/// <summary>
/// The constructor of the repository class
/// </summary>
/// <param name="repo"> The repository </param>
Repository::Repository(const Repository& repo)
{
	this->dogs = repo.dogs;
}

/// <summary>
/// This function assigns a repository to another repository
/// </summary>
/// <param name="repo"></param>
/// <returns></returns>
Repository& Repository::operator=(const Repository& repo)
{
	if (this == &repo)
		return *this;
	this->dogs = repo.dogs;
	return *this;
}

/// <summary>
/// The destructor of the repository class
/// </summary>
Repository::~Repository() {}

/// <summary>
/// Adds a dog to the repository
/// </summary>
/// <param name="dog"> The dog to be added to the repository </param>
void Repository::add_repo(const Dog& dog)
{
	this->dogs.add(dog);
}

/// <summary>
/// Removes a dog from the repository
/// </summary>
/// <param name="index"> The index of the dog to be removed </param>
void Repository::remove_repo(int index)
{
	this->dogs.remove(index);
}

/// <summary>
/// Updates a dog from the repository
/// </summary>
/// <param name="dog"> The dog to update with </param>
/// <param name="index"> The index of the dog to be updated </param>
void Repository::update_repo(const Dog& dog, int index)
{
	this->dogs.update(dog, index);
}

/// <summary>
/// Gets the size of the repository
/// </summary>
/// <returns>
/// The size of the repository
/// </returns>
int Repository::get_size()
{
	return this->dogs.get_size();
}

/// <summary>
/// Gets all the dogs from the repository
/// </summary>
/// <returns>
/// A dynamic array containing all the dogs from the repository
/// </returns>
DynamicVector<Dog> Repository::get_all_repo()
{
	return this->dogs;
}
