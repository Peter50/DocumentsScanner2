#ifndef DOCUMENTHANDLER_H
#define DOCUMENTHANDLER_H

#include <QString>
#include "documentreader.h"

class DocumentHandler
{
public:
    DocumentHandler();
    DocumentHandler(QString filename);
    QString getAll();
signals:

public slots:

private:
    QString _filename;
    QString _extension;
};

#endif // DOCUMENTHANDLER_H
