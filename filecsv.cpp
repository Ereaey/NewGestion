#include "filecsv.h"
#include <QDebug>
#include <QTextCodec>
FileCSV::FileCSV(QString path, int nbColumn, bool version, QObject *parent) : QThread(parent)
{
    m_nbColumn = nbColumn;
    m_mutex = new QMutex();
    m_path = path;
    m_finish = false;

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

    //QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));

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


void FileCSV::loading()
{
    start();
}

void FileCSV::run()
{
    if (m_finish == true)
        return;
    QFile file(m_path);
    if (!file.open(QIODevice::ReadOnly))
            return;

    //QTextStream in(&file);
    //in.setCodec();
    QByteArray current_line = "";
    QList<QByteArray> listeData;
    QStringList d;

    //QTextCodec *codec =
    int i = 0;
    int total0 = 0;

    while (!file.atEnd())
    {
        QByteArray line = file.readLine();
        //line = line.toLocal8Bit();
        //qDebug() <<  QString::fromUtf8(line.toUtf8());
        current_line += line;

        if (current_line.size() > 2)
        {
            if (current_line.at(current_line.size() - 1) == QChar('\n') && (current_line.at(current_line.size() - 2) == QChar('"') || current_line.at(current_line.size() - 2) == QChar(';')))
            {
                listeData.clear();
                if(V1 == false)
                {
                   // listeData = current_line.split("\";\"");
                    current_line.replace(" ;", "");
                    current_line.replace("; ", "");
                    listeData = current_line.split(';');
                }
                else
                {
                    current_line.replace(" ;", "");
                    current_line.replace("; ", "");
                    QByteArray current;
                    for (int i = 0; i < current_line.size(); i++)
                    {
                        current.append(current_line.at(i));
                        if (current_line.at(i) == ';')
                        {
                            if (i == 0)
                            {
                                listeData.append(current);
                                current.clear();
                            }
                            else if (i == current_line.size() - 2)
                            {
                                listeData.append(current);
                                current.clear();
                            }
                            else if (i > 0 || i != current_line.size() - 2)
                            {
                                if (current_line.at(i - 1) == '"' && current_line.at(i + 1) == '"')
                                {
                                    listeData.append(current);
                                    current.clear();
                                }
                            }
                        }
                        if (current_line.at(i) == '"' && i == current_line.size() - 2)
                            listeData.append(current);
                    }
                    //listeData = current_line.split(';');
                }
                d.clear();
                for (int i = 0; i < listeData.size(); i++)
                {
                    QByteArray h = listeData.at(i);
                    h = h.replace('"', "");
                    h = h.replace('\n', "");
                    h = h.replace(';', "");

                    /*
                    QByteArray eg;
                    eg.append(h);*/

                    QString de = QString::fromLatin1(h);
                    QTextStream in(&de);

                    in.setCodec("UTF-8");
                    d.push_back(in.readAll());
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

    m_finish = true;
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
