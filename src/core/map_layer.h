#pragma once

#include <string>
#include <vector>
#include <memory>
#include <unordered_map>

namespace my_desktop_app {

enum class LayerType {
    Points,
    Lines,
    Polygons,
    Heatmap,
    Raster,
    Custom
};

// Forward declarations
class GeoPoint;
class GeoLine;
class GeoPolygon;

// Base class for all map layers
class MapLayer {
public:
    MapLayer(const std::string& id, const std::string& name, LayerType type);
    virtual ~MapLayer();
    
    const std::string& getId() const;
    const std::string& getName() const;
    void setName(const std::string& name);
    
    LayerType getType() const;
    bool isVisible() const;
    void setVisible(bool visible);
    
    int getZIndex() const;
    void setZIndex(int zIndex);
    
    float getOpacity() const;
    void setOpacity(float opacity);
    
    std::unordered_map<std::string, std::string> getMetadata() const;
    void setMetadata(const std::string& key, const std::string& value);
    
    virtual void update() = 0;
    virtual void render() = 0;

protected:
    std::string m_id;
    std::string m_name;
    LayerType m_type;
    bool m_visible;
    int m_zIndex;
    float m_opacity;
    std::unordered_map<std::string, std::string> m_metadata;
};

// Specific layer implementations
class PointLayer : public MapLayer {
public:
    PointLayer(const std::string& id, const std::string& name);
    
    void addPoint(double lat, double lon, const std::string& label = "");
    void clearPoints();
    size_t getPointCount() const;
    
    void update() override;
    void render() override;
    
private:
    std::vector<std::unique_ptr<GeoPoint>> m_points;
};

class LineLayer : public MapLayer {
public:
    LineLayer(const std::string& id, const std::string& name);
    
    void addLine(const std::vector<std::pair<double, double>>& points);
    void clearLines();
    
    void update() override;
    void render() override;
    
private:
    std::vector<std::unique_ptr<GeoLine>> m_lines;
};

class PolygonLayer : public MapLayer {
public:
    PolygonLayer(const std::string& id, const std::string& name);
    
    void addPolygon(const std::vector<std::pair<double, double>>& points);
    void clearPolygons();
    
    void update() override;
    void render() override;
    
private:
    std::vector<std::unique_ptr<GeoPolygon>> m_polygons;
};

} // namespace my_desktop_app
