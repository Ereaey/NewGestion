#ifndef TREATMENT_H
#define TREATMENT_H

#include "data.h"
#include <QThread>
#include "datacommu.h"
#include <QVariant>
#include "datagoal.h"
#include "datadomaine.h"
#include "qfile.h"
#include "datadocument.h"
#include "datauser.h"
#include "datanote.h"

class Treatment : public QThread
{
    Q_OBJECT
    Q_PROPERTY(bool finish READ finish NOTIFY finishChanged)
    Q_PROPERTY(QVariant commu READ commu NOTIFY refreshCommu)
    Q_PROPERTY(QVariant result READ result NOTIFY refreshResult)
    Q_PROPERTY(QVariant descriptionResult READ descriptionResult NOTIFY refreshDescriptionResult)
    Q_PROPERTY(QString currentCommu READ currentCommu NOTIFY commuChanged)
    Q_PROPERTY(QString currentAction READ currentAction NOTIFY currentActionChanged)

    enum t{SEARCH_GOAL_MODIF, SEARCH_GOAL_LECT, SEARCH_GOAL, SEARCH_GOAL_VIDE, SEARCH_DOMAINE, SEARCH_GOAL_PROBLEME, SEARCH_DOMAINE_VIDE, SEARCH_DOMAINE_FULL,
          EXPORT_PLAN, SEARCH_DOCUMENT_VIDE, SEARCH_DOCUMENT_SURCHARGE, SEARCH_DOCUMENT, SEARCH_USER, SEARCH_USER_ABSENT, NOTE_GLOBALE, SEARCH_USER_HORS_PSA,
          SEARCH_GOAL_DOUBLON, SEARCH_USER_DOUBLON, SEARCH_USER_PERIME, SEARCH_USER_ID, SEARCH_GOAL_GEST};

    enum type{RESPONSABLE = 0, GESTIONNAIRE = 1, MODIFICATEUR = 2, LECTEUR = 3};
    public:
        Treatment(Data *d);
        Q_INVOKABLE void searchGoal(QString goal, bool modificateur, bool lecteur, bool gestionnaire);
        bool finish() const;
        QVariant result() const{return QVariant::fromValue(m_result);}
        QVariant descriptionResult() const{return QVariant::fromValue(m_descriptionResult);}
        QVariant commu() const{return QVariant::fromValue(m_commu);}
        QString currentCommu()
        {
            /*
            if (m_currentCommu.isEmpty() && m_data->getCommus().size() > 0)
                m_currentCommu = m_data->getCommus().keys()[0];
*/
            return m_currentCommu;
        }
        QString currentAction() const{return m_currentAction;}
        Q_INVOKABLE void setCommu(QString name);
        Q_INVOKABLE void load();
        Q_INVOKABLE void searchGoalsVide();
        Q_INVOKABLE void searchGoalsProbleme();
        Q_INVOKABLE void searchDomaine(QString name);
        Q_INVOKABLE void searchDomaineVide();
        Q_INVOKABLE void searchDomaineFull();
        Q_INVOKABLE void searchDocumentVide();
        Q_INVOKABLE void searchDocumentSurchage();
        Q_INVOKABLE void searchDocument(QString name);
        Q_INVOKABLE void searchUser(QString name, int type);
        Q_INVOKABLE void searchUserAbsent();
        Q_INVOKABLE void searchUserHorsPSA();
        Q_INVOKABLE void noteGlobale();
        Q_INVOKABLE void searchGoalDoublon();
        Q_INVOKABLE void searchUserDoublon(bool resp);
        Q_INVOKABLE void searchUserPerime(bool resp);
        Q_INVOKABLE void exportPlan(QString idDomaine, QString path);
        Q_INVOKABLE void searchUserId(QString name, int type);
        Q_INVOKABLE void loadCara();


    private:
        Data *m_data;
        bool m_finish;
        int m_type, m_typeUser;
        QString m_goal;
        QString m_currentAction;
        QString m_currentCommu;
        QString m_domaine;
        QString m_document;
        QList<QObject*> m_commu;
        QList<QObject*> m_result;
        QObject* m_descriptionResult;
        QString m_path;
        QString m_dataDocument;
        QString m_file1, m_file2;
        QString m_user;
        QString generatePlan(QString idDomaine);

    Q_SIGNALS:
        void finishChanged();
        void refreshCommu();
        void refreshResult();
        void commuChanged();
        void currentActionChanged();
        void refreshDescriptionResult();

    public slots:

    protected:
        void run();

};

#endif // TREATMENT_H
