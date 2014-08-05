#include <iostream>
#include <cstdlib>
#include <fstream>
#include <map>

#include <boost/locale.hpp>

#include <pugixml.hpp>

#include "stopwords.h"

namespace bl = boost::locale;
namespace blb = bl::boundary;

template<typename A, typename B>
std::pair<B,A> flip_pair(const std::pair<A,B> &p)
{
    return std::pair<B,A>(p.second, p.first);
}

template<typename A, typename B>
std::multimap<B,A> flip_map(const std::map<A,B> &src)
{
    std::multimap<B,A> dst;
    std::transform(src.begin(), src.end(), std::inserter(dst, dst.begin()), 
                   flip_pair<A,B>);
    return dst;
}

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

std::map<std::string, unsigned int> analyze_text(const std::string& text, const nlp::stopwords& stopwords)
{
	std::map<std::string, unsigned int> docmap;

	blb::ssegment_index smap(blb::sentence, text.begin(), text.end());
	smap.rule(blb::sentence_term);
	for (auto sit = smap.begin(); sit != smap.end(); sit++)
	{
		blb::ssegment_index wmap(blb::word, (*sit).begin(), (*sit).end());
		wmap.rule(blb::word_any);
		for (auto wit = wmap.begin(); wit != wmap.end(); wit++)
		{
			auto string = bl::to_lower((*wit).str());
			if (!stopwords.is_stopword(string))
			{
				if (docmap.find(string) != docmap.end())
					docmap[string]++;
				else
					docmap[string] = 1;
			}
		}
	}

	return docmap;
}

void merge_keywords(const std::map<std::string, unsigned int> docmap, std::map<std::string, unsigned int> corpusmap)
{
	for (auto keyword : docmap)
	{
		if (corpusmap.find(keyword.first) != corpusmap.end())
			corpusmap[keyword.first]++;
		else
			corpusmap[keyword.first] = 0;
	}
}

int main(int argc, char** argv)
{
	bl::generator gen;
	std::locale loc = gen("en_US.UTF8");
	std::locale::global(loc);

	nlp::stopwords english_stopwords("data/stopwords-en.txt");

	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file("data/newsspace200.xml");

	std::map<std::string, unsigned int> tfidf;

	int i = 0;
	for (auto news = doc.child("all_news").child("article"); news; news = news.next_sibling("article"))
	{
		merge_keywords(tfidf, analyze_text(news.child_value("description"), english_stopwords));
	}

	auto res = flip_map(tfidf);

	for (auto highest : res)
	{
		std::cout << highest.second << "(" << highest.first << ")" << std::endl;
	}

	return 0;
}
