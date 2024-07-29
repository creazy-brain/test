#ifndef MOVE_H
#define MOVE_H

#include <QObject>
#include <QPushButton>
class fuck : public QObject
{
    Q_OBJECT
public:
    explicit fuck(QObject *parent = nullptr);

signals:
    void statmove_single();

public slots:
    void starmove(QPushButton *btn);
};

#endif // MOVE_H
