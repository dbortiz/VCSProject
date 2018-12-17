/*This header file does not work.*/

#pragma once
#include <iostream>
#include <experimental/filesystem>
#include <fstream>
#include "CreateRepository.h"

namespace fs = std::experimental::filesystem;

void findManifest(fs::path& currentPath, fs::path& manifestPath) {
	for (auto it : fs::recursive_directory_iterator(currentPath)) {
		if (it.path().filename() == "manifest.txt") {
			currentPath = it.path().parent_path();
			manifestPath = it.path();
		}
	}
}

void contentsInManifest(std::vector<std::string>& files, fs::path manifestPath) {
	std::ifstream contentsOfManifest;
	std::string artifact;
	contentsOfManifest.open(manifestPath);

	while (contentsOfManifest >> artifact) {
		files.push_back(artifact);
	}
	
	contentsOfManifest.close();
}

void merge(std::string mainline, std::string firstRepo, std::string secondRepo) {
	// Paths named from project instructions
	fs::path G = mainline;
	fs::path T = firstRepo;
	fs::path R = secondRepo;
	
	// Paths for manifest file
	fs::path manifestPathG;
	fs::path manifestPathT;
	fs::path manifestPathR;

	findManifest(G, manifestPathG);
	findManifest(T, manifestPathT);
	findManifest(R, manifestPathR);

	// Vectors to hold artifacts
	std::vector<std::string> GFiles;
	std::vector<std::string> TFiles;
	std::vector<std::string> RFiles;

	contentsInManifest(GFiles, manifestPathG);
	contentsInManifest(TFiles, manifestPathT);
	contentsInManifest(RFiles, manifestPathR);

	for (auto itG = fs::recursive_directory_iterator(G); itG != fs::recursive_directory_iterator(); ++itG) {
		fs::path pathG = itG->path();
		std::string tempArtifactG;

		if (fs::is_regular_file(pathG)) {
			tempArtifactG = artifactID(pathG);
		}

		for (auto itT = fs::recursive_directory_iterator(T); itT != fs::recursive_directory_iterator(); ++itT) {
			fs::path pathT = itT->path();
			std::string targetPath = pathT.string();
			targetPath = targetPath.substr(targetPath.find_first_of("\\"));

			for (std::vector<std::string>::iterator vectorItT = TFiles.begin(); vectorItT != TFiles.end(); ++vectorItT) {
				if (tempArtifactG == *vectorItT) {
					std::cout << "tempArtifactG: " << tempArtifactG << "\n";
					std::cout << "*vectorItT: " << *vectorItT << "\n";
					std::cout << "pathg: " << pathG << "\n";
					std::cout << "patht: " << pathT << "\n";
					
				}
				else {
					std::string newGName = pathG.parent_path().string() + "\\" + pathG.filename().stem().string() + "_MG" + pathG.extension().string();
					if (pathG == newGName) {
						std::string newTName = pathG.parent_path().string() + "\\" + pathG.filename().stem().string() + "_MT" + pathG.extension().string();
						if (pathG == newTName) {
							std::cout << "path G and path T good " << std::endl;
						}
						else {
							std::ofstream addTFile;
							addTFile.open(newTName);
							addTFile.close();
							fs::copy_file(pathT, newTName, fs::copy_options::overwrite_existing);
						}
						
					}
					else {
						std::string newTName = pathG.parent_path().string() + "\\" + pathG.filename().stem().string() + "_MT" + pathG.extension().string();
						fs::rename(pathG, newGName);
						if (pathG == newTName) {
							std::cout << "path T good in else" << std::endl;
						}
						else {
							std::ofstream addTFile;
							addTFile.open(newTName);
							addTFile.close();
							fs::copy_file(pathT, newTName, fs::copy_options::overwrite_existing);
						}
					}
				}
				

			}

		}
		
		/*for (auto itR = fs::recursive_directory_iterator(R); itR != fs::recursive_directory_iterator(); ++itR) {
			fs::path pathR = itR->path();
			std::string targetPath = pathR.string();
			targetPath = targetPath.substr(targetPath.find_first_of("\\"));

			for (std::vector<std::string>::iterator vectorItT = TFiles.begin(); vectorItT != TFiles.end(); ++vectorItT) {

				
				if (tempArtifactG == *vectorItT) {
					std::cout << "tempArtifactG: " << tempArtifactG << "\n";
					std::cout << "*vectorItT: " << *vectorItT << "\n";
					std::cout << "pathg: " << pathG << "\n";
					std::cout << "pathr: " << pathR << "\n";

				}
				else {
					std::string newGName = pathG.parent_path().string() + "\\" + pathG.filename().string() + "_MG" + pathG.extension().string();
					if (pathG == newGName) {
						std::string newTName = pathG.parent_path().string() + "\\" + pathG.filename().string() + "_MR" + pathG.extension().string();
						std::ofstream addTFile;
						addTFile.open(newTName);
						addTFile.close();
						fs::copy_file(pathR, newTName, fs::copy_options::overwrite_existing);
					}
					else {
						std::string newTName = pathG.parent_path().string() + "\\" + pathG.filename().string() + "_MR" + pathG.extension().string();
						fs::rename(pathG, newGName);
						std::ofstream addTFile;
						addTFile.open(newTName);
						addTFile.close();
						fs::copy_file(pathR, newTName, fs::copy_options::overwrite_existing);
					}
				}
				
			}

		}*/
		
	}

}