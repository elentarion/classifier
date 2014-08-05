#include "sentence_tokenizer.h"

namespace nlp
{
	std::vector<std::wstring> sentence_tokenizer::operator()(const std::wstring& text)
	{
		std::vector<std::wstring> result;
		boost::char_separator<wchar_t> sep(L";.!?");
		
		tokenizer tokens(text, sep);
		for (auto it = tokens.begin(); it != tokens.end(); it++)
			result.push_back(*it);			
		
		return result;
	}
}
