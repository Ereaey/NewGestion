#ifndef DATADOCUMENT_H
#define DATADOCUMENT_H

#include <QObject>

class DataDocument : public QObject
{
    Q_OBJECT
    public:
        explicit DataDocument(QString nom, QString id, int iddomaine, QObject *parent = 0);

        Q_PROPERTY(QString nom READ nom)
        QString nom() const{return m_nom;}

        Q_PROPERTY(QString iddomaine READ iddomaine)
        QString iddomaine() const{return m_iddomaine;}

        Q_PROPERTY(QString id READ id)
        QString id() const{return m_id;}

    private:
        QString m_nom;
        QString m_id;
        QString m_iddomaine;
};

#endif // DATADOCUMENT_H
