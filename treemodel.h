#ifndef MODEL_H
#define MODEL_H

#include <QObject>

class TreeItem;

class Model : public QObject
{
    Q_OBJECT
public:
    explicit Model(QObject *parent = 0);

    Q_PROPERTY(QList<QObject*> tree READ treeAsQObjects NOTIFY treeChanged)
    const QList<TreeItem*> &tree() const;
    const QList<QObject*> treeAsQObjects() const;
    void setRoot(TreeItem* item);
    Q_INVOKABLE void refreshTree()
    {
        emit treeChanged();
    }

signals:
    void treeChanged();
public slots:

private:
    QList<TreeItem*> m_tree;
};

#endif // MODEL_H
