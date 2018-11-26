#include <iostream>
#include <string>
#include <experimental/filesystem>
#include "CreateRepository.h"

namespace fs = std::experimental::filesystem;

int main() {
	std::string userInput;
	std::string userRepo;
	std::cout << fs::current_path() << "\n\n" << std::endl;

	std::cout << "Name of directory: " << std::endl;
	std::cin >> userInput;
	std::cout << "Name of repo: " << std::endl;
	std::cin >> userRepo;
	createRepository(userInput, userRepo);

	return 0;

}