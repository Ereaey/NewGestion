#include "autocompletuser.h"
#include <QDebug>

autoCompletUser::autoCompletUser()
{

}

void autoCompletUser::searchUser(QString nom)
{
    m_user = nom.toUpper();
    start();
}

void autoCompletUser::addUser(QString nom, QString id)
{
    m_m.lock();
    DataUser *u = new DataUser(nom, id);
    m_users.push_back(u);
    m_m.unlock();
}

void autoCompletUser::run()
{
    qDebug() << "test " << m_user;
    m_finish = false;
    finishChanged();
    m_result.clear();
    if (!m_user.isEmpty())
    {
        qDebug() << "search " << QString::number(m_users.size());
        for (int i = 0; i < m_users.size(); i++)
        {
            //qDebug() << m_users[i]->getNom();

            if (m_users[i]->getNom().indexOf(m_user) == 0)
            {
                m_result.append(m_users[i]);
                qDebug() << "ok";
            }
        }
    }
    qDebug() << "finish search";
    m_finish = true;
    finishChanged();
    refreshResult();
}
