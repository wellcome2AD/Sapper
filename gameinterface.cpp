#include <QGridLayout>
#include <QMessageBox>
#include <QApplication>
#include <QPaintEvent>
#include <QIcon>
#include <QPixmap>
#include <QDebug>
#include <QString>
#include "gameinterface.h"
#include "mybutton.h"

GameInterface::GameInterface(size_t size, size_t bombs_num, QWidget *parent)
    : QWidget(parent), map_size(size), map_bombs_num(bombs_num)
{
    initializeComponents();
}

void GameInterface::initializeComponents()
{
    opened_cells = 0;
    QGridLayout* layout = new QGridLayout(this);
    for(size_t i = 0; i < map_size; ++i)
    {
        for(size_t j = 0; j < map_size; ++j)
        {
            MyButton* button = new MyButton(i, j, this);
            layout->addWidget(button, i, j);
            connect(button, SIGNAL(clicked()), SLOT(OnLeftButtonClicked()));
            connect(button, SIGNAL(rightButtonClicked()), SLOT(OnRightButtonClicked()));
        }
    }
    setLayout(layout);
}

void GameInterface::clearComponents()
{
    map = Map();
    QLayoutItem* layout_item = nullptr;
    while((layout_item = layout()->takeAt(0)) != nullptr)
    {
        delete layout_item->widget();
    }
    delete layout();
}

GameInterface::~GameInterface()
{
    clearComponents();
}

void GameInterface::OnLeftButtonClicked()
{
    auto obj = sender();
    auto button = qobject_cast<MyButton*>(obj);
    if(button == nullptr)
    {
        throw std::exception("Signal from button is incorrect");
    }
    if(!button->getMineFlag())
    {
        auto x = button->getX(), y = button->getY();
        handleLeftButtonClicked(x, y);
    }
}
void GameInterface::OnRightButtonClicked()
{
    auto obj = sender();
    auto button = qobject_cast<MyButton*>(obj);
    if(button == nullptr)
    {
        throw std::exception("Signal from button is incorrect");
    }
    button->SwitchFlag();
}

void GameInterface::handleLeftButtonClicked(size_t x, size_t y)
{
    if(opened_cells == 0)
    {
        map = Map(map_size, map_bombs_num, x, y);
    }
    MyButton* button = buttonAt(x, y);
    if(!button->isEnabled())
    {
        return;
    }
    button->setDisabled(true);
    button->setStyleSheet("background-color: white");
    if(map.HasBomb(x, y))
    {
        ShowContent();
        button->PaintContent(MyButton::ExplodedBomb);
        QMessageBox::warning(this, "Game Over!", "Game Over!");
        clearComponents();
        initializeComponents();
    }
    else
    {
        size_t bombs_around =  map.CountNeighbouringBombs(x, y);
        button->PaintContent(MyButton::Number, QString::number(bombs_around));
        if(bombs_around == 0)
        {
            size_t size = map.getSize();
            Map::performFunctionOnAllNeighbours(x, y, size, [this](size_t x, size_t y){
                handleLeftButtonClicked(x, y);
            });
        }

        ++opened_cells;
        if(opened_cells == (map_size * map_size - map_bombs_num))
        {
            QMessageBox::information(this, "You won!", "You won!");
            clearComponents();
            initializeComponents();
        }
    }

    QApplication::sendEvent(this, new QPaintEvent(this->rect()));
}

MyButton* GameInterface::buttonAt(size_t x, size_t y) const
{
    MyButton* button = nullptr;
    auto grid_layout = qobject_cast<QGridLayout*>(layout());
    if (grid_layout)
    {
        auto layout_item = grid_layout->itemAtPosition(x, y);
        if(layout_item)
        {
            auto widget = layout_item->widget();
            if(widget)
            {
                button = qobject_cast<MyButton*>(widget);
            }
        }
    }
    if (button == nullptr)
    {
        throw std::exception("Error: incorrect cast");
    }
    return button;
}

void GameInterface::ShowContent() const
{
    for(int i = 0; i < map_size; ++i)
    {
        for(int j = 0; j < map_size; ++j)
        {
            MyButton* button = buttonAt(i, j);
            MyButton::TypeOfCell type;
            QString text;
            if(button->getMineFlag())
            {
                type = MyButton::MineFlag;
            }
            else if(map.HasBomb(i, j))
            {
                type = MyButton::Bomb;
            }
            else
            {
                type = MyButton::Number;
                text = QString::number(map.CountNeighbouringBombs(i, j));
            }
            button->PaintContent(type, text);
        }
    }
}
