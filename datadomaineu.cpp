#include "datadomaineu.h"

DataDomaineU::DataDomaineU(Domaine *d, QObject *parent) : QObject(parent)
{
    m_domaine = d;
}
