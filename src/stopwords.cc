#include "stopwords.h"

namespace nlp
{
	stopwords::stopwords(const std::string& filename)
	{
		std::ifstream stopwords_file(filename.c_str(), std::ios::in);

		std::string line;
		while (std::getline(stopwords_file, line))
		{
			_stopwords_map[line] = true;
		}

		stopwords_file.close();
	}

	bool stopwords::is_stopword(const std::string& word) const
	{
		return (_stopwords_map.find(word) != _stopwords_map.end());
	}
}
