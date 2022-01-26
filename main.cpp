#include <QCoreApplication>
#include <QDebug>
#include <QtSql>
#include <iostream>

using namespace std;

void general_query();
void insert_into(int id, QString name, QString email);
void delete_from(QString name);
void search(QString name);
//void update2(QString name, int a);
void update_name(QString name, QString a);
void update_number(QString name, QString newNumber);

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("E:/sqliteDatabases/myShop.db");

    if(db.open()){
        qDebug() <<"opened";
    }else{
        auto error = db.lastError();
        std::cerr << "Cannot open database: " << error.text().toStdString() << '\n';
    }


//***********METHODS************

//insert_into(10, "John Doe", "doe2@mail.hu");
//delete_from("vali");
//search("bud");
update_name("PISTA", "PISTA2");
//update_number("PISTA2", "111");
update_number("PISTA2", "06208765512");
general_query();

    return a.exec();
}

void general_query(){
    QSqlQuery q;
    q.prepare("SELECT * FROM users;");
    q.exec();
    while(q.next()){
        int id = q.value(0).toInt();
        QString name2 = q.value(1).toString();
        QString email2 = q.value(3).toString();
        QString number = q.value(2).toString();
        qDebug() << id <<" "<< name2 <<" "<< number <<" "<< email2;
    }
}

void insert_into(int id, QString name, QString email){

    QSqlQuery query;
    query.prepare("INSERT INTO users (id, name, email) "
                     "VALUES (:id, :name, :email)");
    query.bindValue(":id", id);
    query.bindValue(":name", name);
    query.bindValue(":email", email);
    query.exec();

}

//delete from users where name = 'jonas';
void delete_from(QString name){
    QSqlQuery query;
    query.prepare("DELETE FROM users WHERE name = ?");
    query.addBindValue(name);
    query.exec();


}

void search(QString name){

    QSqlQuery q;
    q.prepare("SELECT * FROM users WHERE name like ?");
    q.addBindValue(name+"%");
    q.exec();
    if(q.exec()){
        qDebug() << "OK";
    }else{
         qDebug() << q.lastError().text();
         qDebug() << q.lastError().databaseText();
    }
    while(q.next()){
        int id = q.value(0).toInt();
        QString name = q.value(1).toString();
        QString email = q.value(2).toString();
        qDebug() << name << email << id;
    }

}

//UPDATE users SET name ='kiss jakab' WHERE name = 'jakab';
void update_number(QString name, QString newNumber){
    cout <<"update:"<<endl;
    QSqlQuery q2;
     q2.prepare("UPDATE users SET phone_number = :number WHERE name = :name");//nem volt jó a ':name'.........:(
     q2.bindValue(":number", newNumber);
     q2.bindValue(":name", name);
     q2.exec();
     if (!q2.exec()) {
                 auto error = q2.lastError();
                 std::cerr << "Cannot update database/updatenumber/: " << error.text().toStdString() << '\n';
             } else {
                 std::cout << "Update succeeded."<<endl;;
             }
     //cout <<"while:"<<endl;
     if(!q2.isValid()){
         //qDebug() << "not valid" ;
     }
     //q2.first();
     //cout << q2.next() <<endl;
     //QSqlQuery q3;
     QSqlQuery q;
     q.prepare("SELECT * FROM users WHERE name =:name");
     q.bindValue(":name", name);
     q.exec();
     while(q.next()){
         int id = q.value(0).toInt();
         QString name2 = q.value(1).toString();
         QString email2 = q.value(2).toString();
         qDebug() << name2 << email2 << id;
         /*
         q2.prepare("UPDATE users SET name = :name WHERE id = :id");//nem volt jó a ':name'.........:(
         q2.bindValue(":name", newName);
         q2.bindValue(":id", id);
         q2.exec();
         */
     }
     QSqlQuery q3;
     q3.prepare("SELECT * FROM users WHERE name =:name");
     q3.bindValue(":name", name);
     q3.exec();
     while(q3.next()){
         int id = q3.value(0).toInt();
         QString name2 = q3.value(1).toString();
         QString email2 = q3.value(2).toString();
         qDebug() << name2 << email2 << id;

     }

}

//update users set name = 'jani' where id = 5;
void update_name(QString name, QString newName){
    cout <<"update:"<<endl;
    QSqlQuery q2;
     q2.prepare("UPDATE users SET name = :name WHERE name = :name");//nem volt jó a ':name'.........:(
     q2.bindValue(":name", newName);
     q2.bindValue(":name", name);
     q2.exec();
     if (!q2.exec()) {
                 auto error = q2.lastError();
                 std::cerr << "Cannot update database: " << error.text().toStdString() << '\n';
             } else {
                 std::cout << "Update succeeded."<<endl;;
             }
     //cout <<"while:"<<endl;
     if(!q2.isValid()){
         //qDebug() << "not valid" ;
     }
     //q2.first();
     //cout << q2.next() <<endl;
     //QSqlQuery q3;
     QSqlQuery q;
     q.prepare("SELECT * FROM users WHERE name =:name");
     q.bindValue(":name", name);
     q.exec();
     while(q.next()){
         int id = q.value(0).toInt();
         QString name2 = q.value(1).toString();
         QString email2 = q.value(2).toString();
         qDebug() << name2 << email2 << id;
         q2.prepare("UPDATE users SET name = :name WHERE id = :id");//nem volt jó a ':name'.........:(
         q2.bindValue(":name", newName);
         q2.bindValue(":id", id);
         q2.exec();
     }
     QSqlQuery q3;
     q3.prepare("SELECT * FROM users WHERE name =:name");
     q3.bindValue(":name", newName);
     q3.exec();
     while(q3.next()){
         int id = q3.value(0).toInt();
         QString name2 = q3.value(1).toString();
         QString email2 = q3.value(2).toString();
         qDebug() << name2 << email2 << id;

     }

}
