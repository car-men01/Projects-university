#include <iostream>
#include <crtdbg.h>
#include "UI.h"
#include "service.h"
#include "repository.h"
#include "dynamic_array.h"
#include "dog.h"

using namespace std;

int main() 
{
	
	Repository repo = Repository();
	Service service = Service(repo);
	UI ui = UI(service);

	Tests tests;
	tests.test_all();

	//ui.run();

	return 0;
}
