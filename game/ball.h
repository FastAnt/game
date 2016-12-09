#ifndef BALL_H
#define BALL_H

#include <QQuickItem>
#include <QTimer>
#include <QPoint>
#include <QDebug>

class Ball :public QQuickItem
{
    Q_OBJECT
public:

    Ball()
    {
        // setAcceptedMouseButtons(Qt::AllButtons);

    }
    ~Ball(){}
    double  m_sin = 0;
    double  m_cos = 0;
    double  m_velocity = 0;

    int     m_x = 200;
    int     m_y = 200;
    Q_INVOKABLE void setStertX(int x) {m_x  =x;}
    Q_INVOKABLE void setStartY(int y) {m_y = y;}

    QTimer moveTimer;
    bool isPress;
};

#endif // BALL_H
