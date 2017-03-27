#include "data.h"
#include "qdebug.h"

Data::Data(Model* tree)
{
    treeMo = tree;
    //dataD.unlock();
}

void Data::addUser(QString identifiant, QString nom, QString prenom)
{
    dataD.lock();
    User *u = new User;
    u->ID = identifiant.remove(" ");
    u->nom = nom;
    u->prenom = prenom;

    userId[u->ID] = u;
    userNomPrenom[u->nom + " " + u->prenom].push_back(u);
    userPrenomNom[u->prenom + " " + u->nom].push_back(u);
    dataD.unlock();
}

void Data::addGoal(QString nom, QString ID, QString identifiantResponsable, QString etat)
{
    dataD.lock();
    Goal *g = new Goal;
    g->nom = nom;
    g->etat = etat;
    g->responsable = userId[identifiantResponsable];
    g->ID = ID;

    goalId[g->ID] = g;
    goalNom[g->nom] = g;
    //qDebug() << g->nom;
    dataD.unlock();
}

void Data::addGoalMember(QString idGoal, QString idMember)
{
    dataD.lock();
    if (goalId.contains(idGoal) && userId.contains(idMember))
    {
        //qDebug() << "add";
        goalId[idGoal]->users.append(userId[idMember]);
    }
    dataD.unlock();
    return;
}

void Data::addCommunaute(QString name, QStringList goals)
{
    //qDebug() << name;
    dataD.lock();
    communautes[name] = new Communaute;
    communautes[name]->name = name;
    communautes[name]->note = 50;
    communautes[name]->niveau = 0;
    communautes[name]->synchronises = 0;
    communautes[name]->lsynchronises = 0;
    communautes[name]->asservisseurs = 0;
    communautes[name]->t6mois = 0;
    communautes[name]->c2t = 0;
    communautes[name]->c3t = 0;

    //c_actu = communautes[name];
    if (!goals.isEmpty())
    {
        for (int i = 0; i < goals.size(); i++)
        {
            goals[i].remove(" ");
            if (goalNom.contains(goals[i]))
            {
                qDebug() << goals[i] << " " << goalNom[goals[i]]->users.size();
                communautes[name]->goalsMembers.push_back(goalNom[goals[i]]);

                for (int e = 0; e < goalNom[goals[i]]->users.size(); e++)
                {
                    UserCommu *uc = new UserCommu;
                    uc->user = goalNom[goals[i]]->users[e];

                    communautes[name]->users[goalNom[goals[i]]->users[e]->ID] = uc;
                }
            }
        }
    }
    dataD.unlock();
}

void Data::addDomaineGoal(Domaine *d, Goal *g, int grade)
{
    for (int i = 0; i < g->users.size(); i++)
    {
        addDomaineUser(d, "a - " + g->users[i]->ID, grade);
    }
}

int Data::addDomaineUser(Domaine *d, QString user, int grade)
{
    int etat = 0;
    if (user.isEmpty())
        return 1;
    QString id = user.split(" - ")[1];
    id.remove(" ");

    if (!d->commu->users.contains(id))
    {
        if (!userId.contains(id))
        {
            userId[id] = new User;
            userId[id]->nom = user.split(" - ")[0];
            userId[id]->prenom = "(Hors Annuaire PSA)";
            userId[id]->ID = id;
            userId[id]->psa = false;

            /*
            UserCommu *uc = new UserCommu;
            uc->user = userId[id];
            d->commu->users[id] = uc;
            d->commu->usersNonTrouve.push_back(uc);*/
            etat = 2;
        }

        UserCommu *uc = new UserCommu;
        uc->user = userId[id];
        d->commu->users[id] = uc;

        //qDebug() << id;
        if (userId[id]->psa == false && grade != MODIFICATEURS_GOAL && grade != LECTEURS_GOAL)
            d->commu->usersNonTrouve.push_back(uc);
        else if (grade != MODIFICATEURS_GOAL && grade != LECTEURS_GOAL)
            d->commu->usersInconnu.push_back(uc);
    }
    if (grade == RESPONSABLE)
    {
        d->commu->users[id]->domainesResponsable.push_back(d);
        d->responsable = d->commu->users[id];
        d->commu->usersResponsable[id] = d->commu->users[id];
    }
    else if (grade == GESTIONNAIRES)
    {
        d->commu->users[id]->domainesGestionnaire.push_back(d);
        d->commu->usersGestionnaire[id] = d->commu->users[id];
        if (d->responsable == d->commu->users[id])
            d->commu->domainesDoublonRG.append(d);
    }
    else if (grade == MODIFICATEURS_GOAL)
    {
        d->commu->users[id]->domainesModificateurGOAL.push_back(d);
    }
    else if (grade == LECTEURS_GOAL)
    {
        d->commu->users[id]->domainesLecteurGOAL.push_back(d);
    }
    else if (grade == MODIFICATEURS)
    {
        d->commu->users[id]->domainesModificateur.push_back(d);
        d->commu->usersModificateurs[id] = d->commu->users[id];
        if (user.split(" - ").size() == 3)
        {
            if (QDate::fromString(user.split(" - ")[2].remove(" "), "dd/MM/yyyy") > QDate::currentDate())
            {
                d->commu->usersPerimee[id] = d->commu->users[id];
                UPerime *up = new UPerime;
                up->d = d;
                up->user = d->commu->users[id];
                d->commu->domainesPerimeM.append(up);
            }
        }
        d->users[id] = d->commu->users[id];
    }
    else if (grade == LECTEURS)
    {
        d->commu->users[id]->domainesLecteur.push_back(d);
        d->commu->usersLecteurs[id] = d->commu->users[id];
        if (user.split(" - ").size() == 3)
        {
            if (QDate::fromString(user.split(" - ")[2].remove(" "), "dd/MM/yyyy") > QDate::currentDate())
            {
                d->commu->usersPerimee[id] = d->commu->users[id];
                UPerime *up = new UPerime;
                up->d = d;
                up->user = d->commu->users[id];
                d->commu->domainesPerimeL.append(up);
            }
        }
        if (d->users.contains(id))
        {
            d->commu->domainesDoublonML.append(d);
        }
        d->users[id] = d->commu->users[id];
    }

    return etat;
}

void Data::addDomaine(QString nameCommu, QString nameDomaine, QString IdDomaine, QString IdDomaineParent, QStringList GOALsmodificateurs, QStringList GOALsLecteurs, QStringList GOALsGestionnaires, QString responsable, QStringList gestionnaires, QStringList modificateurs, QStringList lecteurs, QString niveau, QString asservisseur, QString synchronises)
{
    if (IdDomaine == "Identifiant du domaine")
        return;
    dataD.lock();
    Domaine *d = new Domaine;
    d->id = IdDomaine.toInt();
    d->nom = nameDomaine;
    d->id_parent = IdDomaineParent.toInt();
    d->problem = false;

    domaines[d->id] = d;
    if (domaines.contains(d->id_parent))
    {
        domaines[d->id_parent]->enfants.push_back(d);
        d->parent = domaines[d->id_parent];
    }
    if (!communautes.contains(nameCommu))
    {
        qDebug() << "bug commu" << nameCommu;
        QStringList l;
        addCommunaute(nameCommu, l);
    }
    //communautes[nameCommu]->domaines[d->nom] = d;
    communautes[nameCommu]->domainesKey[IdDomaine] = d;
    d->commu = communautes[nameCommu];

    if (d->id_parent == 0)
    {
        communautes[nameCommu]->root = d;
    }
    if (niveau.toInt() > communautes[nameCommu]->niveau)
        communautes[nameCommu]->niveau = niveau.toInt();

    if (asservisseur == "Oui")
        communautes[nameCommu]->asservisseurs++;

    if (asservisseur == "Non" && synchronises == "Non")
        communautes[nameCommu]->synchronises++;
    else if (synchronises == "Oui" && asservisseur == "Non")
        communautes[nameCommu]->lsynchronises++;


    if (addDomaineUser(d, responsable, RESPONSABLE) == 2)
        d->problem = true;

    int goalsP = 0;

    for (int i = 0; i < GOALsmodificateurs.size(); i++)
    {
        QString g = GOALsmodificateurs[i].replace(" ", "");
        if (g != "" && !goalNom.contains(g))
        {
            Goal *go = new Goal;
            go->nom = g;
            go->etat = "Non trouvé";

            goalNom[g] = go;
            communautes[nameCommu]->goalsInexistants.append(go);
            communautes[nameCommu]->goalsInexistantsMap[g] = go;
        }
        if (communautes[nameCommu]->goalsInexistantsMap.contains(g))
        {
            goalsP++;
        }
        if (goalNom.contains(g))
        {
            addDomaineGoal(d, goalNom[g], MODIFICATEURS_GOAL);
            communautes[nameCommu]->domainesGoalModificateurs[g].push_back(d);
            communautes[nameCommu]->domainesGoal[g].push_back(d);
            communautes[nameCommu]->goals[g] = goalNom[g];
        }
    }

    for (int i = 0; i < GOALsLecteurs.size(); i++)
    {
        QString g = GOALsLecteurs[i].replace(" ", "");
        if (g != "" && !goalNom.contains(g))
        {
            Goal *go = new Goal;
            go->nom = g;
            go->etat = "Non trouvé";

            goalNom[g] = go;
            communautes[nameCommu]->goalsInexistants.append(go);
            communautes[nameCommu]->goalsInexistantsMap[g] = go;
        }
        if (communautes[nameCommu]->goalsInexistantsMap.contains(g))
        {
            goalsP++;
        }
        if (goalNom.contains(g))
        {
            addDomaineGoal(d, goalNom[g], LECTEURS_GOAL);
            communautes[nameCommu]->domainesGoalLecteurs[g].push_back(d);
            communautes[nameCommu]->goals[g] = goalNom[g];
            if (GOALsmodificateurs.contains(g))
                communautes[nameCommu]->domainesDoublon.push_back(d);
            else
                communautes[nameCommu]->domainesGoal[g].push_back(d);
        }
    }


    for (int i = 0; i < GOALsGestionnaires.size(); i++)
    {
        QString g = GOALsGestionnaires[i].replace(" ", "");
        if (g != "" && !goalNom.contains(g))
        {
            Goal *go = new Goal;
            go->nom = g;
            go->etat = "Non trouvé";

            goalNom[g] = go;
            communautes[nameCommu]->goalsInexistants.append(go);
            communautes[nameCommu]->goalsInexistantsMap[g] = go;
        }
        if (communautes[nameCommu]->goalsInexistantsMap.contains(g))
        {
            goalsP++;
        }
        if (goalNom.contains(g))
        {
            //addDomaineGoal(d, goalNom[g], LECTEURS_GOAL);
            communautes[nameCommu]->domainesGoalGestionnaires[g].push_back(d);
            communautes[nameCommu]->goals[g] = goalNom[g];
        }
    }

    if (goalsP > 2)
        d->problem = true;

    for (int i = 0; i < gestionnaires.size(); i++)
        if (addDomaineUser(d, gestionnaires[i], GESTIONNAIRES) == 2)
            d->problem = true;

    for (int i = 0; i < modificateurs.size(); i++)
        addDomaineUser(d, modificateurs[i], MODIFICATEURS);

    for (int i = 0; i < lecteurs.size(); i++)
        addDomaineUser(d, lecteurs[i], LECTEURS);


    domainesV.push_back(d);
    dataD.unlock();
}

void Data::addDocument(QString name, QString idDomaine, QString version, QString proprietaire, QString id, QString dateCreation, QString dateModif, QString nbPj, QString namePj, int nbConsult, QString confidentialite, QString Statut)
{
    if (domaines.contains(idDomaine.toInt()))
    {
        if (id.isEmpty())
        {
            //qDebug() << "id";
            return;
        }
        if (version.isEmpty())
        {
            qDebug() << "version";
            return;
        }
        if (name.isEmpty())
        {
            qDebug() << "name";
            return;
        }
        if (proprietaire.isEmpty())
        {
            qDebug() << "proprio";
            return;
        }
        if(domaines[idDomaine.toInt()]->commu->documents.contains(id))
        {
            domaines[idDomaine.toInt()]->commu->documents[id]->nbConsult += nbConsult;
            return;
        }
        dataD.lock();
        Document *d = new Document;

        d->nom = name;
        d->nbConsult = nbConsult;
        d->domaine = domaines[idDomaine.toInt()];
        d->version = version;
        d->dateCreation = QDate::fromString(dateCreation, "dd/MM/yyyy");
        d->dateModif = QDate::fromString(dateModif, "dd/MM/yyyy");
        d->nombresPJ = nbPj.toInt();
        if (!namePj.isEmpty())
            d->nombresPJ++;
        if (d->nombresPJ == 0)
        {
            d->domaine->commu->documentsVide.push_back(d);
        }
        if (d->nombresPJ > 50)
        {
            d->domaine->commu->documentsSurcharge.push_back(d);
        }

        if (Statut == "publiée")
            d->domaine->commu->documentsPublie.append(d);
        else if (Statut == "de travail")
        {
            d->domaine->commu->documentsEnTravail.append(d);
            if (d->dateModif.addMonths(6) > QDate::currentDate())
                d->domaine->commu->t6mois++;
        }
        d->domaine->commu->documents[id] = d;

        QString pro = proprietaire.split(" - ")[1];
        pro.remove(" ");
        if (confidentialite.contains("Aucune confidentialité"))
            domaines[idDomaine.toInt()]->commu->documentsConfidentialitees[0].push_back(d);
        else if (confidentialite.contains("C=1"))
            domaines[idDomaine.toInt()]->commu->documentsConfidentialitees[1].push_back(d);
        else if (confidentialite.contains("C=2"))
        {
            domaines[idDomaine.toInt()]->commu->documentsConfidentialitees[2].push_back(d);
            if (d->nombresPJ > 50)
                d->domaine->commu->c2t++;
        }
        else if (confidentialite.contains("C=3"))
        {
            domaines[idDomaine.toInt()]->commu->documentsConfidentialitees[3].push_back(d);
            if (d->nombresPJ > 50)
                d->domaine->commu->c3t++;
        }
        else if (confidentialite.contains("C=4"))
            domaines[idDomaine.toInt()]->commu->documentsConfidentialitees[4].push_back(d);

        if (domaines[idDomaine.toInt()]->commu->users.contains(pro))
            d->proprietaire = domaines[idDomaine.toInt()]->commu->users[pro];
        else
        {
            if (!userId.contains(pro))
            {
                userId[pro] = new User;
                userId[pro]->nom = proprietaire.split(" - ")[0];
                userId[pro]->prenom = "(Hors annuaire PSA)";
                userId[pro]->ID = pro;
                userId[pro]->psa = false;

                //d->domaine->commu->usersNonTrouve.push_back(userId[pro]);
            }
            UserCommu *uC = new UserCommu;
            uC->user = userId[pro];

            domaines[idDomaine.toInt()]->commu->users[pro] = uC;


            d->proprietaire = domaines[idDomaine.toInt()]->commu->users[pro];

            if (userId[pro]->psa == false)
                domaines[idDomaine.toInt()]->commu->usersNonTrouve.push_back(uC);
            else
                domaines[idDomaine.toInt()]->commu->usersInconnu.push_back(uC);
        }
        domaines[idDomaine.toInt()]->commu->users[pro]->documentsResponsable.push_back(d);
        domaines[idDomaine.toInt()]->commu->users[pro]->domainesavecdocPro.push_back(domaines[idDomaine.toInt()]);
        d->domaine->commu->usersProprietaire[pro] = d->domaine->commu->users[pro];
        d->id = id;
        domaines[idDomaine.toInt()]->documents.append(d);
        dataD.unlock();
    }
     //qDebug() << "domaines";
}

void Data::generateData()
{
    foreach (QString key, communautes.keys())
    {
        foreach(QString name, communautes[key]->goals.keys())
        {
            if (communautes[key]->goals[name]->users.size() == 0 && !communautes[key]->goals[name]->ID.isEmpty())
                communautes[key]->goalsVides.append(communautes[key]->goals[name]);
            if (communautes[key]->goals[name]->etat != "OPERATIONNEL")
            {
                communautes[key]->goalsInexistants.append(communautes[key]->goals[name]);
                for (int i = 0; i < communautes[key]->domainesGoal[name].size(); i++)
                    communautes[key]->domainesInexistantMap[name][communautes[key]->domainesGoal[name][i]->id] = communautes[key]->domainesGoal[name][i];
            }
        }
        foreach(QString name, communautes[key]->domainesKey.keys())
        {
            if (communautes[key]->domainesKey[name]->documents.size() == 0 && communautes[key]->domainesKey[name]->enfants.size() == 0)
            {
                communautes[key]->domainesVides.append(communautes[key]->domainesKey[name]);
            }else if (communautes[key]->domainesKey[name]->documents.size() > 10)
                communautes[key]->domainesPlein.append(communautes[key]->domainesKey[name]);
        }
    }
}

void Data::generateTree()
{
    //qDebug() << domainesV.size();
    for (int key = 0; key < domainesV.size(); key++)
    {
       // qDebug() << domainesV[key]->nom <<  domainesV[key]->id;
        TreeItem *t = new TreeItem(domainesV[key]->nom, domainesV[key]->id, domainesV[key]->problem);
        domainesV[key]->t = t;
        //t->setIsOpen(true);
        if (domainesV[key]->id_parent != 0)
        {
            //if (domaines.contains(domainesV[key]->id_parent))
            //{
                //qDebug() << "add chlid debut";
                domainesV[key]->parent->t->addChildItem(t);
                //qDebug() << "add child fin";
            //}
           // else
            //{
                //qDebug() << "problem parent";
           //}
        }
        else
        {
            treeMo->setRoot(t);
            c_actu = domainesV[key]->commu;
        }
    }
}

void Data::drawTree(QString goal, bool modif, bool lecteur, bool gestionnaire)
{
    for (int key = 0; key < domainesV.size(); key++)
    {
        domainesV[key]->t->setIsOpen(false);
        domainesV[key]->t->setIsSelect(false);
    }
    if (goal.isEmpty())
        return;/*
    if (gestionnaire == true)
    {
        for(int i = 0; i < c_actu->domainesGoalGestionnaires[goal].size(); i++)
        {
            c_actu->domainesGoalGestionnaires[goal][i]->t->setIsSelect(true);
            if (c_actu->domainesGoalGestionnaires[goal][i]->id_parent != 0)
                recursiveOpen(c_actu->domainesGoalGestionnaires[goal][i]->id_parent);
        }
    }
    if (modif == true && lecteur == true)
    {*/

    for(int i = 0; i < c_actu->domainesGoalModificateurs[goal].size(); i++)
    {
        c_actu->domainesGoalModificateurs[goal][i]->t->setColor("blue");
        c_actu->domainesGoalModificateurs[goal][i]->t->setIsSelect(true);

        if (c_actu->domainesGoalModificateurs[goal][i]->id_parent != 0)
            recursiveOpen(c_actu->domainesGoalModificateurs[goal][i]->id_parent);
    }

    for(int i = 0; i < c_actu->domainesGoalLecteurs[goal].size(); i++)
    {
        if (c_actu->domainesGoalLecteurs[goal][i]->t->isSelect() == true)
            c_actu->domainesGoalLecteurs[goal][i]->t->setColor("red");
        else
            c_actu->domainesGoalLecteurs[goal][i]->t->setColor("green");

        c_actu->domainesGoalLecteurs[goal][i]->t->setIsSelect(true);
        if (c_actu->domainesGoalLecteurs[goal][i]->id_parent != 0)
            recursiveOpen(c_actu->domainesGoalLecteurs[goal][i]->id_parent);
    }

/*
    for(int i = 0; i < c_actu->domainesGoal[goal].size(); i++)
    {
        c_actu->domainesGoal[goal][i]->t->setIsSelect(true);
        if (c_actu->domainesGoal[goal][i]->id_parent != 0)
            recursiveOpen(c_actu->domainesGoal[goal][i]->id_parent);
    }*/


        /*
    }
    else if (modif == true && lecteur == false)
    {
        for(int i = 0; i < c_actu->domainesGoalModificateurs[goal].size(); i++)
        {
            c_actu->domainesGoalModificateurs[goal][i]->t->setIsSelect(true);
            if (c_actu->domainesGoalModificateurs[goal][i]->id_parent != 0)
                recursiveOpen(c_actu->domainesGoalModificateurs[goal][i]->id_parent);
        }
    }
    else
    {
        for(int i = 0; i < c_actu->domainesGoalLecteurs[goal].size(); i++)
        {
            c_actu->domainesGoalLecteurs[goal][i]->t->setIsSelect(true);
            if (c_actu->domainesGoalLecteurs[goal][i]->id_parent != 0)
                recursiveOpen(c_actu->domainesGoalLecteurs[goal][i]->id_parent);
        }
    }*/
    treeMo->refreshTree();
}

void Data::drawTree(QString domaine)
{
    for (int key = 0; key < domainesV.size(); key++)
    {
        domainesV[key]->t->setIsOpen(false);
        domainesV[key]->t->setIsSelect(false);
    }
    if (domaine.isEmpty())
        return;
    if (c_actu->domainesKey.contains(domaine))
    {
        c_actu->domainesKey[domaine]->t->setColor("#FFC53C");
        c_actu->domainesKey[domaine]->t->setIsSelect(true);
        if (c_actu->domainesKey[domaine]->id_parent != 0)
            recursiveOpen(c_actu->domainesKey[domaine]->id_parent);
    }
}


void Data::drawTreeUserId(QString user, int type)
{
    for (int key = 0; key < domainesV.size(); key++)
    {
        domainesV[key]->t->setIsOpen(false);
        domainesV[key]->t->setIsSelect(false);
    }
    if (user.isEmpty())
        return;
    if (!c_actu->users.contains(user))
        return;
    if (type == 0)
    {
        for (int i = 0; i < c_actu->users[user]->domainesResponsable.size(); i++)
        {
            c_actu->users[user]->domainesResponsable[i]->t->setColor("#FFC53C");
            c_actu->users[user]->domainesResponsable[i]->t->setIsSelect(true);
            if (c_actu->users[user]->domainesResponsable[i]->id_parent != 0)
                recursiveOpen(c_actu->users[user]->domainesResponsable[i]->id_parent);
        }
    }
    else if (type == 1)
    {
        for (int i = 0; i < c_actu->users[user]->domainesGestionnaire.size(); i++)
        {
            c_actu->users[user]->domainesGestionnaire[i]->t->setColor("#FFC53C");
            c_actu->users[user]->domainesGestionnaire[i]->t->setIsSelect(true);
            if (c_actu->users[user]->domainesGestionnaire[i]->id_parent != 0)
                recursiveOpen(c_actu->users[user]->domainesGestionnaire[i]->id_parent);
        }
    }
    else if (type == 2)
    {
        for (int i = 0; i < c_actu->users[user]->domainesavecdocPro.size(); i++)
        {
            c_actu->users[user]->domainesavecdocPro[i]->t->setColor("#FFC53C");
            c_actu->users[user]->domainesavecdocPro[i]->t->setIsSelect(true);
            if (c_actu->users[user]->domainesavecdocPro[i]->id_parent != 0)
                recursiveOpen(c_actu->users[user]->domainesavecdocPro[i]->id_parent);
        }
    }
}

void Data::recursiveOpen(int id)
{
    domaines[id]->t->setIsOpen(true);
    if (domaines[id]->id_parent != 0)
        recursiveOpen(domaines[id]->id_parent);
}


bool Data::getParentInexistant(Domaine *d, QString goal)
{
    if (c_actu->domainesInexistantMap[goal].contains(d->id_parent))
        return true;
    else if (d->parent == c_actu->root)
        return false;
    else
        return getParentInexistant(d->parent, goal);
}

QVector<int> Data::getDomaineGoalInexistant(QString goal)
{
    QVector<int> data;
    QVector<int> data2;
    QVector<int> data3;
    QVector<int> data4;

    foreach (int id, c_actu->domainesInexistantMap[goal].keys()) {
        data.append(id);
    }

    for (int i = 0; i < data.size(); i++)
    {
        bool t = false;
        if (data2.contains(c_actu->domainesKey[QString::number(data[i])]->id_parent))
        {
            t = true;
        }
        else
        {
            for (int e = 0; e < data.size(); e++)
            {
                if (i != e)
                {
                    if (c_actu->domainesKey[QString::number(data[i])]->id_parent == c_actu->domainesKey[QString::number(data[e])]->id_parent)
                    {
                        data2.append(c_actu->domainesKey[QString::number(data[i])]->id_parent);
                        t = true;
                    }
                }
            }
        }
        if (t == false)
            data2.append(data[i]);
    }


    for (int i = 0; i < data2.size(); i++)
    {
        if (getParentInexistant(c_actu->domainesKey[QString::number(data2[i])], goal) == false)
        {
            if (!data3.contains(data2[i]))
                data3.push_back(data2[i]);
        }
    }

    return data3;
}

void Data::setCurrentCommu(QString name)
{
    if (!communautes.contains(name))
    {
        qDebug() << "PROBLEM";
        return;
    }
    c_actu = communautes[name];
    commuChanged();
    qDebug() << "Data : " << c_actu->root->nom;
    treeMo->setRoot(c_actu->root->t);
}

void Data::getInfo()
{
    qDebug() << communautes.size();
    qDebug() << userId.size();
    qDebug() << goalId.size();
    qDebug() << domaines.size();
    foreach (QString name, communautes.keys()) {
        qDebug() << communautes[name]->name;
    }
}
