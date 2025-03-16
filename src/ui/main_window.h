#pragma once

#include <memory>
#include <string>
#include <vector>

namespace my_desktop_app {

class DataModel;
class MapView;
class LayerPanel;
class ToolBar;

class MainWindow {
public:
    explicit MainWindow(std::shared_ptr<DataModel> dataModel);
    ~MainWindow();

    void show();
    void hide();
    bool isVisible() const;
    void setTitle(const std::string& title);
    
    // Map view controls
    void zoomIn();
    void zoomOut();
    void panTo(double lat, double lon);
    void setZoomLevel(int level);
    
    // Layer management
    void addLayer();
    void removeLayer(const std::string& layerId);
    void toggleLayerVisibility(const std::string& layerId, bool visible);

private:
    std::shared_ptr<DataModel> m_dataModel;
    bool m_visible;
    std::string m_title;
    std::unique_ptr<MapView> m_mapView;
    std::unique_ptr<LayerPanel> m_layerPanel;
    std::unique_ptr<ToolBar> m_toolBar;
    
    void createMenus();
    void createToolbars();
    void createStatusBar();
    void createMapView();
    void createLayerPanel();
    void connectSignals();
};

} // namespace my_desktop_app
