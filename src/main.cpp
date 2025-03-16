#include <iostream>
#include "my_desktop_app/app.h"

int main(int argc, char* argv[]) {
    try {
        my_desktop_app::App app(argc, argv);
        std::cout << "Starting " << app.getAppName() << " version " 
                  << app.getAppVersion() << std::endl;
        
        return app.run();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}
