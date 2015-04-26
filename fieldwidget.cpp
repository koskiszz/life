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
    cells[5][3] = true;
}

// отвечает за отрисовку
void FieldWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    // рисуем сетку
    paintGrid(painter);

    // закрашиваем ячейки
    paintCells(painter);
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

void FieldWidget::paintCells(QPainter &painter)
{
    double cellWidth = (double) width() / fieldSize;
    double cellHeight = (double) height() / fieldSize;

    // обходим по каждой ячеечке
    for (int i = 1; i <= fieldSize; ++i) {
        for (int j = 1; j <= fieldSize; ++j) {
            // и если надо, то красим
            if (cells[i][j] == true) {
                qreal left = (qreal) (cellWidth * j - cellWidth);
                qreal top  = (qreal) (cellHeight * i - cellHeight);
                QRectF r(left, top, (qreal) cellWidth, (qreal) cellHeight);

                color.setAlpha(255);
                painter.fillRect(r, QBrush(color));
            }
        }
    }
}

