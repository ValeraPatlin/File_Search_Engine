#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <map>
#include <mutex>
#include <sstream>
#include <algorithm>

using std::cout;

struct Entry {
	size_t doc_id, count;
	// ������ �������� ��������� ��� ���������� �������� ���������
	bool operator ==(const Entry& other) const
	{
		return (this->doc_id == other.doc_id &&
			this->count == other.count);
	}
};

class InvertedIndex
{
public:
	InvertedIndex();

	//�������� ��� ��������� ���� ����������, �� ������� ����� ��������� �����
	//@param texts_input ���������� ����������

	void UpdateDocumentBase(std::vector<std::string> input_docs);

	//����� ���������� ���������� ��������� ����� word � ����������� ���� ����������
	//@param word �����, ������� ��������� �������� ���������� ����������
	//@return ���������� �������������� ������ � �������� ����

	std::vector<Entry> GetWordCount(const std::string& word);
	size_t get_word_count(const std::string& word, const size_t doc_id) const;

private:
	bool indexing_ongoing = false;
	std::mutex mutex_index;

	std::vector<std::string> docs; // ������ ����������� ����������
	std::map<std::string, std::vector<Entry>> freq_dictionary; // ��������� �������

	void index_file(const std::string& fileContent, size_t docId);
};

