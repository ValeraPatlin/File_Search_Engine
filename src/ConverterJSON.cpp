#include "ConverterJSON.h"

ConverterJSON::ConverterJSON() = default;

std::vector<std::string> ConverterJSON::GetTextDocuments()
{
	if (read_good)
	{
		return documents_vec;
	}
	else
	{
		json_read();
		return documents_vec;
	}
}

int ConverterJSON::GetResponsesLimit()
{
	if (read_good)
	{
		return obj_config.max_responses;
	}
	else
	{
		json_read();
		return obj_config.max_responses;
	}
}

std::vector<std::string> ConverterJSON::GetRequests()
{
	js requests;

	std::ifstream file(PAST_REQUESTS);

	if (!file)
	{
		cout << "File NO is open\n";
		return {};
	}

	file >> requests;

	file.close();

	requests["requests"].get_to<std::vector<std::string>>(requests_vec);

	display_requests();

	return requests_vec;
}

void ConverterJSON::putAnswers(std::vector<std::vector<std::pair<int, float>>> answers)
{
	if (answers.empty())
	{
		cout << "The vector is empty" << std::endl; //здесь!!!
		return;
	}

	std::ofstream file(PAST_ANSWERS, std::ios::out);

	if (!file)
	{
		cout << "File NO is open\n";
		return;
	}

	js answer_js;
	int count = 0;

	for (auto request : answers)
	{
		answer_js["answers"]["request" + std::to_string(count)]["result"] = !request.empty();

		if (request.size() == 1)
		{
			answer_js["answers"]["request" + std::to_string(count)]["docid"] = request[0].first;
			answer_js["answers"]["request" + std::to_string(count)]["rank"] = request[0].second;
		}
		else
		{
			auto obj_arr = js::array();
			int request_id = 0;

			for (auto relevance : request)
			{
				++request_id;
				if (request_id > obj_config.max_responses)
				{
					break;
				}

				auto obj_js = js::object();
				obj_js["docid"] = relevance.first;
				obj_js["rank"] = relevance.second;
				obj_arr.push_back(obj_js);
			}
			answer_js["answers"]["request" + std::to_string(count)]["relevance"] = obj_arr;
		}
		++count;
	}
	file << answer_js;
	file.close();
}

void ConverterJSON::text_documents()
{
	documents_vec.clear();

	for (const auto& file : obj_config.past_files)
	{
		std::ifstream doc_reading(file);
		if (!doc_reading.is_open())
		{
			cout << "\nError. File no open\n";
			exit(3);
		}
		std::string text, buffer;
		while (!doc_reading.eof())
		{
			buffer = "";
			doc_reading >> buffer;
			text += buffer;
			text += " ";
		}
		documents_vec.push_back(text);
		doc_reading.close();
	}
	cout << "The documents have been read. Number of files:\t" << obj_config.past_files.size() << endl;

}

void ConverterJSON::display_config()
{
	cout << "Start\n"
		<< std::setfill('-') << std::setw(70) << "\n"
		<< "\nName:" << std::setfill(' ') << std::setw(54) << obj_config.name
		<< "\nVersion:" << std::setfill(' ') << std::setw(43) << obj_config.version
		<< "\nMax responses per request:" << std::setfill(' ') << std::setw(23)
		<< obj_config.max_responses
		<< "\nThe number of files that need to be searched:\t" << obj_config.past_files.size()
		<< endl << std::setfill('-') << std::setw(70) << "\n";
}

void ConverterJSON::display_requests()
{
	cout << "\nNumber of requests:\t" << requests_vec.size() << endl
		<< std::setfill('-') << std::setw(70) << "\n";
}

void ConverterJSON::json_read()
{
	js config;
	std::ifstream file(PAST_CONFIG);

	if (!file)
	{
		cout << "File NO is open\n";
		exit(2);
	}
	file >> config;
	file.close();

	obj_config.name = config["config"]["name"].get<std::string>();
	obj_config.version = config["config"]["version"].get<double>();
	obj_config.max_responses = config["config"]["max_responses"].get<int>();
	config["files"].get_to<std::vector<std::string>>(obj_config.past_files);

	read_good = true;
	display_config();
	text_documents();
}