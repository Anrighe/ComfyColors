CXX = g++
CXXFLAGS = -Wall -Wextra -pedantic-errors -std=c++23 -I"C:/Program Files/FireDaemon OpenSSL 3/include"
DEPENDENCIES = Dependencies/nlohmann/json.hpp Include/ColorUtils.hpp Include/DesktopController.hpp Include/Settings.hpp Include/TimeUtils.hpp Include/SolarCycleDTO.hpp Include/SolarCycleResponse.hpp Include/SolarCycleClient.hpp
OBJS = main.o
SETTINGS_FILE = settings.json
PROJECT_NAME = comfyColors
EXECUTABLE_NAME = $(PROJECT_NAME).exe
LDFLAGS = -L"C:/Program Files/FireDaemon OpenSSL 3/lib" -lssl -lcrypto -lws2_32 -lcrypt32

all: clean $(OBJS)
	$(CXX) -o $(PROJECT_NAME) $(OBJS) $(LDFLAGS)

main.o: src/main.cpp
	$(CXX) $(CXXFLAGS) -c src/main.cpp -o main.o

clean:
	del main.o
	del comfyColors.exe
	del settings.json