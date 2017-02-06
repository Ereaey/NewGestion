#ifndef DATACOMMU_H
#define DATACOMMU_H

#include <QObject>

class DataCommu : public QObject
{
    Q_OBJECT

    public:
        explicit DataCommu(QString nom, QString id, QObject *parent = 0);
        Q_PROPERTY(QString nom READ nom)
        QString nom() const;

        Q_PROPERTY(QString id READ id)
        QString id() const;

        Q_PROPERTY(int result READ result NOTIFY resultM)
        int result() const;

        void setResult(int result);

    Q_SIGNALS:
        void resultM();

    private:
        QString m_id;
        QString m_nom;
        int m_result;
};

#endif // DATACOMMU_H
