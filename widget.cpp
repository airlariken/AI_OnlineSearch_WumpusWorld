#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

}

Widget::~Widget()
{
    delete ui;
}

void Widget::imgIni()
{


    if(!(white_img.load("/Users/chenziwei/Qt project/AI_OnlineSearch_WumpusWorld/white_image.jpg"))) { //加载图像
        qDebug()<<"cant open this image"<<endl;
        return;
    }
    if(!(treasure_img.load("/Users/chenziwei/Qt project/AI_OnlineSearch_WumpusWorld/gold_img.jpg"))) { //加载图像
        qDebug()<<"cant open this image"<<endl;
        return;
    }
    if(!(pit_img.load("/Users/chenziwei/Qt project/AI_OnlineSearch_WumpusWorld/pit_img.jpg"))) { //加载图像
        qDebug()<<"cant open this image"<<endl;
        return;
    }
    if(!(human_img.load("/Users/chenziwei/Qt project/AI_OnlineSearch_WumpusWorld/Human_img.jpg"))) { //加载图像
        qDebug()<<"cant open this image"<<endl;
        return;
    }
    if(!(wumpus_img.load("/Users/chenziwei/Qt project/AI_OnlineSearch_WumpusWorld/Wumpus_img.jpg"))) { //加载图像
        qDebug()<<"cant open this image"<<endl;
        return;
    }

    treasure_img = ScaleImage2Label(treasure_img, ui->label_world00);
    pit_img = ScaleImage2Label(pit_img, ui->label_world00);
    human_img = ScaleImage2Label(human_img, ui->label_world00);
    wumpus_img = ScaleImage2Label(wumpus_img, ui->label_world00);


    my_wumpus_world.push_back(ui->label_world00);
    my_wumpus_world.push_back(ui->label_world01);
    my_wumpus_world.push_back(ui->label_world02);
    my_wumpus_world.push_back(ui->label_world03);

    my_wumpus_world.push_back(ui->label_world10);
    my_wumpus_world.push_back(ui->label_world11);
    my_wumpus_world.push_back(ui->label_world12);
    my_wumpus_world.push_back(ui->label_world13);

    my_wumpus_world.push_back(ui->label_world20);
    my_wumpus_world.push_back(ui->label_world21);
    my_wumpus_world.push_back(ui->label_world22);
    my_wumpus_world.push_back(ui->label_world23);

    my_wumpus_world.push_back(ui->label_world30);
    my_wumpus_world.push_back(ui->label_world31);
    my_wumpus_world.push_back(ui->label_world32);
    my_wumpus_world.push_back(ui->label_world33);
    for(int i = 0; i < my_wumpus_world.size(); ++i)
    {
        my_wumpus_world[i]->setPixmap(QPixmap::fromImage(white_img));
    }
}
QImage Widget::ScaleImage2Label(QImage qImage, QLabel* qLabel)
{
    QImage qScaledImage;
    QSize qImageSize = qImage.size();
//        qDebug()<<qImage.size()<<endl;
    QSize qLabelSize = qLabel->size();
//        qDebug()<<qLabel->size()<<endl;
    double dWidthRatio = 1.0*qImageSize.width() / qLabelSize.width();
    double dHeightRatio = 1.0*qImageSize.height() / qLabelSize.height();
    if (dWidthRatio>dHeightRatio) {
        qScaledImage = qImage.scaledToWidth(qLabelSize.width());
    }
    else {
        qScaledImage = qImage.scaledToHeight(qLabelSize.height());
    }
    return qScaledImage;
}

void Widget::on_pushButton_random_ini_world_clicked()//初始化地图
{
    cnt = 1;
    imgIni();
    my_world.iniWorld();
    POINT p = my_world.findCurrentPos();
    my_wumpus_world[p.first*4+p.second]->setPixmap(QPixmap::fromImage(human_img));
    for (int i = 0; i < PITNUMBER; ++i)
    {
        p = my_world.pits_pos[i];
        my_wumpus_world[p.first*4+p.second]->setPixmap(QPixmap::fromImage(pit_img));
    }

    my_wumpus_world[my_world.gold_pos.first*4+my_world.gold_pos.second]->setPixmap(QPixmap::fromImage(treasure_img));
    my_wumpus_world[my_world.wumpus_pos.first*4+my_world.wumpus_pos.second]->setPixmap(QPixmap::fromImage(wumpus_img));
    my_world.gameStart();
}

void Widget::on_pushButton_game_start_clicked()//游戏开始一步步走
{
    if(cnt >= my_world.QTPath.size())   return;
    POINT pre =  my_world.QTPath[cnt-1];
    POINT now =  my_world.QTPath[cnt];
    qDebug()<<pre.first*4+pre.second<<endl;
    qDebug()<<now.first*4+now.second<<endl;
    my_wumpus_world[pre.first*4+pre.second]->setPixmap(QPixmap::fromImage(white_img));
    my_wumpus_world[now.first*4+now.second]->setPixmap(QPixmap::fromImage(human_img));
    cnt++;

}
