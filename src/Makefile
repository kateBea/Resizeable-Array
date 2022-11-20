# program name here
PROGRAM_NAME_CXX = main.cc
INCLUDE_FILES = vector.h
CXX_STANDARD = -std=c++17

# compile all
all: program

program: $(PROGRAM_NAME_CXX) $(INCLUDE_FILES)
	g++ -o main $(CXX_STANDARD) -g -Wall -Wextra $(PROGRAM_NAME_CXX) $(LINK_POSIX_THREAD)

build_cxx_optimized: $(PROGRAM_NAME_CXX) $(INCLUDE_FILES)
	g++ -o main $(CXX_STANDARD) -O2 -Wall -Wextra $(PROGRAM_NAME_CXX) $(LINK_POSIX_THREAD)

clean:
	rm main
