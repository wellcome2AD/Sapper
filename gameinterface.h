#ifndef GAMEINTERFACE_H
#define GAMEINTERFACE_H

#include <QWidget>
#include "map.h"
class MyButton;

class GameInterface : public QWidget
{
    Q_OBJECT
private:
    Map map;
    size_t map_size;
    size_t map_bombs_num;
    size_t opened_cells;
private:
    void initializeComponents();
    void clearComponents();
    void handleLeftButtonClicked(size_t x, size_t y);
    MyButton* buttonAt(size_t x, size_t y) const;
    void ShowContent() const;
public:
    GameInterface(size_t size, size_t bombs_num, QWidget *parent = nullptr);
    ~GameInterface();
public slots:
    void OnLeftButtonClicked();
    void OnRightButtonClicked();
};
#endif // GAMEINTERFACE_H
