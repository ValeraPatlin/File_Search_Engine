#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <nlohmann/json.hpp>

using std::cout;
using std::endl;

using js = nlohmann::json;

struct Struct_Json_config
{
	std::string name = "file search";
	double version = 0.1;
	int max_responses = 5;
	std::vector < std::string> files;
};

class ConverterJSON
{

public:
	ConverterJSON();
	/**
	* Метод получения содержимого файлов
	* @return Возвращает список с содержимым файлов перечисленных
	* в config.json
	*/
	std::vector<std::string> GetTextDocuments();
	/**
	* Метод считывает поле max_responses для определения предельного
	* количества ответов на один запрос
	* @return
	*/
	int GetResponsesLimit();
	/**
	* Метод получения запросов из файла requests.json
	* @return возвращает список запросов из файла requests.json
	*/
	std::vector<std::string> GetRequests();
	/**
	* Положить в файл answers.json результаты поисковых запросов
	*/
	void putAnswers(std::vector<std::vector<std::pair<int, float>>>
		answers);
private:
	Struct_Json_config obj_config;
	std::vector<std::string> requests_vec;

	bool read_good = false;

	void json_read();
};

