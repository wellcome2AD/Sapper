#include "map.h"
#include <random>

Map::Map(size_t size, size_t bombs_num, size_t first_move_x, size_t first_move_y) : map(QVector<QVector<bool>>(size, QVector<bool>(size, false)))
{
    srand(time(0));
    for(size_t i = 0; i < bombs_num;)
    {
        int x = rand() % size;
        int y = rand() % size;
        if(!map[x][y] && !(x == first_move_x && y == first_move_y))
        {
            map[x][y] = true;
            ++i;
        }
    }
}

bool Map::HasBomb(size_t x, size_t y) const
{
    return map.at(x).at(y);
}

size_t Map::CountNeighbouringBombs(size_t x, size_t y) const
{
    size_t count = 0;
    size_t size = map.size();
    performFunctionOnAllNeighbours(x, y, size, [this, &count](size_t x, size_t y){
        if(map.at(x).at(y))
        {
            ++count;
        }
    });
    return count;
}

size_t Map::getSize() const
{
    return map.size();
}
