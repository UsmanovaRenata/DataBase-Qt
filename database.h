#ifndef DATABASE_H
#define DATABASE_H
#include "jsonformat.h"
#include <QMainWindow>
#include<QSqlDatabase>
#include<QSqlQuery>
#include<QFileDialog>
#include<QFile>
#include <QSqlTableModel>
#include<QTableView>
#include <QSqlError>
#include<QInputDialog>
#include <QFileInfo>
#include <QMessageBox>
#include <QJsonObject>
#include <QSqlRecord>
QT_BEGIN_NAMESPACE
namespace Ui { class Database; }
QT_END_NAMESPACE

class Database : public QMainWindow
{
    Q_OBJECT

public:
    Database(QWidget *parent = nullptr);
    ~Database();
    QSqlTableModel *model;

private slots:
    void on_open_triggered();
    void on_create_triggered();
private:
    Ui::Database *ui;
    QSqlDatabase db;
    QSqlQuery *query;
    void read_json(QByteArray &val);
    void open_db();
    void read_db();
    void create_table();
    void error_message();
    QString set_db_name();

};
#endif // DATABASE_H
