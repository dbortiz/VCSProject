/*
	Team Name:
			DAA
	Authors:
			Dan Ortiz				dbortiz@csu.fullerton.edu
			Aaron Jimenez-Lopez		aaronjimenez97@csu.fullerton.edu
	Description:
			This header file is for the check in function. This function looks through 
			the checked out repository and appends any changes as artifacts to a new
			manifest file. The new artifacts are put under their folder names accordingly.

*/

#pragma once
#include <iostream>
#include <experimental/filesystem>
#include <fstream>
#include <vector>
#include "CreateRepository.h"

namespace fs = std::experimental::filesystem;

void checkIn(std::string repository, std::string checkedOut) {
	fs::path currentRepository = repository;
	fs::path checkedOutRepository = checkedOut;
	fs::path manifestPath;

	std::vector<std::string> files;

	// Check for manifest file or label
	for (auto it : fs::recursive_directory_iterator(currentRepository)) {
		if (it.path().filename() == "manifest.txt") {
			// std::cout << "Found manifest" << std::endl;
			currentRepository = it.path().parent_path();
			manifestPath = it.path();
		}
	}

	// Opens manifest file and inputs artifacts in vector
	std::ifstream contentsOfManifest;
	std::string artifact;
	contentsOfManifest.open(manifestPath);

	while (contentsOfManifest >> artifact) {
		files.push_back(artifact);
	}

	contentsOfManifest.close();

	// Counts how many labels there are
	std::ifstream labelCount;
	std::string tempLine;
	int count = 0;

	labelCount.open("FileToHoldLabels.txt");
	
	while (std::getline(labelCount, tempLine)) {
		count++;
	}

	labelCount.close();
	
	// Creates new manifest file
	std::ofstream newManifestFile;
	std::string newManifestName = "manifest" + std::to_string(count) + ".txt";
	fs::path newManifestPath = currentRepository /= newManifestName;

	newManifestFile.open(newManifestPath, std::ios_base::app);

	// Iterates through the checked out repository
	for (auto it = fs::recursive_directory_iterator(checkedOutRepository); it != fs::recursive_directory_iterator(); ++it) {
		fs::path path = it->path();

		std::string targetPath = path.string();
		targetPath = targetPath.substr(targetPath.find_first_of('\\'));

		// Checks for the original artifacts inside checked out repository
		for (std::vector<std::string>::iterator vectorIt = files.begin(); vectorIt != files.end(); ++vectorIt) {
			fs::path tempTargetPath = targetPath;
			std::string tempArtifact;

			// Checks if the file has changed using the check sum
			if (tempTargetPath.filename() == *vectorIt) {
				tempArtifact = artifactID(path);

				// If no changes; add old artifact into new manifest file
				if (tempArtifact == *vectorIt) {
					newManifestFile << *vectorIt << std::endl;
					std::cout << "No changes made in file " << *vectorIt << std::endl;
				}

				// else changes; add new artifact into new manifest file and insert into checking in repository
				else {
					// Create empty text file but with artifact in current repository
					std::string pathToAddArtifact = currentRepository.parent_path().string() + tempTargetPath.parent_path().string() + "\\" + tempArtifact;
					std::ofstream createEmptyFile;
					createEmptyFile.open(pathToAddArtifact);
					createEmptyFile.close();

					newManifestFile << tempArtifact << std::endl;
					
					fs::copy_file(path, pathToAddArtifact, fs::copy_options::overwrite_existing);
					std::cout << "Changes have been made in file " << *vectorIt << ". New artifact created: " << tempArtifact << std::endl;
				}
			}
		}
	}

	newManifestFile.close();
}