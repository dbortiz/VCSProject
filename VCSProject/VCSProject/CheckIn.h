#include <iostream>
#include <experimental/filesystem>
#include <string>

namespace fs = std::experimental::filesystem;

void checkin(std::string, std::string);

void checkin(std:: string repo1, std:: string repo2)
{
  //Adds the Files from "Repo 2" to the source Repository
  //Should run new ArtId to the second repository to keep track of any changes
  fs::copy(repo1,repo2, fs::copy_options::recursive);
}
