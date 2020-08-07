#include "datastore.h"

DataStore::DataStore(QObject *parent) : QObject(parent) {}

QStringList DataStore::pickRestaurants(QString url, QString tempo) {

  // validating and manipulating url

  if (!validateUrl(&url)) {
    return QStringList("Invalid Url or File!");
  }

  QFile file(url);
  if (!file.open(QIODevice::ReadOnly)) {
    qDebug() << "erro encontrado";
    qDebug() << file.errorString();

    return QStringList(file.errorString());
  }

  QStringList restaurantName;
  QStringList restaurantTime;

  while (!file.atEnd()) {
    QByteArray line = file.readLine();
    restaurantName.append(line.split(',').first());
    restaurantTime.append(line.split(',').last());
  }

  restaurantName.pop_front();
  restaurantTime.pop_front();

  this->nameList = restaurantName;
  this->workTimeList = restaurantTime;

  // Manipulação das variaveis de tempo

  int hora = 0, minuto = 0;

  if (tempo.length() == 5) {

    hora = tempo.mid(0, 2).toInt();
    minuto = tempo.mid(3, 2).toInt();

  } else if (tempo.length() == 4) {

    hora = tempo.mid(0, 2).toInt();
    minuto = tempo.mid(2, 2).toInt();
  }

  QTime tm(hora, minuto);

  QTime tempoInicial;
  QTime tempoFinal;

  QStringList avaiableRestaurants;

  // verificação dos restaurantes disponíveis na faixa de tempo

  for (int i = 0; i < this->workTimeList.length(); i++) {

    tempoInicial.setHMS(this->workTimeList[i].mid(0, 2).toInt(),
                        this->workTimeList[i].mid(3, 2).toInt(), 0, 0);
    tempoFinal.setHMS(this->workTimeList[i].mid(6, 2).toInt(),
                      this->workTimeList[i].mid(9, 2).toInt(), 0, 0);

    if (tm > tempoInicial && tm < tempoFinal) {
      avaiableRestaurants.append(this->nameList[i]);
    }
  }

  qInfo() << "---Restaurantes disponívels neste horário---";
  for (int i = 0; i < avaiableRestaurants.length(); i++) {
    qInfo() << "Restaurant [" << i << "]" << avaiableRestaurants[i];
  }

  this->avaiableRestaurants = avaiableRestaurants;

  return this->avaiableRestaurants;
}

int DataStore::qtdAvaiableRestaurants() {
  return this->avaiableRestaurants.length();
}

bool DataStore::validateUrl(QString *url) {
  // manipulando string url -> removendo o file://
  url->remove(0, 6);

  // Verificando se é um arquivo csv

  if (!url->contains(".csv")) {
    return false;
  }

  return true;
}
