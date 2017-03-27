#ifndef DATAUSERU_H
#define DATAUSERU_H


#include <QObject>
#include "data.h"

class DataUserU : public QObject
{
    Q_OBJECT
    public:
        explicit DataUserU(User *e, UserCommu *u, bool o, QObject *parent = 0);

        Q_PROPERTY(QString nom READ nom)
        QString nom()
        {
            return QString(m_e->nom + " " + m_e->prenom);
        }

        Q_PROPERTY(QString id READ id)
        QString id()
        {
            return m_e->ID;
        }

        Q_PROPERTY(QString abs READ abs)
        QString abs()
        {
            if (m_o == true)
                return "L'utilisateur n'apparait pas dans cette communauté";
            else if (m_u->absent == true)
                return "L'utilisateur est absent de la communauté ou hors de l'annuaire";
            else
             return "";
        }

        Q_PROPERTY(QString nbDocument READ nbDocument)
        QString nbDocument()
        {
            if (m_o == true)
                return 0;
            return QString::number(m_u->documentsResponsable.size());
        }

        Q_PROPERTY(QString nbDomainesResp READ nbDomainesResp)
        QString nbDomainesResp()
        {
            if (m_o == true)
                return 0;
            return QString::number(m_u->domainesResponsable.size());
        }

        Q_PROPERTY(QString nbDomainesGest READ nbDomainesGest)
        QString nbDomainesGest()
        {
            if (m_o == true)
                return 0;
            return QString::number(m_u->domainesGestionnaire.size());
        }

    private:
        UserCommu *m_u;
        User *m_e;
        bool m_o;
};

#endif // DATAUSERU_H
