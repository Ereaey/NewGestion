#include "datauser.h"

DataUser::DataUser(QString nom, QString id, QString nbDocument,
                   QString nbDomaineRespon, QString nbDomaineGest,
                   QString nbDomaineLect, QString nbDomaineModif, QObject *parent) : QObject(parent)
{
    m_nom = nom;
    m_id = id;
    m_nbDomaineRespon = nbDomaineRespon;
    m_nbDocument = nbDocument;
    m_nbDomaineGest = nbDomaineGest;
    m_nbDomaineLect = nbDomaineLect;
    m_nbDomaineModif = nbDomaineModif;
}
