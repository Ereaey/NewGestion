#ifndef DATADOMAINES_H
#define DATADOMAINES_H

#include <QObject>
#include <QVariant>
#include "datadomaine.h"
#include <QClipboard>
#include <QApplication>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
class DataDomaines : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVariant domaines READ domaines NOTIFY refreshDomaine)

    public:
        explicit DataDomaines(QObject *parent = 0);
        QVariant domaines() const{return QVariant::fromValue(m_domaines);}
        Q_INVOKABLE void addDomaine(QString name, QString id);
        Q_INVOKABLE void deleteDomaine(QString id);
        Q_INVOKABLE void copy(QString id);
        Q_INVOKABLE void exportList(QString path);
        Q_INVOKABLE void clear();

    signals:
        void refreshDomaine();

    public slots:

    private:
        QList<QObject*> m_domaines;
};

#endif // DATADOMAINES_H
