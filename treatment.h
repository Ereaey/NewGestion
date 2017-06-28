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
#include "datauseru.h"
#include "datanote.h"
#include "datadomaineu.h"

class Treatment : public QThread
{
    Q_OBJECT
    Q_PROPERTY(bool finish READ finish NOTIFY finishChanged)
    Q_PROPERTY(QVariant commu READ commu NOTIFY refreshCommu)
    Q_PROPERTY(QVariant result READ result NOTIFY refreshResult)
    Q_PROPERTY(QVariant descriptionResult READ descriptionResult NOTIFY refreshDescriptionResult)
    Q_PROPERTY(QString currentCommu READ currentCommu NOTIFY commuChanged)
    Q_PROPERTY(QString currentAction READ currentAction NOTIFY currentActionChanged)
    Q_PROPERTY(QString goal READ currentGoal NOTIFY currentGoalChanged)
    Q_PROPERTY(QVariant listGoal READ listGoal NOTIFY listGoalRefresh)
    Q_PROPERTY(QVariant listUser READ listUser NOTIFY listUserRefresh)
    Q_PROPERTY(QVariant listDoc READ listDoc NOTIFY listDocRefresh)
    Q_PROPERTY(QVariant listDom READ listDom NOTIFY listDomRefresh)
    Q_PROPERTY(QVariant selectDomaine READ selectDomaine NOTIFY selectDomaineRefresh)
    Q_PROPERTY(QVariant selectUser READ selectUser NOTIFY selectUserRefresh)
    Q_PROPERTY(bool domaineexist READ domaineexit NOTIFY selectDomaineRefresh)

    enum t{SEARCH_GOAL_MODIF, SEARCH_GOAL_LECT, SEARCH_GOAL, SEARCH_GOAL_VIDE, SEARCH_DOMAINE, SEARCH_GOAL_PROBLEME, SEARCH_DOMAINE_VIDE, SEARCH_DOMAINE_FULL,
          EXPORT_PLAN, SEARCH_DOCUMENT_VIDE, SEARCH_DOCUMENT_SURCHARGE, SEARCH_DOCUMENT, SEARCH_USER, SEARCH_USER_ABSENT, NOTE_GLOBALE, SEARCH_USER_HORS_PSA,
          SEARCH_GOAL_DOUBLON, SEARCH_USER_DOUBLON, SEARCH_USER_PERIME, SEARCH_USER_ID, SEARCH_GOAL_GEST, SEARCH_ALL_GOAL, EXPORT_ALL_GOAL, EXPORT_DOC};

    enum type{RESPONSABLE = 0, GESTIONNAIRE = 1, MODIFICATEUR = 2, LECTEUR = 3};
    public:
        Treatment(Data *d);
        Q_INVOKABLE void searchGoal(QString goal, bool modificateur, bool lecteur, bool gestionnaire);
        bool finish() const;
        QVariant result() const{return QVariant::fromValue(m_result);}
        QVariant descriptionResult() const{return QVariant::fromValue(m_descriptionResult);}
        QVariant commu() const{return QVariant::fromValue(m_commu);}
        QVariant listGoal() const{return QVariant::fromValue(m_listgoals);}
        QVariant listUser() const{return QVariant::fromValue(m_listusers);}
        QVariant listDoc() const{return QVariant::fromValue(m_listdocs);}
        QVariant listDom() const{return QVariant::fromValue(m_listdoms);}
        QVariant selectDomaine() const{return QVariant::fromValue(m_selectdomaine);}
        QString currentCommu()
        {
            return m_currentCommu;
        }
        QString currentGoal()
        {
            return m_goal;
        }
        QVariant selectUser()
        {
            return QVariant::fromValue(m_selectuser);
        }
        bool domaineexit()
        {
            return m_domaineexit;
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
        Q_INVOKABLE void exportDoc(QString idDomaine, QString path);
        Q_INVOKABLE void searchUserId(QString name, int type);
        Q_INVOKABLE void loadCara();
        Q_INVOKABLE void searchAllGoal();
        Q_INVOKABLE void exportAllGoal(QString path);

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
        QString generateFile(QString idDomaine);
        QList<QObject*> m_listgoals;
        QList<QObject*> m_listusers;
        QList<QObject*> m_listdocs;
        QList<QObject*> m_listdoms;
        QObject* m_selectuser;
        QObject* m_selectdomaine;
        bool m_domaineexit;

    Q_SIGNALS:
        void finishChanged();
        void refreshCommu();
        void refreshResult();
        void commuChanged();
        void currentActionChanged();
        void refreshDescriptionResult();
        void currentGoalChanged();
        void listGoalRefresh();
        void listUserRefresh();
        void selectUserRefresh();
        void listDocRefresh();
        void listDomRefresh();
        void selectDomaineRefresh();

    public slots:

    protected:
        void run();

};

#endif // TREATMENT_H
