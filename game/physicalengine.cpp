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

}

int physicalEngine::calculateX(int id)
{
    return  m_id_pointers[ id ]->m_x + m_id_pointers[ id ]->m_velocity*m_id_pointers[ id ]->m_cos;
}

int physicalEngine::calculateY(int id)
{
    return  m_id_pointers[ id ]->m_y + m_id_pointers[ id ]->m_velocity*m_id_pointers[ id ]->m_sin;
}


void physicalEngine::moveItem(int id)
{
    m_id_pointers[ id ]->setX(calculateX(id));
    m_id_pointers[ id ]->setY(calculateY(id));
    if(  m_id_pointers[ id ]->m_velocity>=1)
        m_id_pointers[ id ]->m_velocity--;
}

void physicalEngine::initPointers()
{
    for(auto elem : id_names)
    {
        if(parent()->findChild<Ball*>(elem))
            m_id_pointers[ id_names.key(elem)] = parent()->findChild<Ball*>(elem);
    }
}
