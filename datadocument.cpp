#include "datadocument.h"

DataDocument::DataDocument(QString nom, QString id, int iddomaine, QString proprio, QString idproprio, QObject *parent) : QObject(parent)
{
    m_nom = nom;
    m_id = id;
    m_iddomaine = QString::number(iddomaine);
    m_proprio = proprio;
    m_idproprio = idproprio;
}
