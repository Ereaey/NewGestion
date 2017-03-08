#ifndef DATADOMAINE_H
#define DATADOMAINE_H

#include <QObject>

class DataDomaine : public QObject
{
    Q_OBJECT
    public:
        explicit DataDomaine(QString nom, QString iddomaine, QString reponsable = "", QString idresp = "", QObject *parent = 0);

        Q_PROPERTY(QString nom READ nom WRITE setNom)
        QString nom() const;
        void setNom(QString nom);

        Q_PROPERTY(QString iddomaine READ iddomaine WRITE setIddomaine)
        QString iddomaine() const;
        void setIddomaine(QString iddomaine);

        Q_PROPERTY(QString responsable READ responsable WRITE setResponsable)
        QString responsable() const;
        void setResponsable(QString responsable);

        Q_PROPERTY(QString idresponsable READ idresponsable WRITE setIdResponsable)
        QString idresponsable() const;
        void setIdResponsable(QString IdResponsable);
    private:
        QString m_iddomaine;
        QString m_nom;
        QString m_responsable;
        QString m_idresp;
};

#endif // DATADOMAINE_H
