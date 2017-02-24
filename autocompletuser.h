#ifndef AUTOCOMPLETUSER_H
#define AUTOCOMPLETUSER_H

#include <QObject>
#include <QThread>
#include <QVector>
#include <QList>
#include <QVariant>
#include "datauser.h"

class autoCompletUser : public QThread
{
    Q_OBJECT
    public:
        explicit autoCompletUser();
        void addUser(QString nom, QString id);
        Q_INVOKABLE void searchUser(QString nom);

        Q_PROPERTY(bool finish READ finish NOTIFY finishChanged)
        Q_PROPERTY(QVariant result READ result NOTIFY refreshResult)

        bool finish() const{return m_finish;}
        QVariant result() const{return QVariant::fromValue(m_result);}

    Q_SIGNALS:
        void finishChanged();
        void refreshResult();

    private:
        QVector<DataUser*> m_users;
        bool m_finish;
        QList<QObject*> m_result;
        QString m_user;

    protected:
        void run();
};

#endif // AUTOCOMPLETUSER_H
