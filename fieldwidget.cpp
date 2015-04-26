#include "fieldwidget.h"


FieldWidget::FieldWidget(QWidget *parent) :
    QWidget(parent),
    color("#000"),
    timer(new QTimer(this)),
    generation(0),
    fieldSize(10)

{
    timer->setInterval(80);
    // заполняем массив фолсами
    memset(&cells, false, sizeof(cells));
}

// отвечает за отрисовку
void FieldWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    // рисуем сетку
    paintGrid(painter);
}

void FieldWidget::paintGrid(QPainter &painter)
{
    // ставим цвет
    color.setAlpha(20);
    painter.setPen(color);

    // рисуем рамочку по краям
    QRect borders(0, 0, width() - 1, height() - 1);
    painter.drawRect(borders);

    // рисуем вертикальные линии
    double cellWidth = (double) width() / fieldSize;
    for (double i = cellWidth; i <= width(); i += cellWidth) {
        painter.drawLine(i, 0, i, height());
    }

    // рисуем горизонтальные линии
    double cellHeight = (double) height() / fieldSize;
    for (double i = cellHeight; i <= height(); i += cellHeight) {
        painter.drawLine(0, i, width(), i);
    }
}

