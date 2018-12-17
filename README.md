# VCSProject

# Group
Team Name: DAA </br>
Members: Dan Ortiz            (dbortiz@csu.fullerton.edu) </br>
         Aaron Jimenez-Lopez  (aaronjimenez97@csu.fullerton.edu) </br>
				 
</br>

# Introduction
The purpose of this assignment was to recreate a simplified Version Control System. Functions of Project #1 and Project #2 are working
properly; however, Project #3 is incomplete.

# Project #1
For project #1, we were suppose to create a create repository function and a check sum function.

The create repository function takes in 2 arguments: an existing directory and a target repository name. The target repository converts
all regular file names to a folder and within that folder, an artifact is created using the check sum function on the regular file. A
manifest file is also created and all artifacts created are inserted.

The check sum function (we named it artifactID) takes in 1 argument and that is the path of the regular file that will be converted into
artifact.

# Project #2
For project #2, we were suppose to create a label function, checkout function, and checkin function.

The label function takes in 3 arguments: an existing repository, a manifest file, and a new label. The function creates a text file 
named FileToHoldLabels.txt and the desired label name along with the path of the manifest are inserted. The function first searches within
the existing repository to make sure the manifest exists.

The checkout function takes in 3 arguments: an existing repository, a label name, and a target checkout repository. The function first
searches for the label name or manifest name within the existing repository. From there, the contents (artifacts) are inserted into a
vector. Then, the program searches for those files inside the manifest within the existing repository and copies their paths over to the
checkout repository.

The checkin function takes in 2 arguments: the existing repository and the currently checked out branch. The program first searches for any
changes made in any of the files inside the checked out repository with the existing repository. If there is, it'll say so and create a new 
manifest inside the exsting repository under the file that was changed.

# Project #3
INCOMPLETE.

# Requirements
An existing directory </br>
C++17 </br>
Able to compile <experimental/filesystem> library

# Issues/Bugs
This program does not have any security testing and is unsure of it's limits. </br>
You have to recompile to use another function.
