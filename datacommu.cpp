#include "datacommu.h"
#include <QDebug>

DataCommu::DataCommu(QString nom, QString id, QObject *parent) : QObject(parent)
{
    m_id = id;
    m_nom = nom;
    m_result = 0;
}

QString DataCommu::id() const
{
    return m_id;
}

QString DataCommu::nom() const
{
    return m_nom;
}

int DataCommu::result() const
{
    return m_result;
}

void DataCommu::setResult(int result)
{
    //qDebug() << QString::number(result);
    m_result = result;
    emit resultM();
}
