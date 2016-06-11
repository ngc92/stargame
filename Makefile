sources := $(shell find src/ -name \*cpp)
objs    := $(addsuffix .o,$(basename $(sources)))


CXXFLAGS=-Wall -std=c++11 -pipe -fstack-protector-strong \
	 -ftemplate-backtrace-limit=0 --param=ssp-buffer-size=4 -fPIC -pthread
INCLUDE= -Iexternal/Box2D/Box2D/ \
	 -Iexternal/ \
	 -Isrc/ \
	 -Isrc/game
LFLAGS+=-L"/usr/lib" \
	external/irrlicht-lib/libIrrlicht.so \
	external/irrklang-lib/libIrrKlang.so \
	external/Box2D/Box2D/BuildLinux/Box2D/libBox2D.so


target=Stargame


ifeq ($(DEBUG),1)
	CXXFLAGS+=-g -ggdb
	OBJDIR=obj/Debug
	BINDIR=bin/Debug
else
	CXXFLAGS+=-O2
	OBJDIR=obj/Release
	BINDIR=bin/Release
endif


out_objs=$(addprefix $(OBJDIR)/, $(subst src/,,$(objs)))

garbage=$(wildcard bin/ obj/)


$(OBJDIR)/%.o: src/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $^ -o $@


all: $(target)

$(target): $(out_objs)
	@mkdir -p $(BINDIR)
	$(CXX) $(CXXFLAGS) $(out_objs) -o $(BINDIR)/$(target) $(LFLAGS)

clean:
	rm -r $(garbage)