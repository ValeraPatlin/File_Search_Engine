#include "ConverterJSON.h"
#include "SearchEngine.h"
#include "InvertedIndex.h"
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

std::vector<std::string> res_files =
{
        PAST_CONFIG,
        PAST_REQUESTS,
        PAST_ANSWERS
};

void creating_files_json();

int main()
{
    creating_files_json();

    ConverterJSON converter_js;

    std::vector<std::string> documents = converter_js.GetTextDocuments();

    InvertedIndex inverted_in;

    inverted_in.UpdateDocumentBase(documents); //!!

    SearchServer search_server(inverted_in);

    auto requests_results_vec = search_server.search(converter_js.GetRequests());

    if (requests_results_vec.empty())
    {
        cout << "\nError No Data.\n";
        exit(1);
    }

    std::vector<std::vector<std::pair<int, float>>> requests_results_json;

    for (auto& request_result : requests_results_vec)
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

    converter_js.putAnswers(requests_results_json);

    return 0;
}

void creating_files_json()
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
                "resources\\file001.txt",
                "resources\\file002.txt",
                "resources\\file003.txt",
        };

        std::ofstream file(PAST_CONFIG);
        file << config;
        file.close();

        js requests;

        requests["requests"] =
        {
                "one",
                "two",
                "three",
                "four",
                "python",
                "Git"
        };

        file.open(PAST_REQUESTS);
        file << requests;
        file.close();
    }
}
