#ifndef DATA_H
#define DATA_H

#include <QString>
#include <QMap>
#include <QVector>
#include <QDate>
#include "treeitem.h"
#include "treemodel.h"
#include <QMutex>

struct UserCommu;
struct Domaine;

struct User
{
    QString ID;
    QString nom, prenom;
    bool psa = true;
};

struct Goal
{
    QString nom;
    QString ID;
    QVector<User*> users;
    User *responsable;
    QString etat;
};

struct Document
{
    QString nom;
    int Confidentialitee;
    int nombresPJ;
    UserCommu *proprietaire;
    Domaine *domaine;
    int statutDoc;
    QDate dateCreation;
    QDate dateModif;
    QString version;
    QString id;
    int nbConsult, nbConsultRecente;
};

struct UserCommu
{
    User *user;

    bool absent;
    QVector<Domaine*> domainesDoublon;
    //QVector<Domaine*> domainesPerimee;

    QVector<Domaine*> domainesResponsable;
    QVector<Domaine*> domainesGestionnaire;
    QVector<Domaine*> domainesModificateur;
    QVector<Domaine*> domainesLecteur;

    QVector<Domaine*> domainesModificateurGOAL;//via goal
    QVector<Domaine*> domainesLecteurGOAL;//via goal

    QVector<Document*> documentsResponsable;

    QVector<Domaine*> domainesavecdocPro;
};

struct Communaute;

struct Domaine
{
    QString nom;
    int id, id_parent;
    UserCommu *responsable;
    QVector<Document*> documents;
    QVector<Document*> documentsVide;
    QVector<Document*> documentsPlein;

    Domaine *parent;
    QVector<Domaine*> enfants;
    QMap<QString, UserCommu*> users;
    TreeItem *t;
    Communaute *commu;
    bool problem;
};

struct UPerime
{
    UserCommu *user;
    Domaine *d;
};

struct Communaute
{
    QString name;
    int note, synchronises, asservisseurs, niveau, lsynchronises;
    int t6mois, c2t, c3t;
    Domaine *root;
    Model rootTree;

    QVector<Goal*> goalsMembers;

    QMap<QString, UserCommu*> users;
    //QMap<QString, Domaine*> domaines;
    QMap<QString, Domaine*> domainesKey;
    QMap<QString, Goal*> goals;
    QMap<QString, Document*> documents;

    QMap<QString, Goal*> goalsInexistantsMap;
    QVector<Goal*> goalsVides;
    QVector<Goal*> goalsInexistants;
    QMap<QString, QMap<int, Domaine*>> domainesInexistantMap;

    QMap<QString, QVector<Domaine*>> domainesGoalModificateurs;
    QMap<QString, QVector<Domaine*>> domainesGoalLecteurs;
    QMap<QString, QVector<Domaine*>> domainesGoalGestionnaires;
    QMap<QString, QVector<Domaine*>> domainesGoal;

    QVector<Domaine*> domainesVides;
    QVector<Domaine*> domainesPlein;//+10 documents

    QVector<Domaine*> domainesDoublonML;
    QVector<Domaine*> domainesDoublonRG;
    QVector<Domaine*> domainesDoublon;
    QVector<UserCommu*> usersDoublon;

    QVector<UserCommu*> usersInconnu;//Plus dans les membres de la communauté
    QVector<UserCommu*> usersNonTrouve;

    QMap<QString, UserCommu*> usersResponsable;
    QMap<QString, UserCommu*> usersGestionnaire;
    QMap<QString, UserCommu*> usersModificateurs;
    QMap<QString, UserCommu*> usersLecteurs;

    QMap<QString, UserCommu*> usersProprietaire;

    QMap<QString, UserCommu*> usersPerimee;//Date dépassée
    QVector<UPerime*> domainesPerimeM;//Date dépassée user
    QVector<UPerime*> domainesPerimeL;//Date dépassée user


    QVector<Document*> documentsVide;//Sans PJ
    QVector<Document*> documentsSurcharge;//Sans PJ
    QMap<int, QVector<Document*>> documentsConfidentialitees;
    QMap<int, QVector<Document*>> documentsPJ;

    QVector<Document*> documentsPublie;
    QVector<Document*> documentsEnTravail;
    QVector<Document*> documentsEnTravail6Mois;
};

enum typeDoc{C0, C1, C2, C3, C4};
enum statutDoc{Publie, Annule, Travail};
enum grade{RESPONSABLE, GESTIONNAIRES, MODIFICATEURS, LECTEURS, MODIFICATEURS_GOAL, LECTEURS_GOAL, GESTIONNAIRES_GOAL};
class Data : public QObject
{
    Q_OBJECT
    public:
        Data(Model* tree);
        void addUser(QString identifiant, QString nom, QString prenom);
        void addGoal(QString nom, QString ID, QString identifiantResponsable, QString etat);
        void addGoalMember(QString idGoal, QString idMember);
        void addCommunaute(QString name, QStringList goals);
        void addDomaine(QString nameCommu, QString nameDomaine, QString IdDomaine, QString IdDomaineParent,
                        QStringList GOALsmodificateurs, QStringList GOALsLecteurs, QStringList GOALsGestionnaires,QString responsable,
                        QStringList gestionnaires, QStringList modificateurs, QStringList lecteurs, QString niveau,
                        QString asservisseur, QString synchronises
                        );
        void addDocument(QString name, QString idDomaine, QString version, QString proprietaire, QString id,
                         QString dateCreation, QString dateModif, QString nbPj, QString namePj, int nbConsult, int nbConsultRecente,
                         QString confidentialite, QString Statut);
        QMap<QString, Communaute*> getCommus(){ return communautes;}
        void setCurrentCommu(QString name);
        Communaute* getCurrentCommu(){return c_actu;}
        bool getParentInexistant(Domaine *d, QString goal);
        QVector<int> getDomaineGoalInexistant(QString goal);
        int e;
        void getInfo();
        Q_INVOKABLE void generateTree();
        QMap<QString, User*> userId;

    public slots:

        void generateData();
        void drawTree(QString goal, bool modif, bool lecteur, bool gestionnaire);
        void drawTree(QString domaine);
        void drawTreeUserId(QString user, int type);
    signals:
        void commuChanged();
    private:
        int addDomaineUser(Domaine *d, QString user, int grade);
        void addDomaineGoal(Domaine *d, Goal *g, int grade);
        void recursiveOpen(int id);

        QMap<QString, QVector <User*>> userPrenomNom;
        QMap<QString, QVector<User*>> userNomPrenom;

        QMap<QString, Goal*> goalId;
        QMap<QString, Goal*> goalNom;

        QMap<QString, Communaute*> communautes;
        Communaute* c_actu;

        QMap<int, Domaine*> domaines;
        QVector<Domaine*> domainesV;

        Model* treeMo;
        QMutex dataD;
        User *m_userU;
};

#endif // DATA_H
