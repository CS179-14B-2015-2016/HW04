#include <iostream>
#include <vector>
#include <math.h>
#include <cstdlib>
#include "Grid.h"
//#include "Vector2Plus.cpp"
//#include "MainLoop.cpp" --> or where class Entity is located


class Vector2
{
public:
    float x, y;
    Vector2(float xVal, float yVal)
    {
        x = xVal;
        y = yVal;
    }
    Vector2()
    {
        x = 0;
        y = 0;
    }
};

//Spatial Partition
Grid::Grid(int width, int height, int cellSize) :
m_width(width),
m_height(height),
m_cellSize(cellSize) {
    m_numXCells = ceil((float)m_width / m_cellSize);
    m_numYCells = ceil((float)m_height / m_cellSize);
    
    // Allocate all the cells
    const int ENTITIES_TO_RESERVE = 100;
    m_cells.resize(m_numYCells * m_numXCells);
    for (int i = 0; i < m_cells.size(); i++) {
        m_cells[i].entities.reserve(ENTITIES_TO_RESERVE);
    }
}

Grid::~Grid() {
}

void Grid::addEntity(Entity* entity) {
    Cell* cell = getCell(entity->position);
    cell->entities.push_back(entity);
    entity->ownerCell = cell;
    entity->cellVectorIndex = cell->entities.size() - 1;
}

void Grid::addEntity(Entity* entity, Cell* cell) {
    cell->entities.push_back(entity);
    entity->ownerCell = cell;
    entity->cellVectorIndex = cell->entities.size() - 1;
}

Cell* Grid::getCell(int x, int y) {
    if (x < 0) x = 0;
    if (x >= m_numXCells) x = m_numXCells;
    if (y < 0) y = 0;
    if (y >= m_numYCells) y = m_numYCells;
    
    return &m_cells[y * m_numXCells + x];
}

Cell* Grid::getCell(const glm::vec2& pos) {
    int cellX = (int)(pos.x / m_cellSize);
    int cellY = (int)(pos.y / m_cellSize);
    
    return getCell(cellX, cellY);
}

void Grid::removeEntityFromCell(Entity* entity) {
    std::vector<Entity*>& entities = entity->ownerCell->entities;
    // Normal vector swap
    entities[entity->cellVectorIndex] = entities.back();
    entities.pop_back();
    // Update vector index
    if (entity->cellVectorIndex < entities.size()) {
        entities[entity->cellVectorIndex]->cellVectorIndex = entity->cellVectorIndex;
    }
    // Set the index of entity to -1
    entity->cellVectorIndex = -1;
    entity->ownerCell = nullptr;
}

//AABB Collision Detection
float clamp(float value, float min, float max)
{
    if(value < min) return min;
    if(value > max) return max;
    return value;
}

bool isColliding(Vector2 circleCenter, float r, Vector2 rectCenter, float xSize, float ySize)
{
    float xMax = rectCenter.x + (xSize/2.0);
    float xMin = rectCenter.x - (xSize/2.0);
    float yMin = rectCenter.y - (ySize/2.0);
    float yMax = rectCenter.y + (ySize/2.0);
    
    float nearX = clamp(circleCenter.x, xMin, xMax);
    float nearY = clamp(circleCenter.y, yMin, yMax);
    
    float xDiff = circleCenter.x-nearX;
    float yDiff = circleCenter.y-nearY;
    float distSquared = (xDiff*xDiff) + (yDiff*yDiff);
    
    return (distSquared < r*r);
}