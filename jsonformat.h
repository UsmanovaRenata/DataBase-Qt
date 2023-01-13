#ifndef JSONFORMAT_H
#define JSONFORMAT_H
#include<QFile>
#include<QSqlTableModel>
class JsonFormat
{
public:
    JsonFormat();
    void read(QByteArray &file, QSqlTableModel *model);
};

#endif // JSONFORMAT_H
