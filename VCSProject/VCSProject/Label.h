#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;
// Needs target's filename or label.

std::map<std::string, fs::path> labels;

// Function to create labels and store in text file
void createLabel(std::string existingDirectory, std::string manifestFile, std::string newLabel) try {
	fs::path currentPath = existingDirectory;
	std::string textName = manifestFile;
	std::string linkName = newLabel;

	std::ofstream labelFile;
	labelFile.open("FileToHoldLabels.txt", std::ios_base::app);


	for (auto it : fs::recursive_directory_iterator(currentPath)) {
		if (it.path().filename() == textName){
			labelFile << linkName << " " << it.path() << std::endl;
			std::cout << "Label created successfully." << std::endl;
		}
	}
	labelFile.close();
}
catch(const fs::filesystem_error &e){
	std::cout << e.what() << std::endl;
}

// Function to return path of found label in text file
bool lookForLabel(std::string labelName) {
	std::ifstream labelFile("FileToHoldLabels.txt");
	std::string linkName;
	fs::path pathToLabel;

	if (labelFile.is_open()) {
		while (labelFile >> linkName >> pathToLabel) {
			labels.insert(std::pair<std::string, fs::path>(linkName, pathToLabel));
			// std::cout << "linkName: " << linkName << "\npathToLabel: " << pathToLabel << std::endl;
		}
	}


	std::map<std::string, fs::path>::iterator it;
	for (it = labels.begin(); it != labels.end(); ++it) {
		if (it->first == labelName) {
			std::cout << "Found label!" << std::endl;
			std::cout << it->second << std::endl;
			return true;
		}
	}
	return false;
}
