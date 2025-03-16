#pragma once

#include <string>
#include <vector>
#include <memory>
#include <functional>
#include <unordered_map>

namespace my_desktop_app {

// Forward declarations
class DataItem;
class MapLayer;
class GeoCoordinate;

// Observer pattern for data changes
using DataChangeCallback = std::function<void(const std::string&)>;
using LayerChangeCallback = std::function<void(const std::string&)>;

struct MapBounds {
    double north;
    double south;
    double east;
    double west;
};

class DataModel {
public:
    DataModel();
    ~DataModel();

    // General data methods
    void loadData(const std::string& filePath);
    void saveData(const std::string& filePath);
    
    void addItem(const std::string& name, const std::string& value);
    void removeItem(const std::string& name);
    std::string getItemValue(const std::string& name) const;
    
    // Map-specific methods
    void setCurrentLocation(double lat, double lon);
    void setZoomLevel(int level);
    int getZoomLevel() const;
    GeoCoordinate getCurrentLocation() const;
    MapBounds getVisibleBounds() const;
    
    // Layer management
    void addLayer(std::shared_ptr<MapLayer> layer);
    void removeLayer(const std::string& layerId);
    std::shared_ptr<MapLayer> getLayer(const std::string& layerId) const;
    std::vector<std::shared_ptr<MapLayer>> getLayers() const;
    
    // Observer pattern methods
    void registerDataChangeCallback(DataChangeCallback callback);
    void registerLayerChangeCallback(LayerChangeCallback callback);

private:
    std::vector<std::unique_ptr<DataItem>> m_items;
    std::vector<DataChangeCallback> m_callbacks;
    std::vector<LayerChangeCallback> m_layerCallbacks;
    
    // Map data
    double m_currentLat;
    double m_currentLon;
    int m_zoomLevel;
    MapBounds m_visibleBounds;
    std::unordered_map<std::string, std::shared_ptr<MapLayer>> m_layers;
    
    void notifyDataChanged(const std::string& itemName);
    void notifyLayerChanged(const std::string& layerId);
};

class DataItem {
public:
    DataItem(const std::string& name, const std::string& value);
    
    const std::string& getName() const;
    const std::string& getValue() const;
    void setValue(const std::string& value);
    
private:
    std::string m_name;
    std::string m_value;
};

class GeoCoordinate {
public:
    GeoCoordinate(double lat, double lon);
    double latitude() const { return m_lat; }
    double longitude() const { return m_lon; }
    
private:
    double m_lat;
    double m_lon;
};

} // namespace my_desktop_app
