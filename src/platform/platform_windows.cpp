#include <iostream>
#include <string>

namespace my_desktop_app {
namespace platform {

void initialize() {
    std::cout << "Initializing Windows platform-specific features" << std::endl;
}

void cleanup() {
    std::cout << "Cleaning up Windows platform-specific features" << std::endl;
}

std::string getHomeDirectory() {
    const char* userProfile = getenv("USERPROFILE");
    return userProfile ? userProfile : "C:\\Users\\User";
}

bool isHighDpiEnabled() {
    return true; // Implementation would check Windows registry
}

} // namespace platform
} // namespace my_desktop_app
