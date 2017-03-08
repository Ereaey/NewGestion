#ifndef LOADING_H
#define LOADING_H

#include <QObject>
#include <QThread>
#include <QDirIterator>
#include <QDate>
#include <QDebug>
#include <QFileInfo>
#include "autocompletgoal.h"
#include "autocompletuser.h"
#include "filecsv.h"
#include "data.h"

class Loading : public QThread
{
    Q_OBJECT
    Q_PROPERTY(QString messageLoading READ messageLoading NOTIFY currentActionChanged)
    Q_PROPERTY(QString messageLoadingGlobal READ messageLoadingGlobal NOTIFY currentMessageChanged)
    Q_PROPERTY(float progress READ progress)
    Q_PROPERTY(bool finish READ finish NOTIFY finishChanged)
    Q_PROPERTY(bool ready READ ready)

public:
    explicit Loading(Data *d, autoCompletGoal *g, autoCompletUser *user, QObject *parent = 0);
    void setMessageLoading(QString message);

    QString messageLoading();
    QString messageLoadingGlobal() const
    {
        return m_messageLoadingGlobal;
    }
    bool finish() const
    {
        return m_finish;
    }
    bool ready() const
    {
        return m_ready;
    }
    float progress()
    {
        //qDebug() << QString::number(m_current->getProgress());
        double value = 0;
        for (int i = 0; i < m_current.size(); i++)
            value += m_current[i]->getProgress();
        return value / m_current.size();
    }

signals:

public slots:
    void load();

Q_SIGNALS:
    void currentActionChanged();
    void currentMessageChanged();
    void finishChanged();

private slots:
    void loadDomaine(QStringList data);
    void loadMember(QStringList data);
    void loadGoal(QStringList data);
    void loadDocument(QStringList data);
    void loadCommu(QStringList data);
    void loadGoalMember(QStringList data);

    void finishDomaine();
    void finishMember();
    void finishGoal();
    void finishDocument();
    void finishCommu();
    void finishGoalMember();

protected:
    void run();

private:
    void loadFiles();
    bool m_ready;
    int fileDocuments;
    int fileDomaines;

    QMutex mutex;
    QFileInfoList m_listDrives;
    Data *m_data;
    QVector<QFileInfo> m_pathDomaines;
    QFileInfo m_pathMembersInternal;
    QFileInfo m_pathMembersExternal;
    QFileInfo m_pathGoal;
    QVector<QFileInfo> m_pathDocuments;
    QFileInfo m_pathCommu;
    //QFileInfo m_pathFiles;
    QFileInfo m_pathGoalMembers;

    QVector<FileCSV *> m_pathDomainesCSV;
    FileCSV * m_pathMembersInternalCSV;
    FileCSV * m_pathMembersExternalCSV;
    FileCSV * m_pathGoalCSV;
    QVector<FileCSV *> m_pathDocumentsCSV;
    FileCSV * m_pathCommuCSV;
    FileCSV * m_pathGoalMembersCSV;

    QVector<FileCSV *> m_current;

    bool m_finish;
    QString m_messageLoading;
    QString m_messageLoadingGlobal;
    autoCompletGoal *m_g;
    autoCompletUser *m_user;
};

#endif // LOADING_H
