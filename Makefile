CXX = clang++
CXXFLAGS = -std=c++20
SRC = main.cpp
TARGET = wEditor
WX_CONFIG = /usr/local/bin/wx-config
all: $(TARGET)
$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(shell $(WX_CONFIG) --cxxflags) $(SRC) -o $(TARGET) $(shell $(WX_CONFIG) --libs)

clean:
	rm -f $(TARGET)
