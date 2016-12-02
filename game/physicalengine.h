#ifndef PHYSICALENGINE_H
#define PHYSICALENGINE_H

#include <QQuickItem>
#include "ball.h"



class physicalEngine : public QQuickItem
{
    Q_OBJECT
public:
    physicalEngine();

    int  calculateX(int id);
    int  calculateY(int id);
    void moveItem(int id);
    void initPointers();



signals:

public slots:


private :
    QMap<int , Ball*> m_id_pointers;
};

#endif // PHYSICALENGINE_H
