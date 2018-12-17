#pragma once
#include <iostream>
#include <experimental/filesystem>
#include <string>
#include <fstream>
#include <vector>
#include "Label.h"

#include <chrono>
#include <iomanip>


namespace fs = std::experimental::filesystem;
using namespace std::chrono_literals;

void checkOut(std::string existingDirectory, std::string labelName, std::string targetDirectory) {
	std::string label = labelName;
	fs::path currentDirectory = existingDirectory;
	fs::path newDirectory = targetDirectory;
	fs::path manifestPath;

	// Vector to hold contents of manifest
	std::vector<std::string> files;

	// if-else loop to check whether label or user-input manifest file
	if (lookForLabel(label)) {
		std::map<std::string, fs::path>::iterator it;
		for (it = labels.begin(); it != labels.end(); ++it) {
			if (it->first == label) {
				std::cout << "Found label!" << std::endl;
				currentDirectory = it->second.parent_path();
				manifestPath = it->second;
			}
		}
	}
	else {
		for (auto it : fs::recursive_directory_iterator(currentDirectory)) {
			if (it.path().filename() == label) {
				std::cout << "Found manifest" << std::endl;
				std::cout << it.path().parent_path();
				currentDirectory = it.path().parent_path();
				manifestPath = it.path();
			}
		}
	}

	// Opens manifest file and inputs artifacts in vector
	std::fstream contentsOfManifest;
	std::string artifact;
	contentsOfManifest.open(manifestPath);

	auto ftime= fs::last_write_time(manifestPath);
	std::time_t cftime = decltype(ftime)::clock::to_time_t(ftime);
	contentsOfManifest << "Checking Out: " << manifestPath.string() << "Time done\t"  <<std::asctime(std::localtime(&cftime)) <<std::endl;

	while (contentsOfManifest >> artifact) {
		files.push_back(artifact);
	}

	// Creates target directory
	fs::create_directories(newDirectory);

	// Iterator to loop through existing directory (similar to CreateRepository() )
	for (auto it = fs::recursive_directory_iterator(currentDirectory); it != fs::recursive_directory_iterator(); ++it) {
		fs::path path = it->path(); // Path to track current iterator path

		std::string targetPath = path.string(); // TargetPath is string to use substr
		targetPath = targetPath.substr(targetPath.find_first_of('/')); // and get rest of path after TestFolder\'
		// Nested for-loop to iterate through vector and add file and path to target directory
		for (std::vector<std::string>::iterator vectorIt = files.begin(); vectorIt != files.end(); ++vectorIt) {
			fs::path tempTargetPath = targetPath;

			// Checks if artifact in manifest file is in existing directory and includes it in target directory
			if (tempTargetPath.filename() == *vectorIt) {
				fs::create_directories(targetDirectory + tempTargetPath.parent_path().string());
				fs::copy_file(path, targetDirectory + tempTargetPath.string());
			}

		}

	}
}
