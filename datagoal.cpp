#include "datagoal.h"

DataGoal::DataGoal(QString nom, QString idgoal, QString problem, QObject *parent) : QObject(parent)
{
    m_nom = nom;
    m_idgoal = idgoal;
    m_problem = problem;
}
