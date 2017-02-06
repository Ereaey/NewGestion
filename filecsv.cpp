#include "filecsv.h"
#include <QDebug>

FileCSV::FileCSV(QString path, int nbColumn, bool version, QObject *parent) : QObject(parent)
{
    m_nbColumn = nbColumn;
    m_mutex = new QMutex();
    m_path = path;

    QString chaine;
    for (int it = 0; it < 5; it++)
    {
        for (int i = 0; i < 26; i++)
        {
            chaine.clear();
            if (it != 0)
                chaine += QChar('A' + (it - 1));
            chaine += QChar('A' + i);
            cols[chaine] = i + it * 26;
        }
    }


    QFileInfo file1(path);
    m_name = file1.fileName();
    m_size = file1.size();
    V1 = version;
    m_progress = 0;
}

int FileCSV::getColumn(QString name)
{
    return cols[name];
}

FileCSV::~FileCSV()
{
    //for (int i = 0; i < lines.size(); i++)
    //    qDeleteAll(lines[i]);
    //qDeleteAll(lines);
}

/*
void FileCSV::loading()
{
    start();
}
*/
void FileCSV::loading()
{
    QFile file(m_path);
    if (!file.open(QIODevice::ReadOnly))
            return;

    //QTextStream in(&file);
    QString current_line = "";
    QStringList listeData;
    QStringList d;

    int i = 0;
    int total0 = 0;

    while (!file.atEnd())
    {
        QString line = file.readLine();

        current_line += line;

        if (current_line.size() > 2)
        {
            if (current_line.at(current_line.size() - 1) == QChar('\n') && (current_line.at(current_line.size() - 2) == QChar('"') || current_line.at(current_line.size() - 2) == QChar(';')))
            {
                if(V1 == true)
                    listeData = current_line.split("\";\"");
                else
                {
                    listeData = current_line.remove(" ;").remove("; ").split(";");
                }
                d.clear();
                for (int i = 0; i < listeData.size(); i++)
                {
                    QString a = listeData.at(i);

                    d.push_back(a.remove(QChar('"'), Qt::CaseInsensitive).remove(QChar('\n'), Qt::CaseInsensitive));
                }

                if (d.size() != m_nbColumn)
                    qDebug() << m_path << " problem : " << QString::number(d.size()) << QString::number(i);

                emit dataLine(d);
                //lines.push_back(d);
                total0 += current_line.size();
                current_line.clear();
                i++;
                if (i%500)
                {
                m_mutex->lock();
                m_progress = (total0 / m_size) * 100;
                //qDebug() << m_progress;
                //m_progress *= 100;
                m_mutex->unlock();
                }
            }
        }
    }

    emit finish();
    qDebug() << m_path << QString::number(i) << QString::number(total0) << QString::number(m_size);
}

QString FileCSV::getName()
{
    return m_name;
}

float FileCSV::getProgress()
{
    int progress;
    m_mutex->lock();
    progress = m_progress;
    m_mutex->unlock();
    return progress;
}
