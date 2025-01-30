CXX := clang++
CXXFLAGS := -std=c++20 -fmodules -fprebuilt-module-path=build
TARGET := program

all: $(TARGET)

# Final link step: Build the program from all .o files + .pcm files
$(TARGET): build/main.o build/messages.o build/parser.o \
           build/messages.pcm build/parser.pcm
	$(CXX) $(CXXFLAGS) $^ -o $@

# 1) Precompile the 'messages' module interface: messages.cppm -> messages.pcm
build/messages.pcm: messages/messages.cppm
	@mkdir -p build
	$(CXX) $(CXXFLAGS) --precompile $< -o $@

# 2) Precompile the 'parser' module interface: parser.cppm -> parser.pcm
build/parser.pcm: parser/parser.cppm
	@mkdir -p build
	$(CXX) $(CXXFLAGS) --precompile $< -o $@

# 3) Compile the 'messages' module implementation: messages.cpp -> messages.o
#    The .cpp might 'import messages' or other modules, so list build/messages.pcm.
build/messages.o: messages/messages.cpp build/messages.pcm
	@mkdir -p build
	$(CXX) $(CXXFLAGS) -c $< -o $@

# 4) Compile the 'parser' module implementation: parser.cpp -> parser.o
#    The .cpp might 'import parser', so we depend on build/parser.pcm here.
build/parser.o: parser/parser.cpp build/parser.pcm
	@mkdir -p build
	$(CXX) $(CXXFLAGS) -c $< -o $@

# 5) Compile main.cpp -> main.o
#    If main.cpp imports both modules, it depends on both .pcm files
build/main.o: main.cpp build/messages.pcm build/parser.pcm
	@mkdir -p build
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf build $(TARGET)

.PHONY: all clean