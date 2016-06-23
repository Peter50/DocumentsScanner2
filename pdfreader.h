#ifndef PDFREADER_H
#define PDFREADER_H

#include "documentreader.h"

class PdfReader : public DocumentReader
{
public:
    PdfReader();
    PdfReader(QString filename);
    QString getAll(void);
signals:

public slots:

private:
    QString * _content;
};

#endif // PDFREADER_H
