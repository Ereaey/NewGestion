#ifndef AUTOCOMPLETGOAL_H
#define AUTOCOMPLETGOAL_H

#include <QObject>
#include <QThread>
#include <QVariant>

class autoCompletGoal : public QThread
{
    Q_OBJECT
    public:
        autoCompletGoal();
        void addGoal(QString name){m_goals.append(name);}
        Q_PROPERTY(bool finish READ finish NOTIFY finishChanged)
        Q_PROPERTY(QVariant result READ result NOTIFY refreshResult)

        Q_INVOKABLE void search(QString name);

        bool finish() const{return m_finish;}
        QVariant result() const{return QVariant::fromValue(m_result);}

    Q_SIGNALS:
        void finishChanged();
        void refreshResult();

    private:
        QStringList m_goals;
        bool m_finish;
        QStringList m_result;
        QString m_goal;

    protected:
        void run();
};

#endif // AUTOCOMPLETGOAL_H
