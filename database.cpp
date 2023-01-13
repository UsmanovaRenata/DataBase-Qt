#include "database.h"
#include "ui_database.h"

Database::Database(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Database)
{
    ui->setupUi(this);
}

Database::~Database()
{
    delete ui;
    delete model;
    delete query;
}

//создание новой базы

//выбор имени
QString Database::set_db_name()
{
    bool ok;
    QString db_name = QInputDialog::getText(this, tr("Название БД"),
                                             tr("Название:"), QLineEdit::Normal,
                                             tr("Untitled"), &ok);
    if(!ok) return "";
    QString path = "./" + db_name + ".db";
    if(QFileInfo::exists(path) && QFileInfo(path).isFile()){
        QMessageBox::warning(this,"Ошибка","База данных с таким именем существует");
        db_name = set_db_name();
    }
    if (ok && !db_name.isEmpty()){
        ui->db_name->setText(db_name);
    }
    return db_name;
}
//создание соединения бд
void Database::open_db()

{
    QString db_name = set_db_name();
    if(db_name != ""){
    db = QSqlDatabase::addDatabase("QSQLITE");//соединение с бд
    db.setDatabaseName("./" + db_name + ".db");
    }
    if(db.open()){
        qDebug("Successfully opened");
        this->create_table();
    }else{
        qDebug("Error");
        error_message();
    }
}
//создание новой таблицы
void Database::create_table()
{

    query = new QSqlQuery(db); //создание запроса
     if(query->exec("CREATE TABLE student ("
                   "Name VARCHAR(100),"
                   "int integer);"
                   )){
        qDebug("The table was created");
     }
      else{
        qDebug() << query->lastError().text();
     }
    model = new QSqlTableModel;//таблица
    model->setTable("student");
    ui->table->setModel(model);
    ui->table->show();
}


void Database::on_create_triggered()
{
    open_db();
}


//открыть существующую

void Database::read_db()
{
    //выбор файла
    delete model;
    QFile db_file = QFileDialog::getOpenFileName(this,QString("Выбор файла"),QString(),QString("(*.json *.db);;"));
    QFileInfo fileInfo(db_file.fileName());
    QString name(fileInfo.fileName());
    if (!db_file.open(QIODevice::ReadOnly)){
        qDebug("the file cannot be opened");
        error_message();
        return;
    }
    ui->db_name->setText(name.first(name.lastIndexOf(".")));
    //проверка расширения файла
    if(name.right(5) == ".json"){
        qDebug("open json file");
        QByteArray val;
        val = db_file.readAll();
        read_json(val);
        db_file.close();
    }else{
        //если файл расширения .db
        db = QSqlDatabase::addDatabase("QSQLITE");//соединение с бд
        db.setDatabaseName(db_file.fileName());
        model = new QSqlTableModel;
        model->setTable("student");
        ui->table->setModel(model);
        ui->table->show();
    }
}

void Database::read_json(QByteArray &val)
{

}

void Database::error_message()
{
    ui->statusbar->showMessage("Что-то пошло не так :(");
}


void Database::on_open_triggered()
{
    read_db();
}
