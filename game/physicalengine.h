#ifndef PHYSICALENGINE_H
#define PHYSICALENGINE_H

#include <QQuickItem>
#include "ball.h"
#include <QTimer>
#include <pocket.h>



class physicalEngine : public QQuickItem
{
    Q_OBJECT
public:
    physicalEngine();
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    int  calculateX(int id);
    int  calculateY(int id);
    int  calculateX(Ball * obj);
    int  calculateY(Ball * obj);

    void moveItem(int id);
    void moveItem(Ball * obj);
    bool isInPocket(int x, int y);
    bool isBorder(Ball * obj);
    Q_INVOKABLE void initPointers();
    Q_INVOKABLE void toStartPos();
    int m_currentId;
    bool isPress = false;

    QTimer moveTimer;
    QTimer pushTimer;

    int     m_PrevX;
    int     m_PrevY;



signals:
     void pocketEx(int pos_x,int pos_y);
public slots:

    void moveAll();
    void savePos();

private :
    QMap<int , Ball*> m_id_pointers;
    QList<Pocket*> m_Pockets_list;
};

#endif // PHYSICALENGINE_H
