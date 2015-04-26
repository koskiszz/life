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

signals:

public slots:
    void start();
    void stop();
    void clear();

private slots:
    void paintGrid(QPainter &painter);
    void paintCells(QPainter &painter);

private:
    QColor color;
    QTimer* timer;
    int generation;
    bool cells[102][102];
    int fieldSize;

    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *event);

};

#endif // FIELDWIDGET_H
