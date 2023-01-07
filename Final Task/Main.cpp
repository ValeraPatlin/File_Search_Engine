import Functions_JSON;

#include "../include/ConverterJSON.h"
#include "../include/InvertedIndex.h"
#include "../include/SearchServer.h"

int main()
{
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