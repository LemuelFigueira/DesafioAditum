#ifndef DATASTORE_H
#define DATASTORE_H

#include <QDebug>
#include <QFile>
#include <QObject>
#include <QTime>
#include <iostream>

class DataStore : public QObject {
  Q_OBJECT
public:
  explicit DataStore(QObject *parent = 0);

public slots:
  QStringList pickRestaurants(QString url, QString tempo);
  int qtdAvaiableRestaurants();

  bool validateUrl(QString *url);

private:
  QStringList avaiableRestaurants;
  QStringList nameList;
  QStringList workTimeList;
};

#endif // DATASTORE_H
