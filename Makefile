CXX = g++
CXXFLAGS = -Wall -Wextra -pedantic-errors -std=c++23 -I"C:/Program Files/FireDaemon OpenSSL 3/include"
DEPENDENCIES = Dependencies/nlohmann/json.hpp Include/color_utils.hpp Include/desktop_controller.hpp Include/settings.hpp Include/time_utils.hpp Include/solar_cycle_dto.hpp Include/solar_cycle_response.hpp Include/solar_cycle_client.hpp Include/executor.hpp Include/solar_cycle_cacher.hpp
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
	del cache\solar_cycle.cache