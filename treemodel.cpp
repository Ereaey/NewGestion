#include "treemodel.h"
#include "treeitem.h"
#include "QtDebug"
const int number = 100;

TreeItem *createTreeItem(){
    /*
    auto res = new TreeItem(QString::number(qrand() % number));
    while(qrand() % 2)
        res->addChildItem(createTreeItem());
    return res;*/
}

Model::Model(QObject *parent) :
    QObject(parent),
    m_tree(QList<TreeItem*>())
{

    //m_tree.append(createTreeItem());
    /*m_tree.append(createTreeItem());
    m_tree.append(createTreeItem());
    m_tree.append(createTreeItem());
    m_tree.append(createTreeItem());*/
}

void Model::setRoot(TreeItem *item)
{
    qDebug() << "Racine:" << item->content();
    m_tree.clear();
    qDebug() << "Racine:" << item->content();
    m_tree.append(item);
    qDebug() << "Racine:" << item->content();
    emit treeChanged();
}

const QList<TreeItem *> &Model::tree() const{
    return m_tree;
}

const QList<QObject *> Model::treeAsQObjects() const{
    QList<QObject *> res;
    res.reserve(m_tree.count());
    for(auto i : m_tree)
        res.append(i);
    return res;
}
