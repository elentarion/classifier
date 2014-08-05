#ifndef STOPWORDS_H_
#define STOPWORDS_H_

#include <string>
#include <map>
#include <fstream>
#include <iostream>

namespace nlp
{
	typedef std::map<std::string, bool> stopwords_map;

	class stopwords
	{
		public:
			stopwords(const std::string& filename);
			bool is_stopword(const std::string& word) const;

		private:
			stopwords_map _stopwords_map;

	};
}

#endif
