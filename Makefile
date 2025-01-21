CXX = g++
CXXFLAGS = -Wall -Wextra -pedantic-errors -std=c++23
DEPENDENCIES = Dependencies/nlohmann/json.hpp Include/ColorUtils.hpp Include/DesktopController.hpp Include/Settings.hpp Include/TimeUtils.hpp
OBJS = main.o
SETTINGS_FILE = settings.json
PROJECT_NAME = comfyColors
EXECUTABLE_NAME = $(PROJECT_NAME).exe

all: $(OBJS)
	$(CXX) -o $(PROJECT_NAME) $(OBJS)

main.o: src/main.cpp
	$(CXX) $(CXXFLAGS) -c src/main.cpp -o main.o

clean:
