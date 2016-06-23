#ifndef ODTREADER_H
#define ODTREADER_H

#include "documentreader.h"

class OdtReader : public DocumentReader
{
public:
    OdtReader();
    OdtReader(QString filename);
    QString getAll();

signals:

public slots:

private:
    QString * _content;
};

#endif // ODTREADER_H
