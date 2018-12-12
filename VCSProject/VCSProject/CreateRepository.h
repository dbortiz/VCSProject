#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <experimental/filesystem>
// #include "date.h"

namespace fs = std::experimental::filesystem;


std::string artifactID(fs::path);
void createRepository(std::string, std::string);

//void checkout(std::string,std::string,std::string);	//Addition to the File

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
	std::cout << "current path: " << currentPath << std::endl;
	std::ofstream maniFile_;
	maniFile_.open(currentPath+".txt");		//Creates the manifest file for the repo of the given path
	fs::copy(existingDirectory, newDirectory, fs::copy_options::recursive);
	for (auto &it : fs::recursive_directory_iterator(newDirectory)) {
		if (fs::is_regular_file(it.path())) {
		//	std::string timeStamp = date::format("%F %T",std::chrono::system_clock::now());	Trying to get the time stamp in the manifest file working
			std::string newArtifact = artifactID(it.path());
			//maniFile_ << it.path() << "\t"<<newArtifact << timeStamp <<std::endl;
			maniFile_ << it.path() << "\t"<<newArtifact << std::endl;
			fs::rename(it.path(), fs::path(it.path()).replace_filename(newArtifact));
		}
	}
	maniFile_.close();
}
//manfileExists()

checkout(std::string repoToCheckout, std::string directoryTarget, std::string manFile)  //"checks out repo (copies the repository)"
{
   fs::path repoPath = repoToCheckout;
	 if()
	 std:: cout <<"Checking out: current path: "<< repoToCheckout<< std::endl;
	 std::
 	 if(fs::exists )
 	 fs::copy(repoToCheckout, newDirectory, fs::copy_options::recur)
   std::ifstream directoryFile;
	 directoryFile.open(directoryPath);
}
