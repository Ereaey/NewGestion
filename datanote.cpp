#include "datanote.h"

DataNote::DataNote(Data *d, QObject *parent) : QObject(parent)
{
    m_d = d;
    connect(m_d, SIGNAL(commuChanged()), this, SLOT(test()));
}

void DataNote::test()
{
    emit noteChanged();
    emit  nbUserChanged();
    emit  nbDomaineChanged();
    emit  nbDocumentChanged();
    emit nbGoalChanged();
    emit niveauChanged();

    emit domaineVideChanged();
    emit domaineFullChanged();
    emit domaineAsservisseursChanged();
    emit domainesLibreSChanged();
    emit domainesLibreChanged();

    emit documentsC0Changed();
}
