#include "database.h"
#include <string>

using namespace std;
DataBase::DataBase(QObject *parent) : QObject(parent)
{

}

DataBase::~DataBase()
{

}

/* Методы для подключения к базе данных
 * */
void DataBase::connectToDataBase()
{
    /* Перед подключением к базе данных производим проверку на её существование.
     * В зависимости от результата производим открытие базы данных или её восстановление
     * */
    if(!QFile(DATABASE_NAME).exists()){
        qDebug() << "Шаг 1";
        this->restoreDataBase();

    } else {
        qDebug() << "Шаг 2";
        this->openDataBase();
    }
}

/* Методы восстановления базы данных
 * */
bool DataBase::restoreDataBase()
{
    if(this->openDataBase()){
        if(!this->createTable()){
            return false;
        } else {
            return true;
        }
    } else {
        qDebug() << "Не удалось восстановить базу данных";
        return false;
    }
    return false;
}

/* Метод для открытия базы данных
 * */
bool DataBase::openDataBase()
{
    /* База данных открывается по заданному пути
     * и имени базы данных, если она существует
     * */
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName(DATABASE_HOSTNAME);
    db.setDatabaseName(DATABASE_NAME);
    if(db.open()){
        qDebug() << "Открыта БД";
        return true;
    } else {
        return false;
    }
}

void DataBase::closeDataBase()
{
    db.close();
}

bool DataBase::createTable()
{
    QSqlQuery query;
    if(!query.exec( "CREATE TABLE dogs ( "
                    "id INTEGER PRIMARY KEY NOT NULL, "
                    "name VARCHAR(255) NOT NULL,"
                    "breed VARCHAR(255) NOT NULL,"
                    "age INTEGER NOT NULL );"
                    )){
        qDebug() << "Ошибка создания таблицы" << TABLE;
        qDebug() << query.lastError().text();
        return false;
    } else {
        qDebug() << "Создана таблица";
        return true;
    }
    return false;
}

/* Метод для вставки записи в базу данных
 * */
bool DataBase::inserIntoTable(const QVariantList &data)
{
    /* Запрос SQL формируется из QVariantList,
     * в который передаются данные для вставки в таблицу.
     * */
    QSqlQuery query;
    /* В начале SQL запрос формируется с ключами,
     * которые потом связываются методом bindValue
     * для подстановки данных из QVariantList
     * */
    query.prepare("INSERT INTO dogs (name, breed, age) VALUES (?,?,?);");
    int a = data[2].toInt();
    query.addBindValue(data[0].toString());
    query.addBindValue(data[1].toString());
    query.addBindValue(a);
    // После чего выполняется запросом методом exec()
    if(!query.exec()){
        qDebug() << "Ошибка вставки данных" << a;
        qDebug() << query.lastError().text();
        return false;
    } else {
        return true;
    }
    return false;
}
