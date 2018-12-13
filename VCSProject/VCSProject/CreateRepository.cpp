#include <iostream>
#include <string>
#include <experimental/filesystem>
#include "CreateRepository.h"
//#include "checkout.h"

namespace fs = std::experimental::filesystem;

int main() {
	std::string userInput;
	std::string userRepo;
	std::string userSource;
	std::string userTarget;
	std::string userManFile;

	std::cout << fs::current_path() << "\n\n" << std::endl;

	std::cout << "Name of directory: " << std::endl;
	std::cin >> userInput;
	std::cout << "Name of repo: " << std::endl;
	std::cin >> userRepo;
	createRepository(userInput, userRepo);

	std::cout<< "Name of Repo to Checkout: "<< std ::endl;
	std::cin >> userSource;
	std::cout << "New repository name: "<<std::endl;
	std::cin >> userTarget;
	std::cout<< "Name of Manifest file to log."<<std::endl;
	std::cin >> userManFile;
	checkout(userSource, userTarget, userManFile);

	return 0;

}
