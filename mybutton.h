#ifndef MYBUTTON_H
#define MYBUTTON_H

#include <QPushButton>

class MyButton : public QPushButton
{
    Q_OBJECT
private:
    size_t x_coord;
    size_t y_coord;
    bool mineFlag = false;
public:
    enum TypeOfCell
    {
        ExplodedBomb, ClosedCell, Number, MineFlag, Bomb
    };
public:
    MyButton(size_t x, size_t y, QWidget *parent = nullptr);
    size_t getX() const;
    size_t getY() const;
    void mousePressEvent(QMouseEvent* event) override;
    void SwitchFlag();
    bool getMineFlag() const;
    void PaintContent(TypeOfCell type, const QString& text = QString());
signals:
    void rightButtonClicked();
};

#endif // MYBUTTON_H
