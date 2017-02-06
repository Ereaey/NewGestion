#include "datadomaine.h"

DataDomaine::DataDomaine(QString nom, QString iddomaine, QString responsable, QObject *parent) : QObject(parent)
{
    m_nom = nom;
    m_iddomaine = iddomaine;
    m_responsable = responsable;
}

QString DataDomaine::nom() const
{
    return m_nom;
}

void DataDomaine::setNom(QString nom)
{
    m_nom = nom;
}

QString DataDomaine::iddomaine() const
{
    return m_iddomaine;
}

void DataDomaine::setIddomaine(QString iddomaine)
{
    m_iddomaine = iddomaine;
}

QString DataDomaine::responsable() const
{
    return m_responsable;
}
void DataDomaine::setResponsable(QString responsable)
{
    m_responsable = responsable;
}
