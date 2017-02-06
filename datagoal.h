#ifndef DATAGOAL_H
#define DATAGOAL_H

#include <QObject>

class DataGoal : public QObject
{
    Q_OBJECT

    signals:

    public slots:

    public:
        explicit DataGoal(QString nom, QString idgoal, QString problem = "", QObject *parent = 0);
        Q_PROPERTY(QString nom READ nom)
        QString nom() const {return m_nom;}

        Q_PROPERTY(QString idgoal READ idgoal)
        QString idgoal() const{return m_idgoal;}

        Q_PROPERTY(QString problem READ problem)
        QString problem() const{return m_problem;}

    private:
        QString m_idgoal;
        QString m_nom;
        QString m_problem;
};

#endif // DATAGOAL_H
