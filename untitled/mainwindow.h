#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QPoint>
#include <QFile>
#include <QPainter>
#include <QPixmap>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QList>
#include <QDebug>
#include <QPropertyAnimation>
#include <QTimer>
#include <QLabel>
#include <QSound>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QPushButton *new_star,*page2_back,*page3_back;
    QFile *qssFile,*leveicon,*back_button;
    QList<QPushButton*> page2,page3;
    QWidget *w1,*w2;
    QTimer *time1,*time2,*time3;
    QLabel *end_titl,*leve;
    QSound *chose,*back,*play_coin,*end_mdia;
    int data[2];
    int data_flage[5];
    void paintEvent(QPaintEvent *event);
    void zoom1();
    void zoom2();
public slots:
    void dram_page2();
    void dram_page1();
    void dram_page3();
    void change_coin();
    void change_coin_forward();
    void change_coin_back();
    void end_del();
private:
    Ui::MainWindow *ui;
    int flage;
    int leveflage;
    int change_button;
    int count;
    int fanzhuan_flage=true;
    int end;
    const int levec_data[20][4][4]={
        {
            {1,1,1,1},
            {1,1,0,1},
            {1,0,0,0},
            {1,1,0,1}
        },
        {
            {1,0,1,1},
            {0,0,1,1},
            {1,1,0,0},
            {1,1,0,1}
        },
        {
            {0,0,0,0},
            {0,1,1,0},
            {0,1,1,0},
            {0,0,0,0}
        },
        {
            {0,1,1,1},
            {1,0,0,1},
            {1,0,1,1},
            {1,1,1,1}
        },
        {
            {0,1,1,1},
            {1,0,0,1},
            {1,0,1,1},
            {1,1,1,1}
        },
        {
            {1,0,0,1},
            {0,1,1,0},
            {0,1,1,0},
            {1,0,0,1}
        },
        {
            {0,1,1,1},
            {1,0,1,1},
            {1,1,0,1},
            {1,1,1,0}
        },
        {
            {0,1,0,1},
            {1,0,0,0},
            {0,0,0,1},
            {1,0,1,0}
        },
        {
            {1,0,1,0},
            {1,0,1,0},
            {0,0,1,0},
            {1,0,0,1}
        },
        {
            {1,0,1,1},
            {1,1,0,0},
            {0,0,1,1},
            {1,1,0,1}
        },
        {
            {0,1,1,0},
            {1,0,0,1},
            {1,0,0,1},
            {0,1,1,0}
        },
        {
            {0,1,1,0},
            {0,0,0,0},
            {1,1,1,1},
            {0,0,0,0}
        },
        {
            {0,1,1,0},
            {0,0,0,0},
            {0,0,0,0},
            {0,1,1,0}
        },

        {
            {1,0,1,1},
            {0,1,0,1},
            {1,0,1,0},
            {1,1,0,1}
        },
        {
            {0,1,0,1},
            {1,0,0,0},
            {1,0,0,0},
            {0,1,0,1}
        },
        {
            {0,1,1,0},
            {1,1,1,1},
            {1,1,1,1},
            {0,1,1,0}
        },
        {
            {0,1,1,1},
            {0,1,0,0},
            {0,0,1,0},
            {1,1,1,0}
        },
        {
            {0,0,0,1},
            {0,0,1,0},
            {0,1,0,0},
            {1,0,0,0}
        },
        {
            {0,1,0,0},
            {0,1,1,0},
            {0,0,1,1},
            {0,0,0,0}
        },
        {
            {0,0,0,1},
            {0,0,1,0},
            {0,1,0,0},
            {1,0,0,0}
        }
    };
    int current_data[4][4]={
        {1,1,1,1},
        {1,1,1,1},
        {1,1,1,1},
        {1,1,1,1}
    };
    QString chang_coin_data[8]={
        "border-image:url(:/resource/image/Coin0001.png)",
        "border-image:url(:/resource/image/Coin0002.png)",
        "border-image:url(:/resource/image/Coin0003.png)",
        "border-image:url(:/resource/image/Coin0004.png)",
        "border-image:url(:/resource/image/Coin0005.png)",
        "border-image:url(:/resource/image/Coin0006.png)",
        "border-image:url(:/resource/image/Coin0007.png)",
        "border-image:url(:/resource/image/Coin0008.png)"
    };
signals:
    void change_to_page2();
    void change_to_page3();
    void end_singl();
};


#endif // MAINWINDOW_H
