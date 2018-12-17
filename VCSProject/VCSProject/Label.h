/*
	Team Name:
			DAA
	Authors:
			Dan Ortiz				dbortiz@csu.fullerton.edu
			Aaron Jimenez-Lopez		aaronjimenez97@csu.fullerton.edu
	Description:
			This header file is for the label function. The create label function takes a manifest
			name and its path. Then, a file, FileToHoldLabels.txt, to hold the labels is created and
			hold the manifest and its path. The look for label helper function is used to grab the 
			contents of the file holding the labels and refer to the path when called.
*/

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

	// Puts contents of the file into a map
	if (labelFile.is_open()) {
		while (labelFile >> linkName >> pathToLabel) {
			labels.insert(std::pair<std::string, fs::path>(linkName, pathToLabel));
		}
	}

	// Loops through the map to find a requested label (if it exists).
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
