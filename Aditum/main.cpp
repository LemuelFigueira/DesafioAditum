#include "datastore.h"
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

int main(int argc, char *argv[]) {
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

  QGuiApplication app(argc, argv);

  app.setOrganizationName("somename");
  app.setOrganizationDomain("somename");

  QQmlApplicationEngine engine;
  const QUrl url(QStringLiteral("qrc:/main.qml"));
  QQmlContext *context = engine.rootContext();

  context->setContextProperty(QString("dataStore"), new DataStore);
  engine.load(url);

  return app.exec();
}
