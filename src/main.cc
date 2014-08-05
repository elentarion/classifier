#include <iostream>
#include <cstdlib>
#include <fstream>
#include <map>

#include <boost/locale.hpp>

#include "word_tokenizer.h"
#include "sentence_tokenizer.h"

std::string read_file(const std::string& filename)
{
	std::ifstream in(filename, std::ios::in | std::ios::binary);
	std::string contents;

	in.seekg(0, std::ios::end);
	contents.resize(in.tellg());
	in.seekg(0, std::ios::beg);
	in.read(&contents[0], contents.size());
	in.close();

	return contents;
}

int main(int argc, char** argv)
{	
	namespace bl = boost::locale;
	namespace blb = bl::boundary;

	bl::generator gen;
	std::locale loc = gen("en_US.UTF8");
	std::locale::global(loc);

	std::map<std::wstring, bool> stopwords;
	std::wifstream stopwordsFile("data/stopwords-en.txt", std::ios::in);
	std::wstring line;
	while (std::getline(stopwordsFile, line)) {
		stopwords.insert(std::pair<std::wstring, bool>(line, true));
	}
	stopwordsFile.close();

	std::string text = read_file("data/newyorktimes.txt");

	blb::ssegment_index map(blb::word, text.begin(), text.end(), gen("en_US.UTF8"));

	std::cin.get();

	return 0;
}
