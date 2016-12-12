#include "physicalengine.h"
#include <QMap>
#include <QString>
QMap<int , QString> id_names = {
    {0,"gBall"},
    {1,"fBall"},
    {2,"sBall"},
    {3,"tBall"}
};

physicalEngine::physicalEngine()
{
    setAcceptedMouseButtons(Qt::AllButtons);
}

void physicalEngine::mouseMoveEvent(QMouseEvent *event)
{
    if(isPress)
    {
        if(event->pos().rx() > this->width() -  this->width()/20|| event->pos().rx() <= -2 )
        {
//            if(isInPocket(obj->m_x +obj->width()/2  , obj->m_y +obj->height()/2))
//                obj->m_velocity = 0;
//            qDebug() << obj->m_x << "   ----> exploution X  " ;
//            obj->m_cos = - obj->m_cos;
            return ;
        }

        if(event->pos().ry() > this->height() - this->height()/10|| event->pos().ry() <= -2)
        {
//            if(isInPocket(obj->m_x +obj->width()/2  , obj->m_y +obj->height()/2))
//                obj->m_velocity = 0;
//            qDebug() << obj->m_y << "   ----> exploution Y";
//            obj->m_sin = -obj->m_sin;
            return;
        }
        m_id_pointers[ m_currentId ]->m_x = event->pos().rx();
        m_id_pointers[ m_currentId ]->m_y = event->pos().ry();
        qDebug() << QPoint(event->pos());
        m_id_pointers[ m_currentId ]->setPosition(QPoint(event->pos()));
    }

    //        moveTimer.setInterval(50);
    //        moveTimer.start();
}

void physicalEngine::mousePressEvent(QMouseEvent *event)
{

    for(auto obj : this->parent()->findChildren<Ball*>())
    {
        if(obj->isUnderMouse())
        {
            m_currentId  =  obj->property("b_id").toInt();
            isPress = true;
            moveTimer.stop();
            connect(&pushTimer, SIGNAL(timeout()), this, SLOT(savePos()));
            pushTimer.setInterval(100);
            pushTimer.start();
        }
    }


    //        moveTimer.start();
}

void physicalEngine::mouseReleaseEvent(QMouseEvent *event)
{
    //moveTimer.stop();
    isPress = false;
    pushTimer.stop();
    qDebug () << event->x() << " event->x()";
    qDebug () << m_PrevX << " m_PrevX";
    m_id_pointers[ m_currentId ]->m_cos = float((float(event->x() - m_PrevX))/sqrt(pow((event->x() - m_PrevX),2) + pow((event->y() - m_PrevY),2)));
    qDebug() <<  (float(event->x() - m_PrevX)) << "  (float(event->x() - m_PrevX))";
    qDebug() <<  m_id_pointers[ m_currentId ]->m_cos << "  COS";


    m_id_pointers[ m_currentId ]->m_sin = float((event->y() - m_PrevY))/sqrt(pow((event->x() - m_PrevX),2) + pow((event->y() - m_PrevY),2));
    qDebug() <<  float((event->y() - m_PrevY)) << "  float((event->y() - m_PrevY))";
    qDebug() <<  m_id_pointers[ m_currentId ]->m_sin << "  SIN";;
//    m_id_pointers[ m_currentId ]->m_velocity =  not true!!!!
    m_id_pointers[ m_currentId ]->m_velocity = sqrt(pow((float( event->x() - m_PrevX)) * m_id_pointers[ m_currentId ]->m_cos/50,2)
            +pow((float( event->y() - m_PrevY)) * m_id_pointers[ m_currentId ]->m_sin/50,2)) ;
   //connect(&moveTimer, SIGNAL(timeout()), this, SLOT(moveAll()));
     qDebug() <<  m_id_pointers[ m_currentId ]->m_velocity;
   moveTimer.setInterval(30);
   moveTimer.start();
}

int physicalEngine::calculateX(int id)
{
    return  m_id_pointers[ id ]->m_x + m_id_pointers[ id ]->m_velocity*m_id_pointers[ id ]->m_cos;
}

int physicalEngine::calculateY(int id)
{
    return  m_id_pointers[ id ]->m_y + m_id_pointers[ id ]->m_velocity*m_id_pointers[ id ]->m_sin;
}

int physicalEngine::calculateX(Ball * obj)
{
    obj->m_x += obj->m_velocity*obj->m_cos * 15;
    return obj->m_x;
}

int physicalEngine::calculateY(Ball * obj)
{
    obj->m_y +=  obj->m_velocity*obj->m_sin * 15;
    return obj->m_y;
}


void physicalEngine::moveItem(int id)
{
    m_id_pointers[ id ]->setX(calculateX(id));
    m_id_pointers[ id ]->setY(calculateY(id));
    if(  m_id_pointers[ id ]->m_velocity>=1)
        m_id_pointers[ id ]->m_velocity--;
}

bool physicalEngine::isBorder(Ball * obj)
{

    if(obj->m_x>this->width() -  this->width()/20|| obj->m_x <= -2 )
    {
        if(isInPocket(obj->m_x +obj->width()/2  , obj->m_y +obj->height()/2))
            obj->m_velocity = 0;
        qDebug() << obj->m_x << "   ----> exploution X  " ;
        obj->m_cos = - obj->m_cos;
    }

    if(obj->m_y>this->height() - this->height()/10|| obj->m_y <= -2)
    {
        if(isInPocket(obj->m_x +obj->width()/2  , obj->m_y +obj->height()/2))
            obj->m_velocity = 0;
        qDebug() << obj->m_y << "   ----> exploution Y";
        obj->m_sin = -obj->m_sin;
    }

}
void physicalEngine::moveItem(Ball * obj)
{
    obj->setX(calculateX(obj));
    obj->setY(calculateY(obj));
    isBorder(obj);
    qDebug() << obj->m_velocity;
    if(  obj->m_velocity>=0.01)
        obj->m_velocity = obj->m_velocity/1.02;
    else if(obj->m_velocity<=-0.01)
       obj->m_velocity = obj->m_velocity/1.02;
    else obj->m_velocity = 0;



}

bool physicalEngine::isInPocket(int x, int y)
{
    for(auto elem : m_Pockets_list)
    {
        qDebug () << elem->x() << "  " << elem->y();
        qDebug() << x << "  " <<y;

        if((elem->x() < x)&&(elem->x()+ elem->width() > x))
        if((elem->y() < y)&&(elem->y()+ elem->height() > y))
        {
            emit(this->pocketEx(elem->x(),elem->y()));
            return true;
        }
        if(elem->contains(QPointF(x,y)))
        {
            emit(this->pocketEx(elem->x(),elem->y()));
            return true;
        }

    }
    return false;
}


void physicalEngine::initPointers()
{
    for(auto elem : id_names)
    {
        if(parent()->findChild<Ball*>(elem))
            m_id_pointers[ id_names.key(elem)] = parent()->findChild<Ball*>(elem);
    }

    m_Pockets_list =  parent()->findChildren<Pocket*>();
    //connect(&moveTimer,moveTimer.timeout(),this,moveAll());
    connect(&moveTimer, SIGNAL(timeout()), this, SLOT(moveAll()));
    moveTimer.setInterval(30);
    moveTimer.start();
}

void physicalEngine::toStartPos()
{
    m_id_pointers[ 0 ]->m_x = 200;
    m_id_pointers[ 0 ]->m_y = 200;
    m_id_pointers[ 0 ]->m_velocity = 0;
    m_id_pointers[ 0 ]->setOpacity(1);
}

void physicalEngine::moveAll()
{
    for(auto elem : m_id_pointers)
    {
        moveItem(elem);
    }
}
void physicalEngine::savePos()
{
    m_PrevX =  m_id_pointers[ m_currentId ]->m_x;
    m_PrevY =  m_id_pointers[ m_currentId ]->m_y;
}
