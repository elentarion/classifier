#ifndef WORD_TOKENIZER_H_
#define WORD_TOKENIZER_H_

#include <vector>
#include <string>
#include <boost/tokenizer.hpp>

namespace nlp
{
	typedef boost::tokenizer<boost::char_separator<wchar_t>, std::wstring::const_iterator, std::wstring> tokenizer;
	
	class word_tokenizer
	{
		public:
			std::vector<std::wstring> operator()(const std::wstring& text);
			
	};
}

#endif
