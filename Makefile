TARGET = GAME
SRC_FILES = main.cpp
# TARGET = FINAL
# SRC_FILES = main.cpp Shared.cpp Board.cpp LeafBoard.cpp PrimaryBoard.cpp

# I like this linker
ifneq ("$(wildcard /usr/bin/mold)","")
	LINKERFLAG = -fuse-ld=mold
endif

# For including external libraries
INCLUDE = -I /usr/include/
LDLIBS = -lnotcurses-core -lnotcurses
LDFLAGS = -L /usr/lib/ $(LDLIBS)

CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -pedantic-errors $(LINKERFLAG) $(INCLUDE) $(LDFLAGS)
CXXFLAGS_DEBUG = -g
CXXVERSION = -std=c++17

OBJECTS = $(SRC_FILES:.cpp=.o)

ifeq ($(shell echo "Windows"), "Windows")
	TARGET := $(TARGET).exe
	DEL = del
	Q=
else
	DEL = rm -f
	Q="
endif

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(CXXVERSION) $(CXXFLAGS_DEBUG) -o $@ $^

.cpp.o:
	$(CXX) $(CXXFLAGS) $(CXXVERSION) $(CXXFLAGS_DEBUG) -o $@ -c $<

clean:
	$(DEL) $(TARGET) $(OBJECTS) Makefile.bak

depend:
	@sed -i.bak '/^# DEPENDENCIES/,$$d' Makefile
	@$(DEL) sed*
	@echo $(Q)# DEPENDENCIES$(Q) >> Makefile
	@$(CXX) -MM $(SRC_FILES) >> Makefile

zip:
	@tar czf $(TARGET).tar.gz --exclude-ignore=.gitignore --exclude=".git" --exclude=".gitignore" .

.PHONY: all clean depend
