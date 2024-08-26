//#include "Tests.h"
//#include <assert.h>
//#include <iostream>
//
//using namespace std;
//
//void Tests::test_dog()
//{
//	Dog d = Dog("Husky", "Mia", 10, "https://huskymia.jpg");
//	assert(d.get_breed() == "Husky");
//	assert(d.get_name() == "Mia");
//	assert(d.get_age() == 10);
//	assert(d.get_photo() == "https://huskymia.jpg");
//
//	cout << "Test dog" << endl;
//}
//
//void Tests::test_dynamic_array()
//{
//	DynamicVector<Dog> da;
//
//
//	assert(da.get_size() == 0);
//	Dog d = Dog("Husky", "Mia", 10, "https://huskymia.jpg");
//
//	da.add(d);
//	assert(da.get_size() == 1);
//	assert(da[0].get_breed() == "Husky");
//	assert(da[0].get_name() == "Mia");
//	assert(da[0].get_age() == 10);
//	assert(da[0].get_photo() == "https://huskymia.jpg");
//
//	DynamicVector<Dog> da1(da);
//	da = da1;
//	da = da;
//
//	da.remove(0);
//	assert(da.get_size() == 0);
//
//	cout << "Test dynamic array" << endl;
//}
//
//void Tests::test_repository()
//{
//	Repository r;
//	Repository r1(r);
//	r = r;
//
//	assert(r1.get_size() == 0);
//	assert(r.get_size() == 0);
//	Dog d = Dog("Husky", "Mia", 10, "https://huskymia.jpg");
//
//	r.add_repo(d);
//	assert(r.get_size() == 1);
//
//	DynamicVector<Dog> da = r.get_all_repo();
//
//	assert(da[0].get_breed() == "Husky");
//	assert(da[0].get_name() == "Mia");
//	assert(da[0].get_age() == 10);
//	assert(da[0].get_photo() == "https://huskymia.jpg");
//
//	r.remove_repo(0);
//	assert(r.get_size() == 0);
//
//	r.add_repo(d);
//	r.update_repo(Dog("Husky", "Mia", 2, "https://huskymia.jpg"), 0);
//	assert(r.get_all_repo()[0].get_age() == 2);
//
//	cout << "Test repository" << endl;
//}
//
//void Tests::test_service()
//{
//	Service s;
//	Service s1(s);
//	s = s;
//
//	assert(s.get_all().get_size() == 0);
//
//	s.add("Husky", "Mia", 10, "https://huskymia.jpg");
//	assert(s.get_all().get_size() == 1);
//	assert(s.get_all()[0].get_breed() == "Husky");
//	assert(s.get_all()[0].get_name() == "Mia");
//	assert(s.get_all()[0].get_age() == 10);
//	assert(s.get_all()[0].get_photo() == "https://huskymia.jpg");
//
//	cout << "Test add" << endl;
//
//	s.remove("Husky", "Mia");
//	assert(s.get_all().get_size() == 0);
//
//	cout << "Test remove" << endl;
//
//	s.add("Husky", "Mia", 10, "https://huskymia.jpg");
//	s.update("Husky", "Mia", 2, "https://huskymia.jpg");
//	assert(s.get_all()[0].get_age() == 2);
//	s.remove("Husky", "Mia");
//
//	cout << "Test update" << endl;
//
//	s.add_generated_dogs();
//	assert(s.get_all().get_size() == 10);
//
//	s.add("Husky", "Mia", 10, "https://huskymia.jpg");
//	assert(s.check_name_and_breed("Husky", "Mia") == 1);
//	assert(s.check_name_and_breed("Husky", "Mia1") == 0);
//	assert(s.get_all().get_size() == 11);
//
//	cout << "Test add generated" << endl;
//}
//
//void Tests::test_all()
//{
//	test_dog();
//	test_dynamic_array();
//	test_repository();
//	test_service();
//
//	cout << "All tests passed!" << endl << endl;
//}
