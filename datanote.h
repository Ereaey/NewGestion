#ifndef DATANOTE_H
#define DATANOTE_H

#include <QObject>
#include "data.h"

class DataNote : public QObject
{
    Q_OBJECT
    public:
        explicit DataNote(Data *d, QObject *parent = 0);

        Q_PROPERTY(int note READ note NOTIFY noteChanged)
        Q_PROPERTY(int nbUser READ nbUser NOTIFY nbUserChanged)
        Q_PROPERTY(int nbDomaine READ nbDomaine NOTIFY nbDomaineChanged)
        Q_PROPERTY(int nbDocument READ nbDocument NOTIFY nbDocumentChanged)
        Q_PROPERTY(int nbGoal READ nbGoal NOTIFY nbGoalChanged)
        Q_PROPERTY(int niveau READ niveau NOTIFY niveauChanged)

        int note()
        {
            return m_d->getCurrentCommu()->note;
        }
        int nbUser()
        {
            return m_d->getCurrentCommu()->users.size();
        }
        int nbDomaine()
        {
            return m_d->getCurrentCommu()->domainesKey.size();
        }
        int nbDocument()
        {
            return m_d->getCurrentCommu()->documents.size();
        }
        int nbGoal()
        {
            return m_d->getCurrentCommu()->goals.size();
        }
        int niveau()
        {
            return m_d->getCurrentCommu()->niveau;
        }

        Q_PROPERTY(QString domaineVide READ domaineVide NOTIFY domaineVideChanged)
        Q_PROPERTY(QString domaineFull READ domaineFull NOTIFY domaineFullChanged)
        Q_PROPERTY(QString domaineAsservisseurs READ domaineAsservisseurs NOTIFY domaineAsservisseursChanged)
        Q_PROPERTY(QString domaineLibreS READ domaineLibreS NOTIFY domainesLibreSChanged)
        Q_PROPERTY(QString domaineLibre READ domaineLibre NOTIFY domainesLibreChanged)

        QString domaineVide()
        {
            return "<font color=\"#D49C0B\">" + QString::number(m_d->getCurrentCommu()->domainesVides.size()) + "</font> - <i><b>" + QString::number((float)m_d->getCurrentCommu()->domainesVides.size() * 100.0 / (float)m_d->getCurrentCommu()->domainesKey.size()) + "% </b></i>";
        }
        QString domaineFull()
        {
            return "<font color=\"#097E00\">" + QString::number(m_d->getCurrentCommu()->domainesPlein.size()) + "</font>";
        }
        QString domaineAsservisseurs()
        {
            return QString::number(m_d->getCurrentCommu()->asservisseurs);
        }
        QString domaineLibreS()
        {
            return QString::number(m_d->getCurrentCommu()->lsynchronises);
        }
        QString domaineLibre()
        {
            return QString::number(m_d->getCurrentCommu()->synchronises);
        }

        Q_PROPERTY(QString documentsC0 READ documentsC0 NOTIFY documentsC0Changed)
        Q_PROPERTY(QString documentsC1 READ documentsC1 NOTIFY documentsC0Changed)
        Q_PROPERTY(QString documentsC2 READ documentsC2 NOTIFY documentsC0Changed)
        Q_PROPERTY(QString documentsC3 READ documentsC3 NOTIFY documentsC0Changed)
        Q_PROPERTY(QString documentsC4 READ documentsC4 NOTIFY documentsC0Changed)

        QString documentsC0()
        {
            return QString::number(m_d->getCurrentCommu()->documentsConfidentialitees[0].size());
        }
        QString documentsC1()
        {
            return QString::number(m_d->getCurrentCommu()->documentsConfidentialitees[1].size());
        }
        QString documentsC2()
        {
            return QString::number(m_d->getCurrentCommu()->documentsConfidentialitees[2].size());
        }
        QString documentsC3()
        {
            return QString::number(m_d->getCurrentCommu()->documentsConfidentialitees[3].size());
        }
        QString documentsC4()
        {
            return QString::number(m_d->getCurrentCommu()->documentsConfidentialitees[4].size());
        }

        Q_PROPERTY(QString documentsP READ documentsP NOTIFY documentsC0Changed)
        Q_PROPERTY(QString documentsE READ documentsE NOTIFY documentsC0Changed)
        Q_PROPERTY(QString documentsSPJ READ documentsSPJ NOTIFY documentsC0Changed)
        Q_PROPERTY(QString documentsFull READ documentsFull NOTIFY documentsC0Changed)

        QString documentsP()
        {
            return QString::number(m_d->getCurrentCommu()->documentsPublie.size());
        }
        QString documentsE()
        {
            return QString::number(m_d->getCurrentCommu()->documentsEnTravail.size());
        }

        QString documentsSPJ()
        {
            return QString::number(m_d->getCurrentCommu()->documentsVide.size());
        }
        QString documentsFull()
        {
            return QString::number(m_d->getCurrentCommu()->documentsSurcharge.size());
        }

        Q_PROPERTY(QString responsable READ responsable NOTIFY documentsC0Changed)
        Q_PROPERTY(QString gestionnaires READ gestionnaires NOTIFY documentsC0Changed)
        Q_PROPERTY(QString nominatif READ nominatif NOTIFY documentsC0Changed)
        Q_PROPERTY(QString proprietaires READ proprietaires NOTIFY documentsC0Changed)

        QString responsable()
        {
            return QString::number(m_d->getCurrentCommu()->usersResponsable.size());
        }
        QString gestionnaires()
        {
            return QString::number(m_d->getCurrentCommu()->usersGestionnaire.size());
        }

        QString nominatif()
        {
            return QString::number(m_d->getCurrentCommu()->usersModificateurs.size() + m_d->getCurrentCommu()->usersLecteurs.size());
        }

        QString proprietaires()
        {
            return QString::number(m_d->getCurrentCommu()->usersProprietaire.size());
        }

        Q_PROPERTY(QString goalsVide READ goalsVide NOTIFY documentsC0Changed)
        Q_PROPERTY(QString goals READ goals NOTIFY documentsC0Changed)
        Q_PROPERTY(QString goalsInexistant READ goalsInexistant NOTIFY documentsC0Changed)
        Q_PROPERTY(QString usersAbsent READ usersAbsent NOTIFY documentsC0Changed)

        QString goalsVide()
        {
            return QString::number(m_d->getCurrentCommu()->goalsVides.size());
        }

        QString goals()
        {
            return QString::number(m_d->getCurrentCommu()->goals.size());
        }

        QString goalsInexistant()
        {
            return QString::number(m_d->getCurrentCommu()->goalsInexistants.size());
        }
        QString usersAbsent()
        {
            return QString::number(m_d->getCurrentCommu()->usersInconnu.size());
        }

        Q_PROPERTY(QString doct6mois READ doct6mois NOTIFY documentsC0Changed)
        Q_PROPERTY(QString c2t READ c2t NOTIFY documentsC0Changed)
        Q_PROPERTY(QString c3t READ c3t NOTIFY documentsC0Changed)
        Q_PROPERTY(QString usersPerimee READ usersPerimee NOTIFY documentsC0Changed)
        QString doct6mois()
        {
            return QString::number(m_d->getCurrentCommu()->t6mois);
        }
        QString c2t()
        {
            return QString::number(m_d->getCurrentCommu()->c2t);
        }

        QString c3t()
        {
            return QString::number(m_d->getCurrentCommu()->c3t);
        }

        QString usersPerimee()
        {
            return QString::number(m_d->getCurrentCommu()->usersPerimee.size());
        }

    Q_SIGNALS:
        void noteChanged();
        void  nbUserChanged();
        void  nbDomaineChanged();
        void  nbDocumentChanged();
        void nbGoalChanged();
        void niveauChanged();

        void domaineVideChanged();
        void domaineFullChanged();
        void domaineAsservisseursChanged();
        void domainesLibreSChanged();
        void domainesLibreChanged();

        void documentsC0Changed();

    public slots:
        void test();

    private:
        Data *m_d;
};

#endif // DATANOTE_H
