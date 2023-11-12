TARGET = FINAL
SRC_FILES = main.cpp lib/Shared.cpp lib/board/Board.cpp lib/board/LeafBoard.cpp lib/board/PrimaryBoard.cpp lib/GraphicalBoard.cpp lib/NcHandler.cpp lib/wrappers/NcPlaneWrapper.cpp lib/dummies/GraphicalBoardDummy.cpp lib/dummies/NcHandlerDummy.cpp lib/dummies/NcPlaneWrapperDummy.cpp
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
CXXFLAGS = -pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-declarations -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wswitch-default -Wundef -Werror -Wno-unused $(LINKERFLAG) $(INCLUDE) $(LDFLAGS)
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

docs: Doxyfile README.md
	@$(DOXYGEN)

memcheck:
	@valgrind --leak-check=full $(TARGET)

zip:
	@tar czf $(TARGET).tar.gz --exclude-ignore=.gitignore --exclude=".git" --exclude=".gitignore" .

.PHONY: all clean depend
