#include "datadomaines.h"

DataDomaines::DataDomaines(QObject *parent) : QObject(parent)
{

}

void DataDomaines::addDomaine(QString name, QString id)
{
    deleteDomaine(id);
    m_domaines.append(new DataDomaine(name, id));
    emit refreshDomaine();
}

void DataDomaines::deleteDomaine(QString id)
{
    for (unsigned int i = 0; i < m_domaines.size(); i++)
    {
        if (((DataDomaine*)m_domaines[i])->iddomaine() == id)
        {
            m_domaines.removeAt(i);
            emit refreshDomaine();
            return;
        }
    }
}

void DataDomaines::allCopy()
{
    QString text;
    for (unsigned int i = 0; i < m_domaines.size(); i++)
    {
        text += ((DataDomaine*)m_domaines[i])->iddomaine() + "\n";
    }
    QApplication::clipboard()->setText(text);
}

void DataDomaines::copy(QString id)
{
    QApplication::clipboard()->setText(id);
}

void DataDomaines::exportList(QString path)
{
    if (!path.isEmpty())
    {
        path.remove("file:///");
        path.remove("file:\\\/");
        QFile fichier(path);
        fichier.open(QIODevice::WriteOnly);

        QTextStream flux(&fichier);
        for (unsigned int i = 0; i < m_domaines.size(); i++)
        {
            flux << ((DataDomaine*)m_domaines[i])->iddomaine();
            flux << QChar(0x0D);
            flux << QChar(0x0A);
        }


        fichier.close();
    }
}

void DataDomaines::clear()
{
    m_domaines.clear();
    emit refreshDomaine();
}
