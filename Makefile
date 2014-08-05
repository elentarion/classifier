CC=gcc
CXX=g++
RM=rm -f
CPPFLAGS=-g -std=c++11 $(shell root-config --cflags)
LDFLAGS=-g $(shell root-config --ldflags)
LDLIBS=-lboost_locale

SRCS=src/main.cc src/word_tokenizer.cc src/sentence_tokenizer.cc
OBJS=$(subst .cc,.o,$(SRCS))

all: classifier

classifier: $(OBJS)
	g++ $(LDFLAGS) -o classifier $(OBJS) $(LDLIBS) 

depend: .depend

.depend: $(SRCS)
	rm -f ./.depend
	$(CXX) $(CPPFLAGS) -MM $^>>./.depend;

clean:
	$(RM) $(OBJS)

dist-clean: clean
	$(RM) *~ .dependtool	
