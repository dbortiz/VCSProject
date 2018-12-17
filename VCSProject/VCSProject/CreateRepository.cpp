/*
	Team Name:
			DAA
	Authors:
			Dan Ortiz				dbortiz@csu.fullerton.edu
			Aaron Jimenez-Lopez		aaronjimenez97@csu.fullerton.edu
	Description:
			This cpp file is simply a menu-type function to choose between the offered 
			functions (described in the project details). You SHOULD HAVE an already existing
			folder for this program to work. Ideally, you should create a repo first. Then,
			you may label it. After that, you can check out and check in the newly created
			repository, respectively.

*/
#include <iostream>
#include <string>
#include <experimental/filesystem>
#include <map>
#include "CreateRepository.h"
#include "Label.h"
#include "CheckOut.h"
#include "CheckIn.h"
#include "Merge.h"

namespace fs = std::experimental::filesystem;

extern std::map<std::string, fs::path> labels;

int main() {
	int userSelection;

	std::cout << "What would you like to do?\n" << std::endl;
	std::cout << "(1) Create repository.\n(2) Create label.\n(3) Checkout.\n(4) Checkin." << std::endl;
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

		std::cout << "\n\n";

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

		std::cout << "\n\n";

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
		std::cout << "Name of the label or manifest path:" << std::endl;
		std::cin >> labelName;
		std::cout << "Name of target directory:" << std::endl;
		std::cin >> userTargetDirectory;

		std::cout << "\n\n";

		checkOut(userDirectory, labelName, userTargetDirectory);

		break;
	}

	case 4:
	{
		std::string checkingInRepository;
		std::string checkedOutRepository;
		std::cout << "You have selected: 4. Check in." << std::endl;

		std::cout << "Current path: " << fs::current_path() << "\n\n" << std::endl;

		std::cout << "Name of repository checking in to:" << std::endl;
		std::cin >> checkingInRepository;
		std::cout << "Name of checked out repository:" << std::endl;
		std::cin >> checkedOutRepository;
		
		std::cout << "\n\n";

		checkIn(checkingInRepository, checkedOutRepository);

		break;
	}

	// This was intended for Merge.
	/*
	case 5:
	{
		std::string mainline;
		std::string repository1;
		std::string repository2;

		std::cout << "You have selected: 5. Merge." << std::endl;

		std::cout << "Current path: " << fs::current_path() << "\n\n" << std::endl;

		std::cout << "Name of directory:" << std::endl;
		std::cin >> mainline;
		std::cout << "Name of 1st repository:" << std::endl;
		std::cin >> repository1;
		std::cout << "Name of 2nd repository:" << std::endl;
		std::cin >> repository2;

		std::cout << "\n\n";

		merge(mainline, repository1, repository2);

		break;
	}
	*/
	default:
		std::cout << "Invalid option" << std::endl;
		break;
	}
	return 0;

}