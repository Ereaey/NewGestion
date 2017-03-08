#ifndef DATADOCUMENT_H
#define DATADOCUMENT_H

#include <QObject>

class DataDocument : public QObject
{
    Q_OBJECT
    public:
        explicit DataDocument(QString nom, QString id, int iddomaine, QString proprio,
                              QString idproprio, QObject *parent = 0);

        Q_PROPERTY(QString nom READ nom)
        QString nom() const{return m_nom;}

        Q_PROPERTY(QString iddomaine READ iddomaine)
        QString iddomaine() const{return m_iddomaine;}

        Q_PROPERTY(QString id READ id)
        QString id() const{return m_id;}

        Q_PROPERTY(QString proprio READ proprio)
        QString proprio() const{return m_proprio;}

        Q_PROPERTY(QString idproprio READ idproprio)
        QString idproprio() const{return m_idproprio;}


    private:
        QString m_nom;
        QString m_id;
        QString m_iddomaine;
        QString m_proprio;
        QString m_idproprio;
};

#endif // DATADOCUMENT_H
