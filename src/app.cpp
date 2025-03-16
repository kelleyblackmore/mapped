#include "my_desktop_app/app.h"
#include "ui/main_window.h"
#include "core/data_model.h"
#include "core/map_provider.h"
#include "core/map_layer.h"
#include <stdexcept>
#include <iostream>

namespace my_desktop_app {

App::App(int argc, char* argv[]) 
    : m_appName("Mapped"), 
      m_appVersion("0.1.0") {
    
    // Initialize components
    initializeApplication();
    
    // Platform-specific setup
    setupPlatformSpecifics();
    
    // Create data model
    m_dataModel = std::make_shared<DataModel>();
    
    // Load map providers
    loadMapProviders();
    
    // Load saved map layers
    loadSavedLayers();
    
    // Create main window
    m_mainWindow = std::make_unique<MainWindow>(m_dataModel);
    m_mainWindow->setTitle("Mapped - Interactive Map Viewer");
}

App::~App() {
    // Clean up resources
    std::cout << "Shutting down application" << std::endl;
}

void App::initializeApplication() {
    // Load configuration
    std::cout << "Loading Mapped configuration" << std::endl;
}

void App::setupPlatformSpecifics() {
#ifdef PLATFORM_WINDOWS
    std::cout << "Setting up Windows-specific features" << std::endl;
#elif defined(PLATFORM_MACOS)
    std::cout << "Setting up macOS-specific features" << std::endl;
#elif defined(PLATFORM_LINUX)
    std::cout << "Setting up Linux-specific features" << std::endl;
#else
    throw std::runtime_error("Unsupported platform");
#endif
}

void App::loadMapProviders() {
    std::cout << "Loading map providers..." << std::endl;
    
    // Create and add default map providers
    auto osmProvider = std::make_shared<MapProvider>("OpenStreetMap", "https://tile.openstreetmap.org/{z}/{x}/{y}.png");
    auto satelliteProvider = std::make_shared<MapProvider>("Satellite", "https://server.arcgisonline.com/ArcGIS/rest/services/World_Imagery/MapServer/tile/{z}/{y}/{x}");
    
    m_mapProviders.push_back(osmProvider);
    m_mapProviders.push_back(satelliteProvider);
    
    // Set default active map provider
    m_activeMapProvider = osmProvider;
    
    std::cout << "Loaded " << m_mapProviders.size() << " map providers" << std::endl;
}

void App::loadSavedLayers() {
    std::cout << "Loading saved map layers..." << std::endl;
    // Here we would load any user-created map layers from disk
}

void App::addMapLayer(const std::shared_ptr<MapLayer>& layer) {
    m_mapLayers.push_back(layer);
    std::cout << "Added map layer: " << layer->getName() << std::endl;
}

void App::removeMapLayer(const std::string& layerId) {
    auto it = std::find_if(m_mapLayers.begin(), m_mapLayers.end(),
                          [&layerId](const auto& layer) {
                              return layer->getId() == layerId;
                          });
                          
    if (it != m_mapLayers.end()) {
        std::cout << "Removing map layer: " << (*it)->getName() << std::endl;
        m_mapLayers.erase(it);
    }
}

std::vector<std::shared_ptr<MapLayer>> App::getMapLayers() const {
    return m_mapLayers;
}

std::shared_ptr<MapProvider> App::getActiveMapProvider() const {
    return m_activeMapProvider;
}

int App::run() {
    // Show the main window
    m_mainWindow->show();
    
    // Run the event loop
    std::cout << "Running Mapped application main loop" << std::endl;
    
    // Simulate an event loop for now
    return 0;
}

const std::string& App::getAppName() const {
    return m_appName;
}

const std::string& App::getAppVersion() const {
    return m_appVersion;
}

} // namespace my_desktop_app
