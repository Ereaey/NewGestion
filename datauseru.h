#ifndef DATAUSERU_H
#define DATAUSERU_H


#include <QObject>
#include "data.h"

class DataUserU : public QObject
{
    Q_OBJECT
    public:
        explicit DataUserU(UserCommu *u, QObject *parent = 0);

        Q_PROPERTY(QString nom READ nom)
        QString nom()
        {
            return QString(m_u->user->nom + " " + m_u->user->prenom);
        }

        Q_PROPERTY(QString id READ id)
        QString id()
        {
            return m_u->user->ID;
        }

        Q_PROPERTY(QString abs READ abs)
        QString abs()
        {
            if (m_u->absent == true)
                return "L'utilisateur est absent de la communauté ou hors de l'annuaire";
            else
             return "";
        }

        Q_PROPERTY(QString nbDocument READ nbDocument)
        QString nbDocument()
        {
            return QString::number(m_u->documentsResponsable.size());
        }

        Q_PROPERTY(QString nbDomainesResp READ nbDomainesResp)
        QString nbDomainesResp()
        {
            return QString::number(m_u->domainesResponsable.size());
        }

        Q_PROPERTY(QString nbDomainesGest READ nbDomainesGest)
        QString nbDomainesGest()
        {
            return QString::number(m_u->domainesGestionnaire.size());
        }

    private:
        UserCommu *m_u;
};

#endif // DATAUSERU_H
