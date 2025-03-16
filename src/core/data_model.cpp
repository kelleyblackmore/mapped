#include "core/data_model.h"
#include "core/map_layer.h"
#include <algorithm>
#include <iostream>
#include <fstream>
#include <stdexcept>

namespace my_desktop_app {

// DataModel implementation
DataModel::DataModel() 
    : m_currentLat(0.0),
      m_currentLon(0.0),
      m_zoomLevel(10),
      m_visibleBounds{0.0, 0.0, 0.0, 0.0} {
    std::cout << "Map data model created" << std::endl;
}

DataModel::~DataModel() {
    std::cout << "Data model destroyed" << std::endl;
}

void DataModel::loadData(const std::string& filePath) {
    std::cout << "Loading data from: " << filePath << std::endl;
    
    std::ifstream file(filePath);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + filePath);
    }
    
    // Clear existing data
    m_items.clear();
    
    // Read name-value pairs
    std::string name, value;
    while (file >> name >> value) {
        addItem(name, value);
    }
}

void DataModel::saveData(const std::string& filePath) {
    std::cout << "Saving data to: " << filePath << std::endl;
    
    std::ofstream file(filePath);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file for writing: " + filePath);
    }
    
    // Write name-value pairs
    for (const auto& item : m_items) {
        file << item->getName() << " " << item->getValue() << std::endl;
    }
}

void DataModel::addItem(const std::string& name, const std::string& value) {
    // Check if item already exists
    auto it = std::find_if(m_items.begin(), m_items.end(), 
                          [&name](const auto& item) {
                              return item->getName() == name;
                          });
    
    if (it != m_items.end()) {
        (*it)->setValue(value);
    } else {
        m_items.push_back(std::make_unique<DataItem>(name, value));
    }
    
    notifyDataChanged(name);
}

void DataModel::removeItem(const std::string& name) {
    auto it = std::find_if(m_items.begin(), m_items.end(), 
                          [&name](const auto& item) {
                              return item->getName() == name;
                          });
    
    if (it != m_items.end()) {
        m_items.erase(it);
        notifyDataChanged(name);
    }
}

std::string DataModel::getItemValue(const std::string& name) const {
    auto it = std::find_if(m_items.begin(), m_items.end(), 
                          [&name](const auto& item) {
                              return item->getName() == name;
                          });
    
    if (it != m_items.end()) {
        return (*it)->getValue();
    }
    
    return "";
}

void DataModel::setCurrentLocation(double lat, double lon) {
    m_currentLat = lat;
    m_currentLon = lon;
    
    // Update visible bounds based on new location and zoom
    // This is a simplified calculation
    double offset = 0.01 * (20.0 / m_zoomLevel);
    m_visibleBounds.north = m_currentLat + offset;
    m_visibleBounds.south = m_currentLat - offset;
    m_visibleBounds.east = m_currentLon + offset * 2.0;
    m_visibleBounds.west = m_currentLon - offset * 2.0;
    
    // Notify observers about location change
    notifyDataChanged("location");
}

void DataModel::setZoomLevel(int level) {
    if (level < 1) level = 1;
    if (level > 20) level = 20;
    
    m_zoomLevel = level;
    
    // Update visible bounds based on new zoom
    double offset = 0.01 * (20.0 / m_zoomLevel);
    m_visibleBounds.north = m_currentLat + offset;
    m_visibleBounds.south = m_currentLat - offset;
    m_visibleBounds.east = m_currentLon + offset * 2.0;
    m_visibleBounds.west = m_currentLon - offset * 2.0;
    
    // Notify observers about zoom change
    notifyDataChanged("zoom");
}

int DataModel::getZoomLevel() const {
    return m_zoomLevel;
}

GeoCoordinate DataModel::getCurrentLocation() const {
    return GeoCoordinate(m_currentLat, m_currentLon);
}

MapBounds DataModel::getVisibleBounds() const {
    return m_visibleBounds;
}

void DataModel::addLayer(std::shared_ptr<MapLayer> layer) {
    m_layers[layer->getId()] = layer;
    notifyLayerChanged(layer->getId());
}

void DataModel::removeLayer(const std::string& layerId) {
    auto it = m_layers.find(layerId);
    if (it != m_layers.end()) {
        m_layers.erase(it);
        notifyLayerChanged(layerId);
    }
}

std::shared_ptr<MapLayer> DataModel::getLayer(const std::string& layerId) const {
    auto it = m_layers.find(layerId);
    if (it != m_layers.end()) {
        return it->second;
    }
    return nullptr;
}

std::vector<std::shared_ptr<MapLayer>> DataModel::getLayers() const {
    std::vector<std::shared_ptr<MapLayer>> layers;
    for (const auto& pair : m_layers) {
        layers.push_back(pair.second);
    }
    return layers;
}

void DataModel::registerDataChangeCallback(DataChangeCallback callback) {
    m_callbacks.push_back(callback);
}

void DataModel::registerLayerChangeCallback(LayerChangeCallback callback) {
    m_layerCallbacks.push_back(callback);
}

void DataModel::notifyDataChanged(const std::string& itemName) {
    for (const auto& callback : m_callbacks) {
        callback(itemName);
    }
}

void DataModel::notifyLayerChanged(const std::string& layerId) {
    for (const auto& callback : m_layerCallbacks) {
        callback(layerId);
    }
}

// DataItem implementation
DataItem::DataItem(const std::string& name, const std::string& value)
    : m_name(name), m_value(value) {
}

const std::string& DataItem::getName() const {
    return m_name;
}

const std::string& DataItem::getValue() const {
    return m_value;
}

void DataItem::setValue(const std::string& value) {
    m_value = value;
}

// GeoCoordinate implementation
GeoCoordinate::GeoCoordinate(double lat, double lon)
    : m_lat(lat), m_lon(lon) {
}

} // namespace my_desktop_app
