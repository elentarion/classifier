#include <iostream>
#include <cstdlib>
#include <fstream>

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
	nlp::sentence_tokenizer stokenizer;
	nlp::word_tokenizer wtokenizer;
	
	std::wstring text = read_file("newyorktimes.txt");
	
	auto stokens = stokenizer(text);
	for (auto its = stokens.begin(); its != stokens.end(); its++)
	{
		auto wtokens = wtokenizer(*its);
		for (auto itw = wtokens.begin(); itw != wtokens.end(); itw++)
			std::wcout << (*itw) << std::endl;
	}
	
	system("pause");
	
	return 0;
}
