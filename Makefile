CXX := clang++
CXXFLAGS := -std=c++20 -fmodules -fprebuilt-module-path=build
TARGET := program

all: $(TARGET)

$(TARGET): build/main.o build/messages.o build/messages.pcm
	$(CXX) $(CXXFLAGS) $^ -o $@

# Module interface compilation
build/messages.pcm: messages/messages.cppm
	@mkdir -p build
	$(CXX) $(CXXFLAGS) --precompile $< -o $@

# Module implementation
build/messages.o: messages/messages.cpp build/messages.pcm
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Main program
build/main.o: main.cpp build/messages.pcm
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf build $(TARGET)

.PHONY: all clean