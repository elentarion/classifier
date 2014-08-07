CC=gcc
CXX=g++
RM=rm -f
CPPFLAGS=-g -std=c++11
LDFLAGS=-g
LDLIBS=-lboost_locale -lpugixml

SRCS=src/main.cc src/stopwords.cc
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
