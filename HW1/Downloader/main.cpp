#include <QtGui/QApplication>

#include <QTableWidget>
#include <QtSql>
#include "stardelegate.h"
#include "starrating.h"
#include "downloaderwindow.h"


//#include "downloaderwindow.h"


void populateTableWidget(QTableWidget *tableWidget)
{
    static const struct {
        const char *title;
        const char *genre;
        const char *artist;
        int rating;
    } staticData[] = {
        { "Mass in B-Minor", "Baroque", "J.S. Bach", 5 },
        { 0, 0, 0, 0 }
    };

    for (int row = 0; staticData[row].title != 0; ++row) {
        QTableWidgetItem *item0 = new QTableWidgetItem(staticData[row].title);
        QTableWidgetItem *item1 = new QTableWidgetItem(staticData[row].genre);
        QTableWidgetItem *item2 = new QTableWidgetItem(staticData[row].artist);
        QTableWidgetItem *item3 = new QTableWidgetItem;
        item3->setData(0,
                       qVariantFromValue(StarRating(staticData[row].rating)));

        tableWidget->setItem(row, 0, item0);
        tableWidget->setItem(row, 1, item1);
        tableWidget->setItem(row, 2, item2);
        tableWidget->setItem(row, 3, item3);
    }
}


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

//    QString s_cwd(getcwd(NULL,0));
//    qDebug() << "CWD is: " << s_cwd;

//    QSqlDatabase dbase = QSqlDatabase::addDatabase("QSQLITE");
//    dbase.setDatabaseName("my_db5.sqlite");
//    if (!dbase.open()) {
//        qDebug() << "Can't open DB";
//        return -1;
//    }
//    QSqlQuery a_query;
//    bool b = false;
//    // DDL query
//    QString str = "CREATE TABLE my_table ("
//            "number integer PRIMARY KEY NOT NULL, "
//            "address VARCHAR(255), "
//            "age integer"
//            ");";
//    b = a_query.exec(str);
//    if (!b) {
//        qDebug() << "Can't create.";
//    } else {
//        qDebug() << "Created";
//    }

//    // DML

//    srand ( time(NULL) );
//    for (int i = 0; i < 10; ++i) {
//        QString str_insert = "INSERT INTO my_table(number, address, age) "
//                "VALUES (%1, '%2', %3);";
//        str = str_insert.arg(rand())
//                .arg("hello world str.")
//                .arg("37");
//        b = a_query.exec(str);
//        if (!b) {
//            qDebug() << "Can't insert.";
//        } else {
//            qDebug() << "Inserted.";
//        }
//    }
//    if (!a_query.exec("SELECT * FROM my_table")) {
//        qDebug() << "Can't select.";
//        return -2;
//    } else {
//        qDebug() << "Selected";
//    }
//    QSqlRecord rec = a_query.record();
//    int number = 0,
//            age = 0;
//    QString address = "";

//    while (a_query.next()) {
//        number = a_query.value(rec.indexOf("number")).toInt();
//        age = a_query.value(rec.indexOf("age")).toInt();
//        address = a_query.value(rec.indexOf("address")).toString();

//        qDebug() << "number is " << number
//                 << ". age is " << age
//                 << ". address" << address;
//    }
//    //dbase.commit();

//    //dbase.close();

//    QTableWidget tableWidget(4, 4);
//    tableWidget.setItemDelegate(new StarDelegate);
//    tableWidget.setEditTriggers(QAbstractItemView::DoubleClicked
//                                | QAbstractItemView::SelectedClicked);
//    tableWidget.setSelectionBehavior(QAbstractItemView::SelectRows);

//    QStringList headerLabels;
//    headerLabels << "Title" << "Genre" << "Artist" << "Rating";
//    tableWidget.setHorizontalHeaderLabels(headerLabels);

//    populateTableWidget(&tableWidget);

//    tableWidget.resizeColumnsToContents();
//    tableWidget.resize(500, 300);
//    tableWidget.show();

    DownloaderWindow window;
    QObject::connect(&app, SIGNAL(aboutToQuit()), &window, SLOT(onClose()));
    window.show();

    return app.exec();
}



