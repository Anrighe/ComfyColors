#include "../Include/Settings.hpp"

int main(int argc, char *argv[]) {
    

    DesktopController desktopController;
    std::cout<<TimeUtils::getCurrentSystemTime()<<"\n";
    std::cout<<TimeUtils::getCurrentSystemTimeStringFormatted();

    Settings settings(desktopController);

    return 0;
}