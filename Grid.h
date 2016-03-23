//#include "MainLoop.cpp"
#include <vector>

struct Cell {
    std::vector<Entity*> entity;
};

class Grid {
    friend class entityController;
public:
    Grid(int width, int height, int cellSize);
    ~Grid();
    
    /// Adds a entity and determines which cell it belongs to
    void addEntity(Entity* entity);
    /// Adds a entity to the specified cell
    void addEntity(Entity* entity, Cell* cell);
    /// Gets cell based on cell coordinates
    Cell* getCell(int x, int y);
    /// Gets cell based on window coordinates
    Cell* getCell(const glm::vec2& pos);
    
    void removeEntityFromCell(Entity* entity);
    
private:
    std::vector<Cell> m_cells;
    int m_cellSize;
    int m_width;
    int m_height;
    int m_numXCells;
    int m_numYCells;
};
