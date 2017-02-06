#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>
#include <QQmlContext>
#include "loading.h"
#include "data.h"
#include "treemodel.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QThread *thread = new QThread;
    Model *m = new Model();
    Data *d = new Data(m);
    Loading *l = new Loading(d);
    l->moveToThread(thread);
    //QQuickStyle::setStyle("Material");

    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty("loading", l);

    engine.load(QUrl(QLatin1String("qrc:/mainWindow.qml")));

    return app.exec();
}
