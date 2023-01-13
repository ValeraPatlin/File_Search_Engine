#include "../include/ConverterJSON.h"
#include "../include/InvertedIndex.h"
#include "../include/SearchServer.h"
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

std::vector<std::string> res_files =
        {
                "Json\\config.json",
                "Json\\requests.json",
                "Json\\answers.json"
        };

void json_file();
void write_answers_json(const std::vector<std::vector<RelativeIndex>>& requests_results);

int main() {

    json_file();

    ConverterJSON converter_js;

    std::vector<std::string> documents = converter_js.GetTextDocuments();

    InvertedIndex inverted_in;

    inverted_in.UpdateDocumentBase(documents);

    SearchServer search_server(inverted_in);

    auto requests_results_vec = search_server.search(converter_js.GetRequests());

    write_answers_json(requests_results_vec);

    return 0;
}

void json_file()
{
    auto dir = fs::current_path();

    dir = dir / "Json";

    if (fs::exists(dir))
    {
        return;
    }
    else
    {
        fs::create_directories(dir);

        for (auto& file : res_files)
        {
            std::ofstream(file) << "data";
        }

        js config;

        config["config"]["name"] = "file search";
        config["config"]["version"] = 0.1;
        config["config"]["max_responses"] = 5;
        config["files"] =
                {
                        "/resources/file001.txt",
                        "/resources/file002.txt",
                        "/resources/file003.txt",
                };

        std::ofstream file("Json\\config.json");
        file << config;
        file.close();

        js requests;

        requests["requests"] =
                {
                        "some words..",
                        "some words..",
                        "some words..",
                        "some words.."
                };

        file.open("Json\\requests.json");
        file << requests;
        file.close();
    }
}

void write_answers_json(const std::vector<std::vector<RelativeIndex>>& requests_results)
{
    if (requests_results.empty())
    {
        cout << "\nError No Data.\n";
        return;
    }

    std::vector<std::vector<std::pair<int, float>>> requests_results_json;

    for (auto& request_result : requests_results)
    {
        std::vector<std::pair<int, float>> request_json;

        for (auto& relevance_it : request_result)
        {
            std::pair<int, float> relevance_pair;

            relevance_pair.first = static_cast<int>(relevance_it.doc_id);
            relevance_pair.second = relevance_it.rank;
            request_json.push_back(relevance_pair);
        }
        requests_results_json.push_back(request_json);
    }

    ConverterJSON obj;

    obj.putAnswers(requests_results_json);
}
