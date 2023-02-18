#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <nlohmann/json.hpp>
#include <iomanip>

namespace fs = std::filesystem;

#ifdef _WIN32

#ifdef _WIN64

const std::string PAST_CONFIG = "Json\\config.json";
const std::string PAST_REQUESTS = "Json\\requests.json";
const std::string PAST_ANSWERS = "Json\\answers.json";
#else

const std::string PAST_CONFIG = "Json\\config.json";
const std::string PAST_REQUESTS = "Json\\requests.json";
const std::string PAST_ANSWERS = "Json\\answers.json";
#endif

#elif __APPLE__
#include "TargetConditionals.h"

#if TARGET_IPHONE_SIMULATOR

const std::string PAST_REQUESTS = "Json/requests.json";
const std::string PAST_CONFIG = "Json/config.json";
const std::string PAST_ANSWERS = "Json/answers.json";
#elif TARGET_OS_IPHONE

const std::string PAST_REQUESTS = "Json/requests.json";
const std::string PAST_CONFIG = "Json/config.json";
const std::string PAST_ANSWERS = "Json/answers.json";
#elif TARGET_OS_MAC

const std::string PAST_REQUESTS = "Json:requests.json";
const std::string PAST_CONFIG = "Json:config.json";
const std::string PAST_ANSWERS = "Json:answers.json";
#else
#error "Unknown Apple platform"
#endif

#elif __linux__

const std::string PAST_REQUESTS = "Json/requests.json";
const std::string PAST_CONFIG = "Json/config.json";
const std::string PAST_ANSWERS = "Json/answers.json";
#elif __unix__ // all unices not caught above

const std::string PAST_REQUESTS = "Json/requests.json";
const std::string PAST_CONFIG = "Json/config.json";
const std::string PAST_ANSWERS = "Json/answers.json";
#elif defined(_POSIX_VERSION)

const std::string PAST_REQUESTS = "Json/requests.json";
const std::string PAST_CONFIG = "Json/config.json";
const std::string PAST_ANSWERS = "Json/answers.json";
#else
#error "Unknown compiler"
#endif

using std::cout;
using std::endl;

using js = nlohmann::json;

struct Struct_Json_config
{
	std::string name = "No Data";
	double version = 0.0;
	int max_responses = 0;
	std::vector < std::string> past_files;
};

class ConverterJSON
{

public:
	ConverterJSON();

	//Метод получения содержимого файлов
	//@return Возвращает список с содержимым файлов перечисленных
	//в config.json

	std::vector<std::string> GetTextDocuments();

	//Метод считывает поле max_responses для определения предельного
	//количества ответов на один запрос  @return

	int GetResponsesLimit();

	//Метод получения запросов из файла requests.json
	//@return возвращает список запросов из файла requests.json

	std::vector<std::string> GetRequests();

	//Положить в файл answers.json результаты поисковых запросов

	void putAnswers(std::vector<std::vector<std::pair<int, float>>>
		answers);
private:
	Struct_Json_config obj_config;
	std::vector<std::string> requests_vec;
	std::vector<std::string> documents_vec;

	bool read_good = false;

	void text_documents();
	void display_config();
	void display_requests();
	void json_read();
};
