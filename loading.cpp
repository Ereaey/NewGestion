#include "loading.h"
#include "qdebug.h"

Loading::Loading(Data *d, autoCompletGoal *g, QObject *parent) : QThread(parent)
{
    m_listDrives += QFileInfo("C:/fichiersGestion");
    m_data = d;
    m_ready = false;
    m_finish = false;
    qDebug() << "t";
    m_g = g;
}

void Loading::loadFiles()
{
    qDebug() << "e";
    QStringList t;
    t.append("externalID*.csv");
    t.append("internalID*.csv");
    t.append("Plans_de_communautes_*.csv");
    t.append("ssl_goal_pressi*.csv");
    t.append("ssl_membre_pressi*.csv");
    t.append("Audits_des_documents_*.csv");
    t.append("Liste_de_communautés_*.csv");
    qDebug() << "easy";
    QString file;
    foreach(const QFileInfo& FileInfo, m_listDrives)
    {
         QDirIterator it(FileInfo.filePath(), t, QDir::Files, QDirIterator::Subdirectories);
         while (it.hasNext())
         {
             qDebug() << "ok";
             file = it.next();
             if (file.contains("externalID"))
                if (m_pathMembersExternal.lastModified() < QFileInfo(file).lastModified())
                    m_pathMembersExternal = QFileInfo(file);

            if (file.contains("internalID"))
               if (m_pathMembersInternal.lastModified() < QFileInfo(file).lastModified())
                   m_pathMembersInternal = QFileInfo(file);

            if (file.contains("Plans_de_communautes_"))
              if (m_pathDomaines.lastModified() < QFileInfo(file).lastModified())
                  m_pathDomaines = QFileInfo(file);

            if (file.contains("Liste_de_communautés_"))
              if (m_pathCommu.lastModified() < QFileInfo(file).lastModified())
                  m_pathCommu = QFileInfo(file);

            if (file.contains("ssl_goal_pressi"))
             if (m_pathGoal.lastModified() < QFileInfo(file).lastModified())
                 m_pathGoal = QFileInfo(file);

             if (file.contains("ssl_membre_pressi"))
                if (m_pathGoalMembers.lastModified() < QFileInfo(file).lastModified())
                    m_pathGoalMembers = QFileInfo(file);

            if (file.contains("Audits_des_documents_"))
               if (m_pathDocuments.lastModified() < QFileInfo(file).lastModified())
                   m_pathDocuments = QFileInfo(file);
         }
    }

    m_pathDomainesCSV = new FileCSV(m_pathDomaines.absoluteFilePath(), 40, true);
    m_pathMembersInternalCSV = new FileCSV(m_pathMembersInternal.absoluteFilePath(), 24, true);
    m_pathMembersExternalCSV = new FileCSV(m_pathMembersExternal.absoluteFilePath(), 27, true);
    m_pathGoalCSV = new FileCSV(m_pathGoal.absoluteFilePath(), 66, false);
    m_pathDocumentsCSV = new FileCSV(m_pathDocuments.absoluteFilePath(), 51, true);
    m_pathCommuCSV = new FileCSV(m_pathCommu.absoluteFilePath(), 61, true);
    m_pathGoalMembersCSV = new FileCSV(m_pathGoalMembers.absoluteFilePath(), 3, true);

    connect(m_pathDomainesCSV, SIGNAL(dataLine(QStringList)), this, SLOT(loadDomaine(QStringList)), Qt::DirectConnection);
    connect(m_pathMembersInternalCSV, SIGNAL(dataLine(QStringList)), this, SLOT(loadMember(QStringList)), Qt::DirectConnection);
    connect(m_pathMembersExternalCSV, SIGNAL(dataLine(QStringList)), this, SLOT(loadMember(QStringList)), Qt::DirectConnection);
    connect(m_pathGoalCSV, SIGNAL(dataLine(QStringList)), this, SLOT(loadGoal(QStringList)), Qt::DirectConnection);
    connect(m_pathDocumentsCSV, SIGNAL(dataLine(QStringList)), this, SLOT(loadDocument(QStringList)), Qt::DirectConnection);
    connect(m_pathCommuCSV, SIGNAL(dataLine(QStringList)), this, SLOT(loadCommu(QStringList)), Qt::DirectConnection);
    connect(m_pathGoalMembersCSV, SIGNAL(dataLine(QStringList)), this, SLOT(loadGoalMember(QStringList)), Qt::DirectConnection);

    connect(m_pathDomainesCSV, SIGNAL(finish()), this, SLOT(finishDomaine()), Qt::DirectConnection);
    connect(m_pathMembersInternalCSV, SIGNAL(finish()), this, SLOT(finishMember()), Qt::DirectConnection);
    //connect(m_pathMembersExternalCSV, SIGNAL(dataLine(QStringList)), this, SLOT(finishMember()));
    connect(m_pathGoalCSV, SIGNAL(finish()), this, SLOT(finishGoal()), Qt::DirectConnection);
    connect(m_pathDocumentsCSV, SIGNAL(finish()), this, SLOT(finishDocument()), Qt::DirectConnection);
    connect(m_pathCommuCSV, SIGNAL(finish()), this, SLOT(finishCommu()), Qt::DirectConnection);
    connect(m_pathGoalMembersCSV, SIGNAL(finish()), this, SLOT(finishGoalMember()), Qt::DirectConnection);

    QThread *thread = new QThread;
    m_pathDomainesCSV->moveToThread(thread);

    QThread *thread1 = new QThread;
    m_pathGoalCSV->moveToThread(thread1);

    QThread *thread2 = new QThread;
    m_pathDocumentsCSV->moveToThread(thread2);

    QThread *thread3 = new QThread;
    m_pathCommuCSV->moveToThread(thread3);

    QThread *thread4 = new QThread;
    m_pathGoalMembersCSV->moveToThread(thread4);

    m_current = m_pathMembersInternalCSV;
    m_ready = true;
}

void Loading::setMessageLoading(QString message)
{
    mutex.lock();
    m_messageLoading = message;
    mutex.unlock();
}

QString Loading::messageLoading()
{
    QString m;
    mutex.lock();
    m = m_messageLoading;
    mutex.unlock();
    return m;
}

void Loading::load()
{
    start();
}

void Loading::loadDomaine(QStringList data)
{
    /*
    addDomaine(QString nameCommu,
               QString nameDomaine,
               QString IdDomaine,
               QString IdDomaineParent,
               QStringList GOALsmodificateurs,
               QStringList GOALsLecteurs,
               QStringList GOALsGestionnaires,
               QString responsable,
               QStringList gestionnaires,
               QStringList modificateurs,
               QStringList lecteurs,
               QString niveau,
               QString asservisseur,
               QString synchronises)
*/

    if (data.size() > 3)
        m_data->addDomaine(data[m_pathMembersInternalCSV->getColumn("AN")], //QString nameCommu
                data[m_pathMembersInternalCSV->getColumn("B")], // QString nameDomaine
                data[m_pathMembersInternalCSV->getColumn("A")], // QString IdDomaine
                data[m_pathMembersInternalCSV->getColumn("D")], // QString IdDomaineParent
                data[m_pathMembersInternalCSV->getColumn("Z")].split(","), //QStringList GOALsmodificateurs,
                data[m_pathMembersInternalCSV->getColumn("AD")].split(","), // QStringList GOALsLecteurs,
                data[m_pathMembersInternalCSV->getColumn("O")].split(","), //  QStringList GOALsGestionnaires,
                data[m_pathMembersInternalCSV->getColumn("L")], //QString responsable,
                data[m_pathMembersInternalCSV->getColumn("M")].split(","), // QStringList gestionnaires,
                data[m_pathMembersInternalCSV->getColumn("X")].split(","), //  QStringList modificateurs,
                data[m_pathMembersInternalCSV->getColumn("AB")].split(","), // QStringList lecteurs,
                data[m_pathMembersInternalCSV->getColumn("C")], // QString niveau,
                data[m_pathMembersInternalCSV->getColumn("S")], // QString asservisseur,
                data[m_pathMembersInternalCSV->getColumn("T")] // QString synchronises
            );
}

void Loading::loadMember(QStringList data)
{
    //qDebug() << data;
    if (data.size() > 2)
        m_data->addUser(data[m_pathMembersInternalCSV->getColumn("A")],//Identifiant
                data[m_pathMembersInternalCSV->getColumn("B")],//Nom
                data[m_pathMembersInternalCSV->getColumn("C")]);//Prenom
}

void Loading::loadGoal(QStringList data)
{
    if (data.size() > 3)
    {
        m_data->addGoal(data[m_pathMembersInternalCSV->getColumn("B")],//Nom
                data[m_pathMembersInternalCSV->getColumn("A")],//Id
                data[m_pathMembersInternalCSV->getColumn("K")],//Responsable
                data[m_pathMembersInternalCSV->getColumn("D")]);//Etat
        m_g->addGoal(data[m_pathMembersInternalCSV->getColumn("B")]);
    }
}

void Loading::loadDocument(QStringList data)
{
    /*
    if (data.size() > 3)
        m_data->addDocument();*/

    //qDebug() << data[m_pathMembersInternalCSV->getColumn("T")];

    if (data.size() > 3)
        m_data->addDocument(data[m_pathMembersInternalCSV->getColumn("D")],//name
                data[m_pathMembersInternalCSV->getColumn("T")],//iddomaine
                data[m_pathMembersInternalCSV->getColumn("B")],//version
                data[m_pathMembersInternalCSV->getColumn("H")],//proprio
                data[m_pathMembersInternalCSV->getColumn("A")],//id
                data[m_pathMembersInternalCSV->getColumn("M")],//datecreation
                data[m_pathMembersInternalCSV->getColumn("O")],//dateModif
                data[m_pathMembersInternalCSV->getColumn("AI")],//nbPj
                data[m_pathMembersInternalCSV->getColumn("AD")],//namePj
                0,//nbConsult
                data[m_pathMembersInternalCSV->getColumn("AL")],//conf
                data[m_pathMembersInternalCSV->getColumn("C")]//status
                    );
}

void Loading::loadCommu(QStringList data)
{
    if (data.size() > 1)
    {
        if (QString(data[m_pathMembersInternalCSV->getColumn("B")]) == "Nom de la communaute")
            return;
        QString goals = data[m_pathMembersInternalCSV->getColumn("Y")];
        if (goals.isEmpty())
        m_data->addCommunaute(QString(data[m_pathMembersInternalCSV->getColumn("B")]),//Nom
                goals.split(","));//Goals
        qDebug() << data[m_pathMembersInternalCSV->getColumn("B")];
        //qDebug() << QString(data[m_pathMembersInternalCSV->getColumn("B")]).toUtf8();
    }
}

void Loading::loadGoalMember(QStringList data)
{
    if (data.size() > 1)
    {
        m_data->addGoalMember(data[m_pathMembersInternalCSV->getColumn("A")],//idgoal
                data[m_pathMembersInternalCSV->getColumn("C")]);//idmember
        //qDebug() << data;
    }
}

void Loading::finishDomaine()
{
    qDebug() << "Finish plan";
    m_messageLoadingGlobal = "Fichiers : 6 / 6";
    m_messageLoading = "Chargements des documents";
    m_current = m_pathDocumentsCSV;
    m_pathDocumentsCSV->loading();

}

void Loading::finishMember()
{
    qDebug() << "Finish Member";
    m_messageLoading = "Chargements des goals";
    m_current = m_pathGoalCSV;
    m_messageLoadingGlobal = "Fichiers : 2 / 6";
    m_pathGoalCSV->loading();
}

void Loading::finishGoal()
{
    m_messageLoading = "Chargements des communautés";
    qDebug() << "Finish Goal";
    m_messageLoadingGlobal = "Fichiers : 3 / 6";
    m_current = m_pathCommuCSV;
    m_pathCommuCSV->loading();
}

void Loading::finishDocument()
{
    qDebug() << "Finish Documents";
    m_data->getInfo();
    m_finish = true;

}

void Loading::finishCommu()
{
    m_messageLoadingGlobal = "Fichiers : 4 / 6";
    qDebug() << "Finish Commu";
    m_messageLoading = "Chargements des goals membres";
    m_current = m_pathGoalMembersCSV;
    m_pathGoalMembersCSV->loading();
}

void Loading::finishGoalMember()
{
    qDebug() << "Finish Goal members";
    m_messageLoadingGlobal = "Fichiers : 5 / 6";
    m_messageLoading = "Chargements des domaines";
    m_current = m_pathDomainesCSV;
    m_pathDomainesCSV->loading();
}

void Loading::run()
{
    if (m_finish == true)
        return;
    loadFiles();
    m_messageLoading = "Chargements des membres";
    m_messageLoadingGlobal = "Fichiers : 1 / 6";
    QThread *thread = new QThread;
    m_pathMembersExternalCSV->moveToThread(thread);
    m_pathMembersExternalCSV->loading();
    QThread *thread2 = new QThread;
    m_pathMembersInternalCSV->moveToThread(thread2);
    m_pathMembersInternalCSV->loading();
}
