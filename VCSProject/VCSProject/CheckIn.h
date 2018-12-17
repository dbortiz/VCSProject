#include <iostream>
#include <experimental/filesystem>
#include <string>
#include "CreateRepository.h"
#include "CheckOut.h"
#include "Label.h"
namespace fs = std::experimental::filesystem;

void checkin(std::string, std::string);
bool checkExistDir(const std:: string& name);

void checkin(std:: string repo1, std:: string repo2)
{
  //Adds the Files from "Repo 2" to the source Repository
  //Should run new ArtId to the second repository to keep track of any changes
  fs::path sourcePath = repo1;
  fs::path checkInPath = repo2;


  std::fstream updateManifest;

  fs::path modManifestPath = checkInPath;
  updateManifest.open("manifest.txt", std::ios_base::app);

  for (auto it = fs::recursive_directory_iterator(checkInPath); it != fs::recursive_directory_iterator();++it)
  {
        fs::path path = it->path();
        std::string pathString = path.string();
        pathString = pathString.substr(pathString.find_first_of("/"));
        fs::path newPath = pathString;        //Makes sure the file ArtId is changed if there are any mods made
        if(checkExistDir(path.string())){
          //fs::create_directories(repo2+ pathString);
          if(fs::is_regular_file(path)){
            std::string orginalfileName = path.string();
            std::string modArtID = artifactID(checkInPath);
            updateManifest << "Modification to " <<pathString<< "new Artifact Id\t"<<modArtID<< std::endl;

            fs::copy_file(path, repo1+pathString+"/"+modArtID );
          }
        }
  }
  //fs::copy(, fs::copy_options::recursive);
    updateManifest.close();
}

bool checkExistDir(const std::string& name){
		if(FILE *file = fopen(name.c_str(), "r")) {
				fclose(file);
				return true;
		}
		else {
				return false;
		}
}
