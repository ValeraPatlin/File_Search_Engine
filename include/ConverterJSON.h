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
	* ����� ��������� ����������� ������
	* @return ���������� ������ � ���������� ������ �������������
	* � config.json
	*/
	std::vector<std::string> GetTextDocuments();
	/**
	* ����� ��������� ���� max_responses ��� ����������� �����������
	* ���������� ������� �� ���� ������
	* @return
	*/
	int GetResponsesLimit();
	/**
	* ����� ��������� �������� �� ����� requests.json
	* @return ���������� ������ �������� �� ����� requests.json
	*/
	std::vector<std::string> GetRequests();
	/**
	* �������� � ���� answers.json ���������� ��������� ��������
	*/
	void putAnswers(std::vector<std::vector<std::pair<int, float>>>
		answers);
private:
	Struct_Json_config obj_config;
	std::vector<std::string> requests_vec;

	bool read_good = false;

	void json_read();
};

