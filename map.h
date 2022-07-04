#ifndef MAP_H
#define MAP_H
#include <QVector>

class Map
{
    QVector<QVector<bool>> map;
public:
    Map() = default;
    Map(size_t size, size_t bombs_num, size_t first_move_x, size_t first_move_y);
    bool HasBomb(size_t x, size_t y) const;
    size_t CountNeighbouringBombs(size_t x, size_t y) const;
    size_t getSize() const;
public:
    template<class Functor>
    static void performFunctionOnAllNeighbours(size_t x, size_t y, size_t size, Functor functor);
};

template<class Functor>
inline void Map::performFunctionOnAllNeighbours(size_t x, size_t y, size_t size, Functor functor)
{
    for(int i=-1; i<=1; ++i)
    {
        for(int j=-1; j<=1; ++j)
        {
            if(i == 0 && j == 0)
            {
                continue;
            }
            else if(x+i >= 0 && x+i < size && y+j >= 0 && y+j < size)
            {
                functor(x+i, y+j);
            }
        }
    }
}

#endif // MAP_H
