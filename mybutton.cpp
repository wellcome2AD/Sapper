#include <QFont>
#include <QMouseEvent>
#include "mybutton.h"

MyButton::MyButton(size_t x, size_t y, QWidget *parent)
    : QPushButton(parent), x_coord(x), y_coord(y)
{
    setFixedSize(50, 50);
    QFont font("Arial", 20, QFont::Black);
    setFont(font);
    setStyleSheet("background-color: gray");
    QPalette pal = palette();
    pal.setColor(foregroundRole(), Qt::black);
    setPalette(pal);
}

size_t MyButton::getX() const { return x_coord; }

size_t MyButton::getY() const { return y_coord; }

void MyButton::mousePressEvent(QMouseEvent* event)
{
    if(event->button() == Qt::RightButton)
    {
        emit rightButtonClicked();
    }
    else
    {
        QPushButton::mousePressEvent(event);
    }
}

void MyButton::SwitchFlag()
{
    if (mineFlag)
    {
        PaintContent(MyButton::ClosedCell);
    }
    else
    {
        PaintContent(MyButton::MineFlag);
    }
    mineFlag = !mineFlag;
}

bool MyButton::getMineFlag() const
{
    return mineFlag;
}

void MyButton::PaintContent(TypeOfCell type, const QString& text)
{
    QIcon icon;
    switch(type)
    {
        case MineFlag:
        {
            icon = QIcon("D:\\QtProjects\\Sapper\\flag_icon.png");
            break;
        }
        case ClosedCell:
            break;
        case Number:
        {
            setText(text);
            break;
        }
        case ExplodedBomb:
        {
            setEnabled(true);
            icon = QIcon("D:\\QtProjects\\Sapper\\exploded_bomb_icon.png");
            break;
        }
        case Bomb:
        {
            icon = QIcon("D:\\QtProjects\\Sapper\\bomb_icon.png");
            break;
        }
    }
    setIcon(icon);
    setIconSize(QSize(width() - 2, height() - 2));
}
