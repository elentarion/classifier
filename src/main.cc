#include <iostream>
#include <cstdlib>
#include <fstream>
#include <map>

#include <boost/locale.hpp>

#include "word_tokenizer.h"
#include "sentence_tokenizer.h"

std::wstring read_file(const std::string& filename)
{
	std::wifstream in(filename, std::ios::in | std::ios::binary);
	std::wstring contents;
	in.seekg(0, std::ios::end);
	contents.resize(in.tellg());
	in.seekg(0, std::ios::beg);
	in.read(&contents[0], contents.size());
	in.close();

	return contents;
}

int main(int argc, char** argv)
{
	boost::locale::generator gen;
	std::locale loc = gen("en_US.UTF-8");
	
	std::map<std::wstring, bool> stopwords;
	std::wifstream stopwordsFile("data/stopwords-en.txt", std::ios::in);
	std::wstring line;
	while (std::getline(stopwordsFile, line)) {
		stopwords.insert(std::pair<std::wstring, bool>(line, true));
	}
	stopwordsFile.close();

	nlp::sentence_tokenizer stokenizer;
	nlp::word_tokenizer wtokenizer;

	std::wstring text = read_file("data/newyorktimes.txt");

	auto stokens = stokenizer(text);
	for (auto its = stokens.begin(); its != stokens.end(); its++)
	{
		auto wtokens = wtokenizer(*its);
		for (auto itw = wtokens.begin(); itw != wtokens.end(); itw++)
		{
			std::transform((*itw).begin(), (*itw).end(), (*itw).begin(), ::tolower);
			if (stopwords.find((*itw)) == stopwords.end())
				std::wcout << (*itw) << std::endl;
		}
	}

	std::cin.get();

	return 0;
}
