#include <iostream>
#include <string>
#include <experimental/filesystem>
#include <map>
#include "CreateRepository.h"
#include "Label.h"
#include "CheckOut.h"
namespace fs = std::experimental::filesystem;

extern std::map<std::string, fs::path> labels;

int main() {
	int userSelection;

	std::cout << "What would you like to do?\n" << std::endl;
	std::cout << "(1) Create repository.\n(2) Create label.\n(3) Checkout." << std::endl;
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
		std::string userDirectory;
		std::string labelName;
		std::string userTargetDirectory;
		std::cout << "You have selected: 3. Check out." << std::endl;

		std::cout << "Current path: " << fs::current_path() << "\n\n" << std::endl;

		std::cout << "Name of existing directory:" << std::endl;
		std::cin >> userDirectory;
		std::cout << "Name of the label:" << std::endl;
		std::cin >> labelName;
		std::cout << "Name of target directory:" << std::endl;
		std::cin >> userTargetDirectory;

		checkOut(userDirectory, labelName, userTargetDirectory);
	}

	default:
		std::cout << "Invalid option" << std::endl;
		break;
	}

	return 0;

}