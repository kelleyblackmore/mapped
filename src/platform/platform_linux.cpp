#include <iostream>
#include <string>

namespace my_desktop_app {
namespace platform {

void initialize() {
    std::cout << "Initializing Linux platform-specific features" << std::endl;
}

void cleanup() {
    std::cout << "Cleaning up Linux platform-specific features" << std::endl;
}

std::string getHomeDirectory() {
    const char* homeDir = getenv("HOME");
    return homeDir ? homeDir : "/home/user";
}

bool isWayland() {
    const char* xdgSession = getenv("XDG_SESSION_TYPE");
    return (xdgSession && std::string(xdgSession) == "wayland");
}

} // namespace platform
} // namespace my_desktop_app
