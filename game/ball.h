#ifndef BALL_H
#define BALL_H

#include <QQuickItem>
#include <QTimer>

class Ball :public QQuickItem
{
    Q_OBJECT
public:

    Ball() {}
    ~Ball(){}
    double  m_sin;
    double  m_cos;
    double  m_velocity;
    void mouseMoveEvent(QMouseEvent *event)
    {
        if(isPress)
        {
            m_x = event->x();
            m_y = event->y();
        }

//        moveTimer.setInterval(50);
//        moveTimer.start();
    }
    void mousePressEvent(QMouseEvent *event)
    {
          isPress = true;
//        moveTimer.setInterval(50);
//        moveTimer.start();
    }
    void mouseReleaseEvent(QMouseEvent *event)
    {
        //moveTimer.stop();
        m_cos = (event->x() - m_x)/10;
        m_sin = (event->y() - m_y)/10;
        m_velocity = sqrt(m_cos*m_cos + m_sin*m_sin);
        isPress = false;
    }

    int     m_x;
    int     m_y;

    QTimer moveTimer;
    bool isPress;
};

#endif // BALL_H
