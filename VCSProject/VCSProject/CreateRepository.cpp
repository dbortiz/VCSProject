#include <iostream>
#include <string>
#include <experimental/filesystem>
#include <map>
#include "CreateRepository.h"
#include "CheckOut.h"
#include "CheckIn.h"
#include "Label.h"

namespace fs = std::experimental::filesystem;

extern std::map<std::string, fs::path> labels;

int main() {
	int userSelection;

	std::cout << "What would you like to do?\n" << std::endl;
	std::cout << "(1) Create repository.\n(2) Create label.\n(3) Checkout.\n(4) Checkin.\n" << std::endl;


	do{

		std::cin >> userSelection;
	switch (userSelection)
	{
	case 1: {
		std::string userInput;
		std::string userRepo;
		std::cout << "You have selected: 1. Create repository." << std::endl;

		std::cout << fs::current_path() << "\n\n" << std::endl;

		std::cout << "Name of directory: " << std::endl;
		std::cin >> userInput;
		std::cout << "Name of repo: " << std::endl;
		std::cin >> userRepo;

		createRepository(userInput, userRepo);
		break;
	}

	case 2:
	{
		std::string userDirectory;
		std::string userManifestFile;
		std::string newLabel;
		std::cout << "You have selected: 2. Create label." << std::endl;

		std::cout << "Current path: " << fs::current_path() << "\n\n" << std::endl;

		std::cout << "Name of existing directory: " << std::endl;
		std::cin >> userDirectory;
		std::cout << "Name of manifest file: " << std::endl;
		std::cin >> userManifestFile;
		std::cout << "Name of new label for manifest file: " << std::endl;
		std::cin >> newLabel;

		createLabel(userDirectory, userManifestFile, newLabel);

		break;
	}
	case 3:
	{
		std:: string userSource;
		std:: string userTarget;
		std:: string userManFile;
		std::cout<< "You have selected: 3. Checkout."<< std::endl;
		std::cout<< "Name of Repo to Checkout: "<< std ::endl;
		std::cin >> userSource;
		std::cout << "New Repository name: "<<std::endl;
		std::cin >> userTarget;
		std::cout<< "Name of Manifest file to log."<<std::endl;
		std::cin >> userManFile;

		checkOut(userSource, userTarget, userManFile);

		break;
	}
	case 4:
	{
		std:: string userRepo1;
		std:: string userRepo2;
		std:: cout<< "You have selected: 4. Checkin."<<std::endl;
		std:: cout<< "Name of Repository One: "<< std::endl;
		std:: cin >> userRepo1;
		std:: cout<< "Name of Repository Two: "<<std::endl;
		std:: cin >> userRepo2;

		checkin(userRepo1,userRepo2);

		break;
	}
	default:
		std::cout << "Invalid option" << std::endl;
		break;
	}
	std::cout <<"To exit enter 5"<<std::endl;
}while(userSelection!=5);
	return 0;

}
