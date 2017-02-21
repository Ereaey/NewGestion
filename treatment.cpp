#include "treatment.h"
#include <QDebug>

Treatment::Treatment(Data *d)
{
    m_data = d;
    m_finish = false;
    m_type = SEARCH_GOAL;
    m_goal = "";
    m_domaine = "";
    m_descriptionResult = new DataDomaine("", "");
}

void Treatment::load()
{
    foreach (QString key, m_data->getCommus().keys()) {
        m_commu.append(new DataCommu(key, 0));
        setCommu(key);
        qDebug() << key;
    }
    emit refreshCommu();
}

void Treatment::searchUser(QString name, int type)
{
    m_currentAction = "Rechercher un utilisateur > " + name;
    emit currentActionChanged();
    m_user = name;
    m_type = SEARCH_USER;
    m_typeUser = type;
    start();
}

void Treatment::searchUserId(QString name, int type)
{
    m_currentAction = "Rechercher un utilisateur > " + name;
    emit currentActionChanged();
    m_user = name;
    m_type = SEARCH_USER_ID;
    m_typeUser = type;
    start();
}

void Treatment::searchDocumentVide()
{
    m_currentAction = "Rechercher des documents vides";
    emit currentActionChanged();
    m_type = SEARCH_DOCUMENT_VIDE;
    start();
}

void Treatment::searchDocument(QString name)
{
    m_currentAction = "Rechercher des documents > " + name;
    emit currentActionChanged();
    m_type = SEARCH_DOCUMENT;
    m_document = name;
    start();

}

void Treatment::searchDocumentSurchage()
{
    m_currentAction = "Rechercher des documents avec plus de 50 documents";
    emit currentActionChanged();
    m_type = SEARCH_DOCUMENT_SURCHARGE;
    start();
}

void Treatment::searchUserHorsPSA()
{
    m_currentAction = "Rechercher des utilisateurs absent de l'annuaire PSA";
    emit currentActionChanged();
    m_type = SEARCH_USER_HORS_PSA;
    start();
}

void Treatment::searchGoal(QString goal, bool modificateur, bool lecteur, bool gestionnaire)
{
    m_goal = goal;
    m_currentAction = "Rechercher un goal > " + goal;
    if (gestionnaire == true)
    {
        m_type = SEARCH_GOAL_GEST;
        m_currentAction += " (G)";
    }
    else if (modificateur == true && lecteur == false)
    {
        m_type = SEARCH_GOAL_MODIF;
        m_currentAction += " (M)";
    }
    else if (modificateur == false && lecteur == true)
    {
        m_type = SEARCH_GOAL_LECT;
        m_currentAction += " (L)";
    }
    else if (modificateur == true && lecteur == true)
    {
        m_type = SEARCH_GOAL;
        m_currentAction += " (M/L)";
    }
    else
    {
        m_type = SEARCH_GOAL;
        m_currentAction = "Rechercher un goal";
        m_goal = "";
    }
    emit currentActionChanged();

    start();
}

void Treatment::noteGlobale()
{
    m_currentAction = "Note Globale";
    emit currentActionChanged();
    m_type = NOTE_GLOBALE;
    start();
}

void Treatment::searchGoalsVide()
{
    m_currentAction = "Rechercher un goal vide";
    emit currentActionChanged();
    m_type = SEARCH_GOAL_VIDE;
    start();
}

void Treatment::searchGoalDoublon()
{
    m_currentAction = "Rechercher les goals doublons";
    emit currentActionChanged();
    m_type = SEARCH_GOAL_DOUBLON;
    start();
}

void Treatment::searchUserDoublon(bool resp)
{
    m_currentAction = "Rechercher les utilisateurs doublons";
    emit currentActionChanged();
    m_type = SEARCH_USER_DOUBLON;
    m_typeUser = resp;
    start();
}

void Treatment::searchUserPerime(bool resp)
{
    m_currentAction = "Rechercher les utilisateurs perimés";
    emit currentActionChanged();
    m_type = SEARCH_USER_PERIME;
    m_typeUser = resp;
    start();
}

void Treatment::searchGoalsProbleme()
{
    m_currentAction = "Rechercher un goal inexistants / périmés";
    emit currentActionChanged();
    m_type = SEARCH_GOAL_PROBLEME;
    start();
}

void Treatment::searchDomaine(QString name)
{
    m_currentAction = "Rechercher un domaine > " + name;
    m_domaine = name;
    emit currentActionChanged();
    m_type = SEARCH_DOMAINE;
    start();
}

void Treatment::searchDomaineVide()
{
    m_currentAction = "Rechercher des domaines vides";
    //m_domaine = name;
    emit currentActionChanged();
    m_type = SEARCH_DOMAINE_VIDE;
    start();
}

void Treatment::searchUserAbsent()
{
    m_currentAction = "Rechercher des utilisateurs absent";
    //m_domaine = name;
    emit currentActionChanged();
    m_type = SEARCH_USER_ABSENT;
    start();
}

void Treatment::searchDomaineFull()
{
    m_currentAction = "Rechercher des domaines surchargés";
    //m_domaine = name;
    emit currentActionChanged();
    m_type = SEARCH_DOMAINE_FULL;
    start();
}

bool Treatment::finish() const
{
    return m_finish;
}

void Treatment::setCommu(QString name)
{
    m_currentCommu = name;
    m_data->setCurrentCommu(name);
    emit commuChanged();
    //start();
}

void Treatment::exportPlan(QString idDomaine, QString path)
{
    path.remove("file:///");
    path.remove("file:\\\/");

    m_currentAction = "Exportation du plan";
    m_domaine = idDomaine;
    m_path = path;
    emit currentActionChanged();
    m_type = EXPORT_PLAN;
    start();
}

QString Treatment::generatePlan(QString idDomaine)
{
    QString d;
    qDebug() << idDomaine;
    d += "[\"" + QString::number(m_data->getCurrentCommu()->domainesKey[idDomaine]->id) + "\", \""
            + m_data->getCurrentCommu()->domainesKey[idDomaine]->nom + "\", \""
            + QString::number(m_data->getCurrentCommu()->domainesKey[idDomaine]->enfants.size()) + "\", \""
            + QString::number(m_data->getCurrentCommu()->domainesKey[idDomaine]->documents.size()) + "\", \""
            + QString::number(m_data->getCurrentCommu()->domainesKey[idDomaine]->id_parent) + "\", \""
            + m_data->getCurrentCommu()->domainesKey[idDomaine]->responsable->user->nom + " " + m_data->getCurrentCommu()->domainesKey[idDomaine]->responsable->user->prenom
            + "\"]";
    m_file1 += QString::number(m_data->getCurrentCommu()->domainesKey[idDomaine]->id) + ";"
            + m_data->getCurrentCommu()->domainesKey[idDomaine]->nom + ";"
            + QString::number(m_data->getCurrentCommu()->domainesKey[idDomaine]->enfants.size()) + ";"
            + QString::number(m_data->getCurrentCommu()->domainesKey[idDomaine]->documents.size()) + ";"
            + QString::number(m_data->getCurrentCommu()->domainesKey[idDomaine]->id_parent) + ";"
            + m_data->getCurrentCommu()->domainesKey[idDomaine]->responsable->user->nom + " " + m_data->getCurrentCommu()->domainesKey[idDomaine]->responsable->user->prenom
            + QString(QChar('\n'));
    for (int i = 0; i < m_data->getCurrentCommu()->domainesKey[idDomaine]->enfants.size(); i++)
    {
         d += "," + generatePlan(QString::number(m_data->getCurrentCommu()->domainesKey[idDomaine]->enfants[i]->id));
    }
    qDebug() << "Documents";
    for (int i = 0; i < m_data->getCurrentCommu()->domainesKey[idDomaine]->documents.size(); i++)
    {
         m_dataDocument += ", [\"" + m_data->getCurrentCommu()->domainesKey[idDomaine]->documents[i]->id + "\", \""
                 + m_data->getCurrentCommu()->domainesKey[idDomaine]->documents[i]->nom + "\", \""
                 + m_data->getCurrentCommu()->domainesKey[idDomaine]->documents[i]->version + "\", \""
                 + m_data->getCurrentCommu()->domainesKey[idDomaine]->documents[i]->domaine->nom + "\", \""
                 + m_data->getCurrentCommu()->domainesKey[idDomaine]->documents[i]->proprietaire->user->nom + " " + m_data->getCurrentCommu()->domainesKey[idDomaine]->documents[i]->proprietaire->user->prenom + "\", \""
                 + m_data->getCurrentCommu()->domainesKey[idDomaine]->documents[i]->dateCreation.toString("dd/MM/yyyy") + "\", \""
                 + m_data->getCurrentCommu()->domainesKey[idDomaine]->documents[i]->dateModif.toString("dd/MM/yyyy") + "\", \""
                 + QString::number(m_data->getCurrentCommu()->domainesKey[idDomaine]->documents[i]->nombresPJ) + "\", \""
                 + QString::number(m_data->getCurrentCommu()->domainesKey[idDomaine]->documents[i]->nbConsult) + "\", \""
                 + idDomaine
                 + "\"]";
         m_file2 += m_data->getCurrentCommu()->domainesKey[idDomaine]->documents[i]->id + ";"
                 + m_data->getCurrentCommu()->domainesKey[idDomaine]->documents[i]->nom + ";"
                 + m_data->getCurrentCommu()->domainesKey[idDomaine]->documents[i]->version + ";"
                 + m_data->getCurrentCommu()->domainesKey[idDomaine]->documents[i]->domaine->nom + ";"
                 + m_data->getCurrentCommu()->domainesKey[idDomaine]->documents[i]->proprietaire->user->nom + " " + m_data->getCurrentCommu()->domainesKey[idDomaine]->documents[i]->proprietaire->user->prenom + ";"
                 + m_data->getCurrentCommu()->domainesKey[idDomaine]->documents[i]->dateCreation.toString("dd/MM/yyyy") + ";"
                 + m_data->getCurrentCommu()->domainesKey[idDomaine]->documents[i]->dateModif.toString("dd/MM/yyyy") + ";"
                 + QString::number(m_data->getCurrentCommu()->domainesKey[idDomaine]->documents[i]->nombresPJ)+ ";"
                 + QString::number(m_data->getCurrentCommu()->domainesKey[idDomaine]->documents[i]->nbConsult)
                 + QString(QChar('\n'));;
    }
    return d;
}


void Treatment::loadCara()
{
    emit commuChanged();
}

void Treatment::run()
{
    m_finish = false;
    emit finishChanged();
    if (m_type == SEARCH_GOAL)
    {
        m_data->drawTree(m_goal, true, true, false);
        for (int i = 0; i < m_commu.size(); i++)
        {
            ((DataCommu*)(m_commu[i]))->setResult(m_data->getCommus()[((DataCommu*)m_commu[i])->nom()]->domainesGoal[m_goal].size());
            if (m_goal.isEmpty())
                ((DataCommu*)(m_commu[i]))->setResult(0);
            qDebug() << QString::number(m_data->getCommus()[((DataCommu*)m_commu[i])->nom()]->domainesGoal[m_goal].size());
        }
    }
    else if (m_type == SEARCH_USER_ID)
    {
        /*
        m_data->drawTree(m_goal, true, true);
        */
        m_data->drawTreeUserId(m_user, m_typeUser);

        for (int i = 0; i < m_commu.size(); i++)
        {

            if (m_data->getCommus()[((DataCommu*)m_commu[i])->nom()]->users.contains(m_user))
            {
                if (m_typeUser == 0)
                {
                    ((DataCommu*)(m_commu[i]))->setResult(m_data->getCommus()[((DataCommu*)m_commu[i])->nom()]->users[m_user]->domainesResponsable.size());
                }
                else if (m_typeUser == 1)
                {
                    ((DataCommu*)(m_commu[i]))->setResult(m_data->getCommus()[((DataCommu*)m_commu[i])->nom()]->users[m_user]->domainesModificateur.size());
                }
                else if (m_typeUser == 2)
                {
                    ((DataCommu*)(m_commu[i]))->setResult(m_data->getCommus()[((DataCommu*)m_commu[i])->nom()]->users[m_user]->domainesGestionnaire.size());
                }
                else if (m_typeUser == 3)
                {
                    ((DataCommu*)(m_commu[i]))->setResult(m_data->getCommus()[((DataCommu*)m_commu[i])->nom()]->users[m_user]->domainesLecteur.size());
                }
            }
            else
                ((DataCommu*)(m_commu[i]))->setResult(0);
            if (m_user.isEmpty())
                ((DataCommu*)(m_commu[i]))->setResult(0);

            //qDebug() << QString::number(m_data->getCommus()[((DataCommu*)m_commu[i])->nom()]->domainesGoal[m_goal].size());
        }



    }
    else if (m_type == SEARCH_GOAL_MODIF)
    {
        m_data->drawTree(m_goal, true, false, false);
        for (int i = 0; i < m_commu.size(); i++)
        {
            ((DataCommu*)(m_commu[i]))->setResult(m_data->getCommus()[((DataCommu*)m_commu[i])->nom()]->domainesGoalModificateurs[m_goal].size());
            if (m_goal.isEmpty())
                ((DataCommu*)(m_commu[i]))->setResult(0);
        }
    }
    else if (m_type == SEARCH_GOAL_GEST)
    {
        m_data->drawTree(m_goal, false, false, true);
        for (int i = 0; i < m_commu.size(); i++)
        {
            ((DataCommu*)(m_commu[i]))->setResult(m_data->getCommus()[((DataCommu*)m_commu[i])->nom()]->domainesGoalGestionnaires[m_goal].size());
            if (m_goal.isEmpty())
                ((DataCommu*)(m_commu[i]))->setResult(0);
        }
    }
    else if (m_type == SEARCH_GOAL_LECT)
    {
        m_data->drawTree(m_goal, false, true, false);
        for (int i = 0; i < m_commu.size(); i++)
        {
            ((DataCommu*)(m_commu[i]))->setResult(m_data->getCommus()[((DataCommu*)m_commu[i])->nom()]->domainesGoalLecteurs[m_goal].size());
            if (m_goal.isEmpty())
                ((DataCommu*)(m_commu[i]))->setResult(0);
        }
    }
    else if (m_type == SEARCH_GOAL_VIDE)
    {
        m_result.clear();
        for (int i = 0; i < m_commu.size(); i++)
        {
            ((DataCommu*)(m_commu[i]))->setResult(m_data->getCommus()[((DataCommu*)m_commu[i])->nom()]->goalsVides.size());
        }
        for (int i = 0; i < m_data->getCurrentCommu()->goalsVides.size(); i++)
        {
            m_result.append(new DataGoal(m_data->getCurrentCommu()->goalsVides[i]->nom, m_data->getCurrentCommu()->goalsVides[i]->ID));
        }
        emit refreshResult();
    }
    else if (m_type == SEARCH_DOMAINE)
    {
        m_data->drawTree(m_domaine);
        for (int i = 0; i < m_commu.size(); i++)
        {
            if (m_data->getCommus()[((DataCommu*)m_commu[i])->nom()]->domainesKey.contains(m_domaine))
            {
                ((DataCommu*)(m_commu[i]))->setResult(1);
                setCommu(((DataCommu*)m_commu[i])->nom());
                m_data->drawTree(m_domaine);
                Domaine *g = m_data->getCommus()[((DataCommu*)m_commu[i])->nom()]->domainesKey[m_domaine];
                DataDomaine *d = new DataDomaine(g->nom, QString::number(g->id), g->responsable->user->nom + " " + g->responsable->user->prenom);
                m_descriptionResult = d;
            }
            else
                ((DataCommu*)(m_commu[i]))->setResult(0);
        }
        emit refreshDescriptionResult();
        emit refreshResult();
    }
    else if (m_type == SEARCH_DOMAINE_VIDE)
    {
        m_result.clear();
        for (int i = 0; i < m_commu.size(); i++)
        {
            ((DataCommu*)(m_commu[i]))->setResult(m_data->getCommus()[((DataCommu*)m_commu[i])->nom()]->domainesVides.size());
        }
        for (int i = 0; i < m_data->getCurrentCommu()->domainesVides.size(); i++)
        {
            m_result.append(new DataDomaine(m_data->getCurrentCommu()->domainesVides[i]->nom, QString::number(m_data->getCurrentCommu()->domainesVides[i]->id)));
        }
        emit refreshResult();
    }
    else if (m_type == SEARCH_GOAL_DOUBLON)
    {
        m_result.clear();
        for (int i = 0; i < m_commu.size(); i++)
        {
            ((DataCommu*)(m_commu[i]))->setResult(m_data->getCommus()[((DataCommu*)m_commu[i])->nom()]->domainesDoublon.size());
        }
        for (int i = 0; i < m_data->getCurrentCommu()->domainesDoublon.size(); i++)
        {
            m_result.append(new DataDomaine(m_data->getCurrentCommu()->domainesDoublon[i]->nom, QString::number(m_data->getCurrentCommu()->domainesDoublon[i]->id)));
        }
        emit refreshResult();
    }
    else if (m_type == SEARCH_DOMAINE_FULL)
    {
        m_result.clear();
        for (int i = 0; i < m_commu.size(); i++)
        {
            ((DataCommu*)(m_commu[i]))->setResult(m_data->getCommus()[((DataCommu*)m_commu[i])->nom()]->domainesPlein.size());
        }
        for (int i = 0; i < m_data->getCurrentCommu()->domainesPlein.size(); i++)
        {
            m_result.append(new DataDomaine(m_data->getCurrentCommu()->domainesPlein[i]->nom, QString::number(m_data->getCurrentCommu()->domainesPlein[i]->id)));
        }
        emit refreshResult();
    }
    else if (m_type == SEARCH_GOAL_PROBLEME)
    {
        m_result.clear();
        for (int i = 0; i < m_commu.size(); i++)
        {
            ((DataCommu*)(m_commu[i]))->setResult(m_data->getCommus()[((DataCommu*)m_commu[i])->nom()]->goalsInexistants.size());
        }
        for (int i = 0; i < m_data->getCurrentCommu()->goalsInexistants.size(); i++)
        {
            QString d;
            QVector<int> data = m_data->getDomaineGoalInexistant(m_data->getCurrentCommu()->goalsInexistants[i]->nom);

            /*if (m_data->getParentInexistant(m_data->getCurrentCommu()->domainesGoal[m_data->getCurrentCommu()->goalsInexistants[i]->nom][e], m_data->getCurrentCommu()->goalsInexistants[i]->nom) == false)
            {
                qDebug() << "A" << QString::number(m_data->getCurrentCommu()->domainesGoal[m_data->getCurrentCommu()->goalsInexistants[i]->nom][e]->id);
                d.append(" - " + QString::number(m_data->getCurrentCommu()->domainesGoal[m_data->getCurrentCommu()->goalsInexistants[i]->nom][e]->id));
            }*/
            for (int g = 0; g < data.size(); g++)
            {
                d.append(" - " + QString::number(data[g]));
            }
            qDebug() << "Nb Do" <<  QString::number(m_data->getCurrentCommu()->domainesGoal[m_data->getCurrentCommu()->goalsInexistants[i]->nom].size());
            m_result.append(new DataGoal(m_data->getCurrentCommu()->goalsInexistants[i]->nom, m_data->getCurrentCommu()->goalsInexistants[i]->ID + d, m_data->getCurrentCommu()->goalsInexistants[i]->etat));

        }
        emit refreshResult();
    }
    else if (m_type == SEARCH_DOCUMENT_VIDE)
    {
        m_result.clear();
        for (int i = 0; i < m_commu.size(); i++)
        {
            ((DataCommu*)(m_commu[i]))->setResult(m_data->getCommus()[((DataCommu*)m_commu[i])->nom()]->documentsVide.size());
        }
        for (int i = 0; i < m_data->getCurrentCommu()->documentsVide.size(); i++)
        {
            m_result.append(new DataDocument(m_data->getCurrentCommu()->documentsVide[i]->nom, m_data->getCurrentCommu()->documentsVide[i]->id, m_data->getCurrentCommu()->documentsVide[i]->domaine->id));
        }
        emit refreshResult();
    }
    else if (m_type == SEARCH_DOCUMENT_SURCHARGE)
    {
        m_result.clear();
        for (int i = 0; i < m_commu.size(); i++)
        {
            ((DataCommu*)(m_commu[i]))->setResult(m_data->getCommus()[((DataCommu*)m_commu[i])->nom()]->documentsSurcharge.size());
        }
        for (int i = 0; i < m_data->getCurrentCommu()->documentsSurcharge.size(); i++)
        {
            m_result.append(new DataDocument(m_data->getCurrentCommu()->documentsSurcharge[i]->nom, m_data->getCurrentCommu()->documentsSurcharge[i]->id, m_data->getCurrentCommu()->documentsSurcharge[i]->domaine->id));
        }
        emit refreshResult();
    }
    else if (m_type == SEARCH_DOCUMENT)
    {
        m_result.clear();
        for (int i = 0; i < m_commu.size(); i++)
        {
            if (m_data->getCommus()[((DataCommu*)m_commu[i])->nom()]->documents.contains(m_document))
            {
                qDebug() << "salut";
                ((DataCommu*)(m_commu[i]))->setResult(1);
                setCommu(((DataCommu*)m_commu[i])->nom());
                m_result.append(new DataDocument(m_data->getCurrentCommu()->documents[m_document]->nom, m_data->getCurrentCommu()->documents[m_document]->id, m_data->getCurrentCommu()->documents[m_document]->domaine->id));

            }
            else
                ((DataCommu*)(m_commu[i]))->setResult(0);
        }

        emit refreshResult();
    }
    else if (m_type == NOTE_GLOBALE)
    {
        m_result.clear();
        for (int i = 0; i < m_commu.size(); i++)
        {
            ((DataCommu*)(m_commu[i]))->setResult(m_data->getCommus()[((DataCommu*)m_commu[i])->nom()]->note);
        }
        m_result.append(new DataNote(m_data));
        emit refreshResult();
    }
    else if (m_type == SEARCH_USER_ABSENT)
    {
        m_result.clear();
        for (int i = 0; i < m_commu.size(); i++)
        {
            ((DataCommu*)(m_commu[i]))->setResult(m_data->getCommus()[((DataCommu*)m_commu[i])->nom()]->usersInconnu.size());
        }

        for (int i = 0; i < m_data->getCurrentCommu()->usersInconnu.size(); i++)
        {
            m_result.append(new DataUser(m_data->getCurrentCommu()->usersInconnu[i]->user->nom + " " + m_data->getCurrentCommu()->usersInconnu[i]->user->prenom, m_data->getCurrentCommu()->usersInconnu[i]->user->ID));
        }
        emit refreshResult();
    }
    else if (m_type == SEARCH_USER_DOUBLON)
    {
        m_result.clear();
        if (m_typeUser == true)
        {
            for (int i = 0; i < m_commu.size(); i++)
            {
                ((DataCommu*)(m_commu[i]))->setResult(m_data->getCommus()[((DataCommu*)m_commu[i])->nom()]->domainesDoublonRG.size());
            }
            for (int i = 0; i < m_data->getCurrentCommu()->domainesDoublonRG.size(); i++)
            {
                m_result.append(new DataDomaine(m_data->getCurrentCommu()->domainesDoublonRG[i]->nom, QString::number(m_data->getCurrentCommu()->domainesDoublonRG[i]->id)));
            }
        }
        else
        {
            for (int i = 0; i < m_commu.size(); i++)
            {
                ((DataCommu*)(m_commu[i]))->setResult(m_data->getCommus()[((DataCommu*)m_commu[i])->nom()]->domainesDoublonML.size());
            }
            for (int i = 0; i < m_data->getCurrentCommu()->domainesDoublonML.size(); i++)
            {
                m_result.append(new DataDomaine(m_data->getCurrentCommu()->domainesDoublonML[i]->nom, QString::number(m_data->getCurrentCommu()->domainesDoublonML[i]->id)));
            }
        }
        emit refreshResult();
    }
    else if (m_type == SEARCH_USER_PERIME)
    {
        m_result.clear();
        if (m_typeUser == true)
        {
            for (int i = 0; i < m_commu.size(); i++)
            {
                ((DataCommu*)(m_commu[i]))->setResult(m_data->getCommus()[((DataCommu*)m_commu[i])->nom()]->domainesPerimeM.size());
            }
            for (int i = 0; i < m_data->getCurrentCommu()->domainesPerimeM.size(); i++)
            {
                m_result.append(new DataDomaine(m_data->getCurrentCommu()->domainesPerimeM[i]->user->user->nom + " " + m_data->getCurrentCommu()->domainesPerimeM[i]->user->user->prenom, QString::number(m_data->getCurrentCommu()->domainesPerimeM[i]->d->id)));
            }
        }
        else
        {
            for (int i = 0; i < m_commu.size(); i++)
            {
                ((DataCommu*)(m_commu[i]))->setResult(m_data->getCommus()[((DataCommu*)m_commu[i])->nom()]->domainesPerimeL.size());
            }
            for (int i = 0; i < m_data->getCurrentCommu()->domainesPerimeL.size(); i++)
            {
                m_result.append(new DataDomaine(m_data->getCurrentCommu()->domainesPerimeL[i]->user->user->nom + " " + m_data->getCurrentCommu()->domainesPerimeL[i]->user->user->prenom, QString::number(m_data->getCurrentCommu()->domainesPerimeL[i]->d->id)));
            }
        }
        emit refreshResult();
    }
    else if (m_type == SEARCH_USER_HORS_PSA)
    {
        m_result.clear();
        for (int i = 0; i < m_commu.size(); i++)
        {
            ((DataCommu*)(m_commu[i]))->setResult(m_data->getCommus()[((DataCommu*)m_commu[i])->nom()]->usersNonTrouve.size());
        }

        for (int i = 0; i < m_data->getCurrentCommu()->usersNonTrouve.size(); i++)
        {
            m_result.append(new DataUser(m_data->getCurrentCommu()->usersNonTrouve[i]->user->nom + " " + m_data->getCurrentCommu()->usersNonTrouve[i]->user->prenom, m_data->getCurrentCommu()->usersNonTrouve[i]->user->ID));
        }
        emit refreshResult();
    }
    else if (m_type == SEARCH_USER)
    {
        m_result.clear();
        if (m_typeUser == RESPONSABLE)
        {
            for (int i = 0; i < m_commu.size(); i++)
            {
                if (m_data->getCommus()[((DataCommu*)m_commu[i])->nom()]->users.contains(m_user))
                    ((DataCommu*)(m_commu[i]))->setResult(m_data->getCommus()[((DataCommu*)m_commu[i])->nom()]->users[m_user]->domainesResponsable.size());
                else
                    ((DataCommu*)(m_commu[i]))->setResult(0);
            }

            if (m_data->getCurrentCommu()->users.contains(m_user))
            {
                for (int i = 0; i < m_data->getCurrentCommu()->users[m_user]->domainesResponsable.size(); i++)
                {
                    m_result.append(new DataDomaine(m_data->getCurrentCommu()->users[m_user]->domainesResponsable[i]->nom, QString::number(m_data->getCurrentCommu()->users[m_user]->domainesResponsable[i]->id), m_data->getCurrentCommu()->users[m_user]->domainesResponsable[i]->responsable->user->nom));
                }
            }
        }
        else if (m_typeUser == GESTIONNAIRE)
        {
            for (int i = 0; i < m_commu.size(); i++)
            {
                if (m_data->getCommus()[((DataCommu*)m_commu[i])->nom()]->users.contains(m_user))
                    ((DataCommu*)(m_commu[i]))->setResult(m_data->getCommus()[((DataCommu*)m_commu[i])->nom()]->users[m_user]->domainesGestionnaire.size());
                else
                    ((DataCommu*)(m_commu[i]))->setResult(0);
            }

            if (m_data->getCurrentCommu()->users.contains(m_user))
            {
                for (int i = 0; i < m_data->getCurrentCommu()->users[m_user]->domainesGestionnaire.size(); i++)
                {
                    m_result.append(new DataDomaine(m_data->getCurrentCommu()->users[m_user]->domainesGestionnaire[i]->nom, QString::number(m_data->getCurrentCommu()->users[m_user]->domainesGestionnaire[i]->id), m_data->getCurrentCommu()->users[m_user]->domainesGestionnaire[i]->responsable->user->nom));
                }
            }
        }
        else if (m_typeUser == MODIFICATEUR)
        {
            for (int i = 0; i < m_commu.size(); i++)
            {
                int g = 0;
                if (m_data->getCommus()[((DataCommu*)m_commu[i])->nom()]->users.contains(m_user))
                {
                    g = m_data->getCommus()[((DataCommu*)m_commu[i])->nom()]->users[m_user]->domainesModificateur.size();
                    g += m_data->getCommus()[((DataCommu*)m_commu[i])->nom()]->users[m_user]->domainesModificateurGOAL.size();
                    ((DataCommu*)(m_commu[i]))->setResult(g);
                }
                else
                    ((DataCommu*)(m_commu[i]))->setResult(0);
            }

            if (m_data->getCurrentCommu()->users.contains(m_user))
            {
                for (int i = 0; i < m_data->getCurrentCommu()->users[m_user]->domainesModificateur.size(); i++)
                {
                    m_result.append(new DataDomaine(m_data->getCurrentCommu()->users[m_user]->domainesModificateur[i]->nom, QString::number(m_data->getCurrentCommu()->users[m_user]->domainesModificateur[i]->id), m_data->getCurrentCommu()->users[m_user]->domainesModificateur[i]->responsable->user->nom));
                }
                for (int i = 0; i < m_data->getCurrentCommu()->users[m_user]->domainesModificateurGOAL.size(); i++)
                {
                    qDebug() << m_data->getCurrentCommu()->users[m_user]->domainesModificateurGOAL[i]->nom;
                    m_result.append(new DataDomaine(m_data->getCurrentCommu()->users[m_user]->domainesModificateurGOAL[i]->nom, QString::number(m_data->getCurrentCommu()->users[m_user]->domainesModificateurGOAL[i]->id), m_data->getCurrentCommu()->users[m_user]->domainesModificateurGOAL[i]->responsable->user->nom));
                }
            }
        }
        else if (m_typeUser == LECTEUR)
        {
            for (int i = 0; i < m_commu.size(); i++)
            {
                int g = 0;
                if (m_data->getCommus()[((DataCommu*)m_commu[i])->nom()]->users.contains(m_user))
                {
                    g = m_data->getCommus()[((DataCommu*)m_commu[i])->nom()]->users[m_user]->domainesLecteur.size();
                    g += m_data->getCommus()[((DataCommu*)m_commu[i])->nom()]->users[m_user]->domainesLecteurGOAL.size();
                    ((DataCommu*)(m_commu[i]))->setResult(g);
                }
                else
                    ((DataCommu*)(m_commu[i]))->setResult(0);
            }

            if (m_data->getCurrentCommu()->users.contains(m_user))
            {
                for (int i = 0; i < m_data->getCurrentCommu()->users[m_user]->domainesLecteur.size(); i++)
                {
                    m_result.append(new DataDomaine(m_data->getCurrentCommu()->users[m_user]->domainesLecteur[i]->nom, QString::number(m_data->getCurrentCommu()->users[m_user]->domainesLecteur[i]->id), m_data->getCurrentCommu()->users[m_user]->domainesLecteur[i]->responsable->user->nom));
                }
                for (int i = 0; i < m_data->getCurrentCommu()->users[m_user]->domainesLecteurGOAL.size(); i++)
                {
                    m_result.append(new DataDomaine(m_data->getCurrentCommu()->users[m_user]->domainesLecteurGOAL[i]->nom, QString::number(m_data->getCurrentCommu()->users[m_user]->domainesLecteurGOAL[i]->id), m_data->getCurrentCommu()->users[m_user]->domainesLecteurGOAL[i]->responsable->user->nom));
                }
            }
        }
        emit refreshResult();
    }
    else if (m_type == EXPORT_PLAN)
    {
        QString data;
        m_file1 = "Identifiant du domaine;Domaine;Nombre de sous-domaines directs;Nombre de documents directs;Identifiant du domaine parent;Responsable" + QString(QChar('\n'));
        m_file2 = "Id;Titre;Version;Domaine;Proprietaire;Date de création;Date de dernière modification;Nombre de pièce jointe"+ QString(QChar('\n'));
        m_dataDocument = "var documents = [A";
        data = "var domaines = [" + generatePlan(m_domaine) + "];";
        data.replace(QString::number(m_data->getCurrentCommu()->domainesKey[m_domaine]->id_parent), "");
        //qDebug() << data;
        QFile file(":/index.html");
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
            return;
        qDebug() << "Open";
        QTextStream in(&file);
        QString de = in.readAll();
        de.replace("datadomaines", data);
        m_dataDocument += "];";
        m_dataDocument.remove("A,");
        de.replace("datadocuments", m_dataDocument);
        de.replace("xxxxxx", m_domaine);

        //qDebug() << de;
        QFile file2(m_path);
        if (!file2.open(QIODevice::WriteOnly | QIODevice::Text))
            return;
        qDebug() << "Enregistrement";
        QTextStream out(&file2);
        out << de;
        QString m_pattth = m_path;
        QFile file3(m_path.replace(".html", "2.csv"));
        if (!file3.open(QIODevice::WriteOnly | QIODevice::Text))
            return;
        qDebug() << "Enregistrement";
        QTextStream out1(&file3);
        out1 << m_file1;

        QFile file4(m_pattth.replace(".html", "3.csv"));
        if (!file4.open(QIODevice::WriteOnly | QIODevice::Text))
            return;
        qDebug() << "Enregistrement";
        QTextStream out2(&file4);
        out2 << m_file2;
        searchDomaine(m_domaine);
    }
    m_finish = true;
    emit finishChanged();
}
