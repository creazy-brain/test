#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    flage=1;
    update();
    ui->setupUi(this);
    new_star=new QPushButton(this);
    new_star->setFixedSize(100,100);
    qssFile = new QFile(":/button.qss", this);
    qssFile->open(QFile::ReadOnly);
    QString styleSheet = tr(qssFile->readAll());
    new_star->setStyleSheet(styleSheet);
    new_star->move(150,400);
    connect(new_star,&QPushButton::clicked,this,[=](){
        chose->play();
        zoom1();
        zoom2();
        QTimer::singleShot(400,this,[=](){
            flage=2;
            new_star->setHidden(true);
            update();
            emit change_to_page2();
        });
    });
    connect(this,&MainWindow::change_to_page2,this,&MainWindow::dram_page2);
    connect(this,&MainWindow::change_to_page3,this,&MainWindow::dram_page3);
    chose=new QSound(":/resource/music/TapButtonSound.wav",this);
    play_coin=new QSound(":/resource/music/ConFlipSound.wav",this);
    end_mdia=new QSound(":/resource/music/LevelWinSound.wav",this);
    back=new QSound(":/resource/music/BackButtonSound.wav",this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::paintEvent(QPaintEvent *event){
    QPainter *qpainter=new QPainter(this);
    QPixmap pic,pix_title,pix_bg;
    switch (flage) {
    case 1:
             pic= QPixmap(":/resource/image/MenuSceneBg.png");
             qpainter->drawPixmap(0,0,this->width(),this->height(),pic);
        break;
    case 2:
             pic = QPixmap(":/resource/image/OtherSceneBg.png");
             qpainter->drawPixmap(0,0,this->width(),this->height(),pic);
             pix_title=QPixmap(":/resource/image/Title.png");
             qpainter->drawPixmap(0,0,350,100,pix_title);
        break;
    case 3:
             pic = QPixmap(":/resource/image/PlayLevelSceneBg.png");
             qpainter->drawPixmap(0,0,this->width(),this->height(),pic);
             pix_title=QPixmap(":/resource/image/Title.png");
             qpainter->drawPixmap(0,0,350,100,pix_title);
             pix_bg=QPixmap(":/resource/image/BoardNode.png");
             for(int i=0;i<4;i++){
                 for(int j=0;j<4;j++){
                    qpainter->drawPixmap(100-22+j*64,150-16+76*i,50,50,pix_bg);
                 }
             }

        break;
    }
}
void MainWindow::dram_page2(){
    if(page2.isEmpty()){
        w1 = new QWidget;
        w1->setParent(this);
        QVBoxLayout *vlayout = new QVBoxLayout;
        int i,j,value=1;
        for(i=1;i<=5;i++){
            QHBoxLayout *layout = new QHBoxLayout;
            for(j=1;j<=4;j++){
                QPushButton *button1 = new QPushButton;
                leveicon=new QFile(":/button_click.qss",this);
                leveicon->open(QFile::ReadOnly);
                 QString styleSheet = tr(leveicon->readAll());
                button1->setStyleSheet(styleSheet);
                button1->setFixedSize(50,50);
                button1->setText(QString::number(value));
                connect(button1,&QPushButton::clicked,this,[=](){
                chose->play();
                leveflage=value;
                emit change_to_page3();
                });
                layout->addWidget(button1);
                value++;
            }
            layout->setSpacing(0);
            layout->setMargin(0);
            vlayout->addLayout(layout);
        }
        w1->setLayout(vlayout);
        w1->setFixedSize(300,350);
        w1->move(50,100);
        w1->show();
        page2_back=new QPushButton(this);
        page2_back->setParent(this);
        back_button=new QFile(":/back_select.qss",this);
        back_button->open(QFile::ReadOnly);
        QString styleSheet = tr(back_button->readAll());
        page2_back->setStyleSheet(styleSheet);
        page2_back->setFixedSize(100,50);
        page2_back->setHidden(false);
        page2_back->move(270,500);
        page2=w1->findChildren<QPushButton *>();
        qDebug()<<QString::number(page2.isEmpty());
        connect(page2_back,&QPushButton::clicked,this,&MainWindow::dram_page1);
    }else{
        for(int i=0;i<20;i++){
            page2.at(i)->setHidden(false);
            }
        w1->setHidden(false);
        page2_back->setHidden(false);
    }
}
void MainWindow::dram_page1(){
    back->play();
    flage=1;
    update();
    for(int i=0;i<20;i++){
        page2.at(i)->setHidden(true);
    }
    w1->setHidden(true);
    page2_back->setHidden(true);
    new_star->setHidden(false);
}
void MainWindow::dram_page3(){
    flage=3;
    update();

    for(int i=0;i<20;i++){
        page2.at(i)->setHidden(true);
    }
    if(page3.isEmpty()){
        end_titl=new QLabel;
        end_titl->setParent(this);
        end_titl->setFixedSize(300,100);
        end_titl->move(50,10);
        end_titl->setStyleSheet("border-image:url(:/resource/image/LevelCompletedDialogBg.png)");
        page2_back->setHidden(true);
        page3_back=new QPushButton(this);
        page3_back->setParent(this);
        back_button=new QFile(":/back_select.qss",this);
        back_button->open(QFile::ReadOnly);
        QString styleSheet = tr(back_button->readAll());
        page3_back->setStyleSheet(styleSheet);
        page3_back->setFixedSize(100,50);
        page3_back->setHidden(false);
        page3_back->move(270,500);
        w2 = new QWidget;
        w2->setParent(this);
        QVBoxLayout *vlayout = new QVBoxLayout;
        for(int i=1;i<5;i++){
            QHBoxLayout *layout = new QHBoxLayout;
            for(int j=1;j<=4;j++){
                QPushButton *button1 = new QPushButton;
                current_data[i-1][j-1]=levec_data[leveflage-1][i-1][j-1];
                if(current_data[i-1][j-1]){
                button1->setStyleSheet("border-image:url(:/resource/image/Coin0001.png)");
                }else{
                    button1->setStyleSheet("border-image:url(:/resource/image/Coin0008.png)");
                }
                button1->setFixedSize(40,40);
                connect(button1,&QPushButton::clicked,this,[=](){
                    if(fanzhuan_flage){
                        play_coin->play();
                        fanzhuan_flage=false;
                        change_button=j+(i-1)*4;
                        change_coin();
                    }
                });
                layout->addWidget(button1);
            }
            layout->setSpacing(0);
            layout->setMargin(0);
            vlayout->addLayout(layout);
        }
        w2->setLayout(vlayout);
        w2->setFixedSize(300,350);
        w2->move(50,100);
        w2->show();
        page3=w2->findChildren<QPushButton*>();
        connect(page3_back,&QPushButton::clicked,this,[=](){
            back->play();
            for(int i=0;i<16;i++){
                page3.at(i)->setHidden(true);
            }
            fanzhuan_flage=true;
            leve->setHidden(true);
            w2->setHidden(true);
            page3_back->setHidden(true);
            flage=2;
            end_titl->setHidden(true);
            update();
            emit change_to_page2();
        });
        leve=new QLabel;
        leve->setParent(this);
        QString str="LeveL: "+QString::number(leveflage);
        leve->setText(str);
        leve->setFixedSize(200,50);
        leve->setHidden(false);
        QFont font("黑体",30);
        leve->setFont(font);
        leve->move(20,510);
    }else
    {

        for(int i=0;i<16;i++){
            page3.at(i)->setHidden(false);
            current_data[i/4][i%4]=levec_data[leveflage-1][i/4][i%4];
            if(current_data[i/4][i%4]){
            page3.at(i)->setStyleSheet("border-image:url(:/resource/image/Coin0001.png)");
            }else{
                page3.at(i)->setStyleSheet("border-image:url(:/resource/image/Coin0008.png)");
            }
        }
        QString str="LeveL: "+QString::number(leveflage);
        leve->setText(str);
        leve->setHidden(false);
        w2->setHidden(false);
        page3_back->setHidden(false);
    }
}
void MainWindow::zoom1(){
    QPropertyAnimation *animation=new QPropertyAnimation(new_star,"geometry");
    animation->setDuration(200);
    animation->setStartValue(QRect(new_star->x(),new_star->y(),new_star->width(),new_star->height()));
    animation->setEndValue(QRect(new_star->x(),new_star->y()+10,new_star->width(),new_star->height()));
    animation->setEasingCurve(QEasingCurve::OutBounce);
    animation->start();
}
void MainWindow::zoom2(){
    QPropertyAnimation *animation=new QPropertyAnimation(new_star,"geometry");
    animation->setDuration(200);
    animation->setStartValue(QRect(new_star->x(),new_star->y()+10,new_star->width(),new_star->height()));
    animation->setEndValue(QRect(new_star->x(),new_star->y(),new_star->width(),new_star->height()));
    animation->setEasingCurve(QEasingCurve::OutBounce);
    animation->start();
}
void MainWindow::change_coin(){
        time1=new QTimer(this);
        connect(time1,&QTimer::timeout,this,&MainWindow::change_coin_forward);
        time2=new QTimer(this);
        connect(time2,&QTimer::timeout,this,&MainWindow::change_coin_back);
        data[0]=1;
        data[1]=6;
        time1->start(100);
        time2->start(100);
        QTimer::singleShot(700,this,[=](){
            time1->stop();
            time2->stop();
            if((change_button-1)/4==change_button/4&&change_button!=16){
            current_data[change_button/4][change_button%4]=data_flage[0];
            }
            if((change_button-1)/4==(change_button-2)/4 && change_button!=1){
            current_data[(change_button-2)/4][(change_button-2)%4]=data_flage[1];
            }
            if((change_button-1)>3){
            current_data[((change_button-1)-4)/4][((change_button-1)-4)%4]=data_flage[2];
            }
            if((change_button-1)<12){
            current_data[((change_button-1)+4)/4][((change_button-1)+4)%4]=data_flage[3];
            }
            current_data[(change_button-1)/4][(change_button-1)%4]=data_flage[4];
            end=1;
            for(int i=0;i<4;i++){
                for(int j=0;j<4;j++){
                    end=current_data[i][j]&end;
                }
            }
            if(end==1){
                end_del();
            }else{
            fanzhuan_flage=true;
            }
        });
}
void MainWindow::change_coin_forward(){
    data[0]++;
    data[0]%=8;
    if((change_button-1)/4==change_button/4&&change_button!=16){
        if(current_data[change_button/4][change_button%4]==1){
        page3.at(change_button)->setStyleSheet(chang_coin_data[data[0]]);
        data_flage[0]=0;
        }
    }
    if((change_button-1)/4==(change_button-2)/4 && change_button!=1){
        if(current_data[(change_button-2)/4][(change_button-2)%4]==1){
        page3.at(change_button-2)->setStyleSheet(chang_coin_data[data[0]]);
        data_flage[1]=0;
        }
    }
    if((change_button-1)>3){
        if(current_data[((change_button-1)-4)/4][((change_button-1)-4)%4]==1){
         page3.at((change_button-1)-4)->setStyleSheet(chang_coin_data[data[0]]);
         data_flage[2]=0;
        }
    }
    if((change_button-1)<12){
        if(current_data[((change_button-1)+4)/4][((change_button-1)+4)%4]==1){
         page3.at((change_button-1)+4)->setStyleSheet(chang_coin_data[data[0]]);
         data_flage[3]=0;
        }
    }
    if(current_data[(change_button-1)/4][(change_button-1)%4]==1){
     page3.at(change_button-1)->setStyleSheet(chang_coin_data[data[0]]);
     data_flage[4]=0;
    }
}
void MainWindow::change_coin_back(){
    if(data[1]>=0){data[1]--;}
    if(current_data[(change_button-1)/4][(change_button-1)%4]==0){
        page3.at(change_button-1)->setStyleSheet(chang_coin_data[data[1]]);
        data_flage[4]=1;
    }
    if((change_button-1)/4==change_button/4&&change_button!=16){
        if(current_data[change_button/4][change_button%4]==0){
        page3.at(change_button)->setStyleSheet(chang_coin_data[data[1]]);
        data_flage[0]=1;
        }
    }
    if((change_button-1)/4==(change_button-2)/4 && change_button!=1){
        if(current_data[(change_button-2)/4][(change_button-2)%4]==0){
        page3.at(change_button-2)->setStyleSheet(chang_coin_data[data[1]]);
        data_flage[1]=1;
        }
    }
    if((change_button-1)>3){
        if(current_data[((change_button-1)-4)/4][((change_button-1)-4)%4]==0){
        page3.at((change_button-1)-4)->setStyleSheet(chang_coin_data[data[1]]);
        data_flage[2]=1;
        }
    }
    if((change_button-1)<12 ){
        if(current_data[((change_button-1)+4)/4][((change_button-1)+4)%4]==0){
        page3.at((change_button-1)+4)->setStyleSheet(chang_coin_data[data[1]]);
        data_flage[3]=1;
        }
    }
}
void MainWindow::end_del(){
        end_mdia->play();
        end_titl->setHidden(false);

}

