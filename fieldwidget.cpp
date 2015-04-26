#include "fieldwidget.h"
#include <qmath.h>
#include <QMessageBox>


FieldWidget::FieldWidget(QWidget *parent) :
    QWidget(parent),
    color("#000"),
    timer(new QTimer(this)),
    fieldSize(20)

{
    timer->setInterval(100);

    // создадим два динамических массива нужного размера
    cells = new bool* [fieldSize + 2];
    next  = new bool* [fieldSize + 2];
    for (int i = 0; i < fieldSize + 2; ++i) {
        cells[i] = new bool [fieldSize + 2];
        next[i]  = new bool [fieldSize + 2];
        // заполним исходный массив нулями
        for (int j = 0; j < fieldSize + 2; ++j) {
            cells[i][j] = false;
            next[i][j] = false;
        }
    }

    connect(timer, SIGNAL(timeout()), this, SLOT(newGeneration()));
}

FieldWidget::~FieldWidget()
{
    for (int i = 0; i < fieldSize + 2; ++i) {
        delete [] cells[i];
        delete [] next[i];
    }
    delete [] cells;
    delete [] next;
}


// срабатывает при клике по ячейке
void FieldWidget::mousePressEvent(QMouseEvent *event)
{
    double cellWidth = (double) width() / fieldSize;
    double cellHeight = (double) height() / fieldSize;

    // подсчитываем в какую ячейку кликнули
    int i = floor(event->y() / cellHeight) + 1;
    int j = floor(event->x() / cellWidth) + 1;

    // изменяем значение и перерисовываем
    cells[i][j] = ! cells[i][j];
    update();
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

void FieldWidget::start()
{
    timer->start();
}

void FieldWidget::stop()
{
    timer->stop();
}

void FieldWidget::clear()
{
    for (int i = 0; i < fieldSize + 2; ++i) {
        for (int j = 0; j < fieldSize + 2; ++j) {
            cells[i][j] = false;
            next[i][j] = false;
        }
    }
    update();
}

void FieldWidget::newGeneration()
{
    bool isChanged = false;

    for (int i = 1; i <= fieldSize; ++i) {
        for(int j = 1; j <= fieldSize; ++j) {
            // для каждой клетки смотрим жива ли она
            next[i][j] = isAlive(i, j);
            // если где-то что-то поменялось, то зафиксируем это
            if (next[i][j] != cells[i][j])
                isChanged = true;
        }
    }

    // если у нас есть изменения
    if (isChanged) {
        // меняем местами массивы и перерисовываем
        bool** tmp = cells;
        cells = next;
        next = tmp;
        update();
    }
    else {
        QMessageBox::information(this, "Finish", "Finish", QMessageBox::Ok);
        stop();
    }
}

bool FieldWidget::isAlive(int i, int j)
{
    int count = 0;
    count += cells[i + 1][j];
    count += cells[i - 1][j];
    count += cells[i][j + 1];
    count += cells[i][j - 1];
    count += cells[i + 1][j + 1];
    count += cells[i - 1][j - 1];
    count += cells[i - 1][j + 1];
    count += cells[i + 1][j - 1];

    if (cells[i][j] == false && count == 3) {
        return true;
    }

    if ((cells[i][j] == true) && ((count == 2) || (count == 3))) {
        return true;
    }

    return false;
}

