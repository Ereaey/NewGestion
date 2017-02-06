#include "datauser.h"

DataUser::DataUser(QString nom, QString id, QObject *parent) : QObject(parent)
{
    m_nom = nom;
    m_id = id;
}
