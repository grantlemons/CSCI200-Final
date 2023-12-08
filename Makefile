TARGET = FP
TEST_TARGET = TEST
DOCS_DIR = docs

LIB_FILES = lib/Shared.cpp lib/board/ABoard.cpp lib/board/LeafBoard.cpp lib/board/PrimaryBoard.cpp lib/graphical_board/AGraphicalBoard.cpp lib/graphical_board/PrimaryGraphicalBoard.cpp lib/graphical_board/LeafGraphicalBoard.cpp lib/NcHandler.cpp lib/wrappers/NcPlaneWrapper.cpp lib/factories/BoardFactory.cpp
DUMMY_FILES = lib/dummies/AGraphicalBoardDummy.cpp lib/dummies/PrimaryGraphicalBoardDummy.cpp lib/dummies/LeafGraphicalBoardDummy.cpp lib/dummies/NcHandlerDummy.cpp lib/dummies/NcPlaneWrapperDummy.cpp lib/factories/DummyBoardFactory.cpp
TEST_FILES = lib/tests/BoardWinTests.cpp lib/tests/BoardHelperTests.cpp lib/tests/PrimaryBoardTests.cpp lib/tests/LeafBoardTests.cpp

SRC_FILES = main.cpp $(LIB_FILES) $(DUMMY_FILES)
TEST_SRC_FILES = test.cpp $(LIB_FILES) $(DUMMY_FILES) $(TEST_FILES)

# I like this linker
ifneq ("$(shell which mold)","")
	LINKERFLAG = -fuse-ld=mold
endif

ifneq ("$(shell which doxygen)","")
	DOXYGEN = doxygen
endif

# For including external libraries
INCLUDE = -I/usr/include/ -I./GSL/include -I./ 
LDLIBS = -lnotcurses-core -lnotcurses
LDFLAGS = -L /usr/lib/ $(LDLIBS)

CXX = g++
CXXFLAGS = -pedantic -Werror -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-declarations -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wno-strict-overflow -Wswitch-default -Wundef -Wno-unused $(LINKERFLAG) $(INCLUDE) $(LDFLAGS)
CXXFLAGS_DEBUG = -g
CXXVERSION = -std=c++17

OBJECTS = $(SRC_FILES:.cpp=.o)
HEADERS = $(LIB_FILES:.cpp=.h) $(DUMMY_FILES:.cpp=.h)
TEST_OBJECTS = $(TEST_SRC_FILES:.cpp=.o)
TEST_HEADERS = $(LIB_FILES:.cpp=.h) $(DUMMY_FILES:.cpp=.h) $(TEST_FILES:.cpp=.h)

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
	$(CXX) $(CXXFLAGS) $(CXXVERSION) $(CXXFLAGS_DEBUG) -o $@ $^

$(TEST_TARGET): $(TEST_OBJECTS)
	$(CXX) $(CXXFLAGS) $(CXXVERSION) $(CXXFLAGS_DEBUG) -o $@ $^

.cpp.o:
	$(CXX) $(CXXFLAGS) $(CXXVERSION) $(CXXFLAGS_DEBUG) -o $@ -c $<

clean:
	$(DEL) -r $(TARGET) $(OBJECTS) $(TEST_OBJECTS) $(DOCS_DIR) Makefile.bak

depend:
	@sed -i.bak '/^# DEPENDENCIES/,$$d' Makefile
	@$(DEL) sed*
	@echo $(Q)# DEPENDENCIES$(Q) >> Makefile
	@$(CXX) -MM $(SRC_FILES) >> Makefile

test: $(TEST_TARGET)
	@./$(TEST_TARGET)

docs:
	@$(DOXYGEN)

memcheck:
	@valgrind --leak-check=full ./$(TARGET)

lint: .clang-tidy $(SRC_FILES)
	@find lib *.cpp -regex '.*\.[(cpp)(h)]' -not -path '*/tests/*' | xargs -I{} clang-tidy -p compile-commands.json {}

lint-fix: .clang-tidy $(SRC_FILES)
	@find lib *.cpp -regex '.*\.[(cpp)(h)]' -not -path '*/tests/*' | xargs -I{} clang-tidy -p compile-commands.json {} -fix

zip:
	@tar czf ../$(TARGET).tar.gz --exclude-ignore=.gitignore --exclude=".git" --exclude=".gitignore" .

.PHONY: all clean depend docs memcheck lint lint-fix zip
