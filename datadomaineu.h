#ifndef DATADOMAINEU_H
#define DATADOMAINEU_H

#include <QObject>
#include "data.h"

class DataDomaineU : public QObject
{
    Q_OBJECT
public:
    explicit DataDomaineU(Domaine *d, QObject *parent = 0);

    Q_PROPERTY(QString nom READ nom)
    Q_PROPERTY(QString id READ id)
    Q_PROPERTY(QString responsable READ responsable)
    Q_PROPERTY(QString nbDocument READ nbDocument)
    Q_PROPERTY(QString nbEnfant READ nbEnfant)

    QString nom()
    {
        return m_domaine->nom;
    }

    QString id()
    {
        return QString::number(m_domaine->id);
    }

    QString responsable()
    {
        return m_domaine->responsable->user->nom  + " " + m_domaine->responsable->user->prenom;
    }

    QString nbDocument()
    {
        return QString::number(m_domaine->documents.size());
    }

    QString nbEnfant()
    {
        return QString::number(m_domaine->enfants.size());
    }

signals:

public slots:

private:
    Domaine *m_domaine;
};

#endif // DATADOMAINEU_H
