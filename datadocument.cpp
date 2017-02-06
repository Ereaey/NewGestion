#include "datadocument.h"

DataDocument::DataDocument(QString nom, QString id, int iddomaine, QObject *parent) : QObject(parent)
{
    m_nom = nom;
    m_id = id;
    m_iddomaine = QString::number(iddomaine);
}
