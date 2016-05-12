files=$(shell find src/ -name \*cpp)
objs=$(addsuffix .o,$(basename $(files)))

CXXFLAGS=-Wall -std=c++11 -pipe -fomit-frame-pointer \
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


.cpp.o:
	$(CXX) $(CXXFLAGS) -c $^ -o $(OBJDIR)/$(notdir $@)

all: $(target)
	@echo ${files}
	@echo $(OBJDIR)

$(target): $(objs)
	$(CXX) $(objs) $(LFLAGS) -o $(BINDIR)/$(target)