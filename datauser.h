#ifndef DATAUSER_H
#define DATAUSER_H

#include <QObject>

class DataUser : public QObject
{
    Q_OBJECT
    public:
        explicit DataUser(QString nom, QString id, QObject *parent = 0);

        Q_PROPERTY(QString nom READ nom)
        QString nom() const{return m_nom;}

        Q_PROPERTY(QString id READ id)
        QString id() const{return m_id;}

        QString getNom(){return m_nom;}
    private:
        QString m_nom;
        QString m_id;
};

#endif // DATAUSER_H
