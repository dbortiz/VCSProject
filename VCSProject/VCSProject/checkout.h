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
    //Would like to move this file to inside the folder and check for it there
  	nameManfile_.open(manifestFile+".txt",std::fstream::app);
  	std:: cout <<"Checking out: "<<repoPath<<"\nNew path: "<< targetPath << std::endl;
 		nameManfile_ << "Checked Out  "<< repoPath <<std::endl;
 		fs::copy(repoToCheckout,targetPath, fs::copy_options::recursive);		//Creates new repository
 		nameManfile_.close();
 }
