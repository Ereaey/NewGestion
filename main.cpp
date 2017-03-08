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
#include "autocompletgoal.h"
#include "datadomaines.h"
#include "autocompletuser.h"

int main(int argc, char *argv[])
{
    //QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    //QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));

    //qDebug() << "system name:"      << QLocale::system().name();
    //qDebug() << "codecForCStrings:" << QTextCodec::codecForCStrings();
    //qDebug() << "codecForLocale:"   << QTextCodec::codecForLocale()->name();

    QThread *thread = new QThread;
    autoCompletGoal *g = new autoCompletGoal;
    autoCompletUser *user = new autoCompletUser;
    Model *m = new Model;
    Data *d = new Data(m);
    Loading *l = new Loading(d, g, user);
    l->moveToThread(thread);
    Treatment *tre = new Treatment(d);
    DataDomaines *ds = new DataDomaines();
    DataNote *ef = new DataNote(d);
    //QQuickStyle::setStyle("Material");

    //qDebug() << "ééé";


    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty("loading", l);
    engine.rootContext()->setContextProperty("treatment", tre);
    engine.rootContext()->setContextProperty("treet", m);
    engine.rootContext()->setContextProperty("data", d);
    engine.rootContext()->setContextProperty("goals", g);
    engine.rootContext()->setContextProperty("listDomaine", ds);
    engine.rootContext()->setContextProperty("note", ef);
    engine.rootContext()->setContextProperty("users", user);
    engine.load(QUrl(QLatin1String("qrc:/mainWindow.qml")));

    return app.exec();
}
