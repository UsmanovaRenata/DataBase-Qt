#include "jsonformat.h"

JsonFormat::JsonFormat()
{

}

void JsonFormat::read(QByteArray &file, QSqlTableModel *model)
{
    model->insertRow(1);
    model->setData(model->index(1,0),"w");
    model->submitAll();
}
