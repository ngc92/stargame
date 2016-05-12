files=$(shell find src/ -name \*cpp)
objs=$(addsuffix .o,$(basename $(files)))

CXXFLAGS=-Wall -std=c++11 -pipe -fomit-frame-pointer \
	 -ftemplate-backtrace-limit=0 \
	 -Iexternal/Box2D/Box2D/ \
	 -Iexternal/ \
	 -Isrc/
LFLAGS=

target=Stargame

ifeq ($(DEBUG),1)
	CXXFLAGS+=-g -ggdb
	OBJDIR=obj/Debug
	BINDIR=bin/Debug
else
	OBJDIR=obj/Release
	BINDIR=bin/Release
endif

garbage=$(wildcard bin/ obj/)

.cpp.o:
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $^ -o $(OBJDIR)/$(notdir $@)

all: $(target)

$(target): $(objs)
	@mkdir -p $(BINDIR)
	$(CXX) $(objs) $(LFLAGS) -o $(BINDIR)/$(target)

clean:
	rm -r $(garbage)