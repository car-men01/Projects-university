#include "Repository.h"
#include "RepoExceptions.h"
#include <string>
#include <fstream>
#include "Utils.h"

using namespace std;

Repository::Repository(const std::string& filename)
{
    this->filename = filename;
    this->readFromFile();
}

/// <summary>
/// The destructor of the repository class
/// </summary>
Repository::~Repository() {}

Dog Repository::find_by_breed_and_name(const std::string& breed, const std::string& name) const
{
    for (auto d : this->dogs)
    {
        if (d.get_breed() == breed && d.get_name() == name)
            return d;
    }
    return Dog{};
}

/// <summary>
/// Adds a dog to the repository
/// </summary>
/// <param name="dog"> The dog to be added to the repository </param>
void Repository::add_repo(Dog dog)
{
    if (this->find_by_breed_and_name(dog.get_breed(), dog.get_name()).get_name() != "")
        throw DuplicateDogException();
    this->dogs.push_back(dog);
    this->writeToFile();
}

/// <summary>
/// Removes a dog from the repository
/// </summary>
/// <param name="index"> The index of the dog to be removed </param>
void Repository::remove_repo(int index)
{
    if (index < 0 || index >= this->dogs.size())
        throw InexistentDogException();
    this->dogs.erase(this->dogs.begin() + index);
    this->writeToFile();
}

/// <summary>
/// Updates a dog from the repository
/// </summary>
/// <param name="dog"> The dog to update with </param>
/// <param name="index"> The index of the dog to be updated </param>
void Repository::update_repo(Dog dog, int index)
{
    if (index < 0 || index >= this->dogs.size())
        throw InexistentDogException();
    this->dogs[index] = dog;
    this->writeToFile();
}

/// <summary>
/// Adds a dog to the adoption list
/// </summary>
/// <param name="d"> The dog to be added </param>
void Repository::add_adoption_list(Dog d)
{
    this->adoption_list.push_back(d);
}

/// <summary>
/// Removes a dog from the adoption list
/// </summary>
/// <param name="index"> The index of the dog to be removed </param>
void Repository::remove_adoption_list(int index)
{
    this->adoption_list.erase(this->adoption_list.begin() + index);
}

/// <summary>
/// Gets the size of the repository
/// </summary>
/// <returns>
/// The size of the repository
/// </returns>
int Repository::get_size()
{
    return this->dogs.size();
}

/// <summary>
/// Gets all the dogs from the repository
/// </summary>
/// <returns>
/// A dynamic array containing all the dogs from the repository
/// </returns>
std::vector<Dog> Repository::get_all_repo()
{
    return this->dogs;
}

std::vector<Dog> Repository::get_adoption_list()
{
    return this->adoption_list;
}

Dog Repository::get_dog(int index)
{
    return this->dogs[index];
}

void Repository::readFromFile()
{
    ifstream file(this->filename);

    if (!file.is_open())
        throw FileException("The file could not be opened!");

    Dog d;
    while (file >> d)
        this->dogs.push_back(d);

    file.close();
}

void Repository::writeToFile()
{
    ofstream file(this->filename);
    if (!file.is_open())
        throw FileException("The file could not be opened!");

    for (const auto& d : this->dogs) {
        file << d;
    }

    file.close();
}
