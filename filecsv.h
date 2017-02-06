#ifndef FILECSV_H
#define FILECSV_H

#include <QObject>
#include <QVector>
#include <QFile>
#include <QTextStream>
#include <QFileInfo>
#include <QCoreApplication>
#include <QThread>
#include <QMutex>
#include <QObject>

class FileCSV  : public QObject
{
    Q_OBJECT
    public:
        FileCSV(QString path, int nbColumn, bool version = true, QObject *parent = 0);
        ~FileCSV();
        QString getName();
        float getProgress();
        int getColumn(QString name);
        void loading();

    private:
        QMap<QString, int> cols;
        QString m_name, m_path;
        QMutex *m_mutex, *m_mutexProgress;
        double m_size, m_nbColumn, V1;
        float m_progress;

    signals:
        void dataLine(QStringList data);
        void finish();

    protected:
        void run();
};

#endif // FILECSV_H
