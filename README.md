# File_Search_Engine

ENG
Application for searching of request words in resources text files. 
The request is located in the requests.json file.  
Path to resources files are specified in config.json. Search result is putting into answers.json.

RUS
Приложение для поиска запрашиваемых слов в текстовых файлах ресурсов. 
Запрос находиться в файле requests.json. 
Путь к ресурсам указан в config.json. Результат поиска помещается в answers.json.

C++ 20

CMAKE 3.8
https://cmake.org/

JSON 3.10.5
https://github.com/nlohmann/json

GTEST 1.11
https://github.com/google/googletest



Files specification
	config.json

	File where specified name and version of application.
	Here you can also change the maximal quantity of relevant pages that will be put into answers.json

	requests.json

	File where specified requests for search.

	answers.json

	File where search result will be written in JSON format.