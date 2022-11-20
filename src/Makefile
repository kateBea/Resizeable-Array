# program name here
OUTPUT_BINARY = main
SOURCE_FILES = main.cc
INCLUDE_FILES = vector.h
CXX_STANDARD = -std=c++17

# compile all
all: program

program: $(PROGRAM_NAME_CXX) $(INCLUDE_FILES)
	g++ -o $(OUTPUT_BINARY) $(CXX_STANDARD) -g -Wall -Wextra $(SOURCE_FILES)

build_cxx_optimized: $(PROGRAM_NAME_CXX) $(INCLUDE_FILES)
	g++ -o $(OUTPUT_BINARY) $(CXX_STANDARD) -O2 -Wall -Wextra $(SOURCE_FILES)

clean:
	rm main
