#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>
#include <QQmlContext>
#include "loading.h"
#include "data.h"
#include "treemodel.h"
#include "treatment.h"
#include <QTextCodec>
#include <QDebug>


int main(int argc, char *argv[])
{
    //QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    //QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));

    qDebug() << "system name:"      << QLocale::system().name();
    //qDebug() << "codecForCStrings:" << QTextCodec::codecForCStrings();
    qDebug() << "codecForLocale:"   << QTextCodec::codecForLocale()->name();

    QThread *thread = new QThread;
    Model *m = new Model();
    Data *d = new Data(m);
    Loading *l = new Loading(d);
    l->moveToThread(thread);
    Treatment *tre = new Treatment(d);
    //QQuickStyle::setStyle("Material");

    qDebug() << "ééé";


    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty("loading", l);
    engine.rootContext()->setContextProperty("treatment", tre);

    engine.load(QUrl(QLatin1String("qrc:/mainWindow.qml")));

    return app.exec();
}
