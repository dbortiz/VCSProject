#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;


std::string artifactID(fs::path);
void createRepository(std::string, std::string);

bool dirNotExist(const std::string& name);


std::string artifactID(fs::path directoryPath) {
	std::string artifactFile;
	int weights[5] = { 1, 3, 7, 11, 17 };
	int sum = 0;
	int size = 0;
	int positionInList = 0;
	char c;

	std::vector<char> charFromID;

	std::ifstream directoryFile;

	directoryFile.open(directoryPath);

	while (directoryFile.get(c)) {
		charFromID.push_back(c);
		size++;
	}

	directoryFile.close();

	for (std::vector<char>::iterator it = charFromID.begin(); it != charFromID.end(); ++it) {
		// Reset weights
		if (positionInList == 5) {
			positionInList = 0;
		}

		sum += (weights[positionInList] * int(*it));
		sum %= 2147483647;
		positionInList++;
	}


	artifactFile = std::to_string(sum) + "-L" + std::to_string(size) + directoryPath.extension().string();
	return artifactFile;
}


void createRepository(std::string existingDirectory, std::string newDirectory) {
	fs::path currentPath = existingDirectory;
	fs::path newPath = newDirectory;

	fs::create_directories(newPath);

	std::ofstream manifestFile;
	fs::path manifest = newPath /= "manifest.txt";

	manifestFile.open(manifest, std::ios_base::app);

	for (auto it = fs::recursive_directory_iterator(currentPath); it != fs::recursive_directory_iterator(); ++it) {
		fs::path path = it->path(); // Path to track current iterator path
		

		std::string targetPath = path.string(); // TargetPath is string to use substr
		targetPath = targetPath.substr(targetPath.find_first_of('\\')); // and get rest of path after TestFolder\'
		
		if (dirNotExist(path.string())) {
			fs::create_directories(newDirectory + targetPath);

			if (fs::is_regular_file(path)) {
				std::string newArtifact = artifactID(path);
				manifestFile << newArtifact << std::endl;
				fs::copy_file(path, newDirectory + targetPath + "\\" + newArtifact);
			}
		}
	}

	manifestFile.close();
}

// Function used from: https://stackoverflow.com/questions/12774207/fastest-way-to-check-if-a-file-exist-using-standard-c-c11-c
bool dirNotExist(const std::string& name) {
	if (FILE *file = fopen(name.c_str(), "r")) {
		fclose(file);
		return true;
	}
	else {
		return false;
	}
}