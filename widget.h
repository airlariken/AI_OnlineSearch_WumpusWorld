#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QDebug>
#include <QLabel>
#include <QPainter>
#include <QPen>
#include <QImage>
#include <QPixmap>
#include <QSize>
#include "WumpusWorld.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT
    QImage white_img;
    QImage treasure_img;
    QImage pit_img;
    QImage human_img;
    QImage wumpus_img;
    vector<QLabel*> my_wumpus_world;//放置所有label
    WumpusWorld my_world;
    int cnt;//记录步数
public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    QImage ScaleImage2Label(QImage qImage, QLabel* qLabel);
    void imgIni();
private slots:
    void on_pushButton_random_ini_world_clicked();

    void on_pushButton_game_start_clicked();

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
