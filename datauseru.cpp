#include "datauseru.h"

DataUserU::DataUserU(User *e, UserCommu *u, bool o, QObject *parent)
{
    m_u = u;
    m_e = e;
    m_o = o;
}
