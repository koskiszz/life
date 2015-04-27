#ifndef FIELDWIDGET_H
#define FIELDWIDGET_H

#include <QWidget>
#include <QColor>
#include <QTimer>
#include <QPainter>
#include <QMouseEvent>

class FieldWidget : public QWidget
{
    Q_OBJECT
public:
    explicit FieldWidget(QWidget *parent = 0);
    ~FieldWidget();

signals:

public slots:
    void start();
    void stop();
    void clear();

private slots:
    void paintGrid(QPainter &painter);
    void paintCells(QPainter &painter);
    void newGeneration();

private:
    QColor color;
    QTimer* timer;
    bool** cells;
    bool** next;
    int fieldSize;

    bool isAlive(int i, int j);
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

};

#endif // FIELDWIDGET_H
