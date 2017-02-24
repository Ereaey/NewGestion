#include "autocompletgoal.h"
#include <QDebug>

autoCompletGoal::autoCompletGoal()
{
}

void autoCompletGoal::search(QString name)
{
    m_goal = name;
    m_goals.sort();
    start();
}

void autoCompletGoal::run()
{
    m_finish = false;
    finishChanged();
    m_result.clear();
    if (!m_goal.isEmpty())
    {
        for (int i = 0; i < m_goals.size(); i++)
        {
            if (m_goals[i].indexOf(m_goal) == 0)
            {
                m_result.append(m_goals[i]);
                qDebug() << "ok";
            }
        }
    }
    m_finish = true;
    finishChanged();
    refreshResult();
}
