# File_Search_Engine

ENG
Application for searching of request words in resources text files. 
The request is located in the requests.json file.  
Path to resources files are specified in config.json. Search result is putting into answers.json.

C++ 20

CMAKE 3.8

https://cmake.org/

JSON 3.10.5

https://github.com/nlohmann/json

GTEST 1.11

https://github.com/google/googletest

Use the default build

	cmake -S . -B "build"
	cmake --build build --config Release
	
Step 1: Build the project.

If you use Visual Studio compiler you can build x64 or x32 version respectively:

For x64 version:

	cmake -A x64 -S . -B "build64"
	
	cmake --build build64 --config Release
	
For x32 version:

	cmake -A Win32 -S . -B "build32"
	
	cmake --build build32 --config Release
	
In other cases use default build:
cmake -S . -B "build"
cmake --build build --config Release

Step 2: copy files:
.\bin\requests.json, .\bin\config.json, .\bin\answers.json and .\bin\resources folder
from .\bin folder
to the .\bin\Release folder.

Step 3: run the application:
.\bin\Release\Search_in_files

Files specification

	config.json

	File where specified name and version of application.
	Here you can also change the maximal quantity of relevant pages that will be put into answers.json

	requests.json

	File where specified requests for search.

	answers.json

	File where search result will be written in JSON format.
