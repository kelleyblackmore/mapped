#pragma once

#include <string>
#include <memory>
#include <vector>

namespace my_desktop_app {

class MainWindow;
class DataModel;
class MapProvider;
class MapLayer;

class App {
public:
    App(int argc, char* argv[]);
    ~App();

    int run();
    const std::string& getAppName() const;
    const std::string& getAppVersion() const;
    
    // Map management
    void loadMapProviders();
    void loadSavedLayers();
    
    // Return the active map provider
    std::shared_ptr<MapProvider> getActiveMapProvider() const;
    
    // Map layer operations
    void addMapLayer(const std::shared_ptr<MapLayer>& layer);
    void removeMapLayer(const std::string& layerId);
    std::vector<std::shared_ptr<MapLayer>> getMapLayers() const;

private:
    std::string m_appName;
    std::string m_appVersion;
    std::unique_ptr<MainWindow> m_mainWindow;
    std::shared_ptr<DataModel> m_dataModel;
    std::vector<std::shared_ptr<MapProvider>> m_mapProviders;
    std::shared_ptr<MapProvider> m_activeMapProvider;
    std::vector<std::shared_ptr<MapLayer>> m_mapLayers;
    
    void initializeApplication();
    void setupPlatformSpecifics();
    void setupMapDefaults();
};

} // namespace my_desktop_app
