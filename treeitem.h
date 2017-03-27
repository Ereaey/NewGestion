#ifndef TREEITEM_H
#define TREEITEM_H

#include <QObject>

class TreeItem : public QObject
{
    Q_OBJECT
public:
    explicit TreeItem(QString content, int id, bool problem, QObject *parent = 0);

    Q_PROPERTY(QString content READ content NOTIFY contentChanged)
    const QString & content() const;
    void setContent(const QString & content);

    Q_PROPERTY(int id READ id)
    const int id(){return m_id;}

    Q_PROPERTY(bool problem READ problem)
    const bool problem(){return m_problem;}

    Q_PROPERTY(QList<QObject*> childItems READ childItemsAsQObject NOTIFY childItemsChanged)
    const QList<TreeItem *> &childItems() const;
    const QList<QObject *> childItemsAsQObject() const;
    void addChildItem(TreeItem * childItem);

    Q_PROPERTY(bool isOpen READ isOpen WRITE setIsOpen NOTIFY isOpenChanged)
    bool isOpen() const;
    void setIsOpen(bool isOpen);

    Q_PROPERTY(bool isSelect READ isSelect WRITE setIsSelect NOTIFY isSelectChanged)
    bool isSelect() const;
    void setIsSelect(bool isSelect);

    Q_PROPERTY(bool hasChild READ hasChild NOTIFY hasChildChanged)
    bool hasChild() const;

    Q_PROPERTY(QString color READ getColor WRITE setColor NOTIFY colorChanged)
    void setColor(QString color);
    QString getColor() const;


signals:
    void contentChanged();
    void childItemsChanged();
    void isOpenChanged();
    void isSelectChanged();
    void hasChildChanged();
    void colorChanged();

public slots:
private:
    QString m_content;
    QList<TreeItem *> m_childItems;
    bool m_isOpen;
    bool m_isSelect;
    int m_id;
    bool m_problem;
    QString m_color;
};

#endif // TREEITEM_H
