TARGET = FINAL
SRC_FILES = main.cpp lib/Shared.cpp lib/board/Board.cpp lib/board/LeafBoard.cpp lib/board/PrimaryBoard.cpp lib/GraphicalBoard.cpp lib/NcHandler.cpp
DOCS_DIR = docs

# I like this linker
ifneq ("$(shell which mold)","")
	LINKERFLAG = -fuse-ld=mold
endif

ifneq ("$(shell which doxygen)","")
	DOXYGEN = doxygen
endif

# For including external libraries
INCLUDE = -I/usr/include/ -I./
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

all: $(TARGET) docs

$(TARGET): $(OBJECTS)
	@echo Building $@
	$(CXX) $(CXXFLAGS) $(CXXVERSION) $(CXXFLAGS_DEBUG) -o $@ $^

.cpp.o:
	$(CXX) $(CXXFLAGS) $(CXXVERSION) $(CXXFLAGS_DEBUG) -o $@ -c $<

clean:
	$(DEL) -r $(TARGET) $(OBJECTS) $(DOCS_DIR) Makefile.bak

depend:
	@sed -i.bak '/^# DEPENDENCIES/,$$d' Makefile
	@$(DEL) sed*
	@echo $(Q)# DEPENDENCIES$(Q) >> Makefile
	@$(CXX) -MM $(SRC_FILES) >> Makefile

docs: Doxyfile
	@$(DOXYGEN)

zip:
	@tar czf $(TARGET).tar.gz --exclude-ignore=.gitignore --exclude=".git" --exclude=".gitignore" .

.PHONY: all clean depend
