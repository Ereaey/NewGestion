#ifndef DATAUSER_H
#define DATAUSER_H

#include <QObject>

class DataUser : public QObject
{
    Q_OBJECT
    public:
        explicit DataUser(QString nom, QString id, QString nbDocument, QString nbDomaineRespon, QString nbDomaineGest, QString nbDomaineLect, QString nbDomaineModif, QObject *parent = 0);

        Q_PROPERTY(QString nom READ nom)
        QString nom() const{return m_nom;}

        Q_PROPERTY(QString id READ id)
        QString id() const{return m_id;}

        Q_PROPERTY(QString nbDocument READ nbDocument)
        QString nbDocument() const{return m_nbDocument;}

        Q_PROPERTY(QString nbDomaineRespon READ nbDomaineRespon)
        QString nbDomaineRespon() const{return m_nbDomaineRespon;}

        Q_PROPERTY(QString nbDomaineGest READ nbDomaineGest)
        QString nbDomaineGest() const{return m_nbDomaineGest;}

        Q_PROPERTY(QString nbDomaineLect READ nbDomaineLect)
        QString nbDomaineLect() const{return m_nbDomaineLect;}

        Q_PROPERTY(QString nbDomaineModif READ nbDomaineModif)
        QString nbDomaineModif() const{return m_nbDomaineModif;}



    private:
        QString m_nom;
        QString m_id;
        QString m_nbDocument;
        QString m_nbDomaineRespon;
        QString m_nbDomaineGest;
        QString m_nbDomaineLect;
        QString m_nbDomaineModif;
};

#endif // DATAUSER_H
