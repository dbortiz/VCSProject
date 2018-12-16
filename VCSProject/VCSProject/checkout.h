#include <iostream>
#include <string>
#include <experimental/filesystem>


namespace fs = std::experimental::filesystem;


void checkout(std::string,std::string,std::string);

void checkout(std::string repoToCheckout, std::string directoryTarget, std::string manifestFile)  //"checks out repo (copies the repository)"
{
  	std:: ofstream nameManfile_;
    fs::path repoPath = repoToCheckout;
 		fs::path targetPath = directoryTarget;
    fs::copy(repoPath,targetPath, fs::copy_options::recursive);		//Creates new repository
    //Would like to move this file to inside the folder and check for it there
    fs::path newManifestPath = targetPath /= manifestFile + ".txt";
  	nameManfile_.open(newManifestPath,std::fstream::app);
  	std:: cout <<"\nChecking out: "<<repoPath<<"\nNew path: "<< targetPath << std::endl;
 		nameManfile_ << "Checked Out  "<< repoPath <<std::endl;

 		nameManfile_.close();
 }
