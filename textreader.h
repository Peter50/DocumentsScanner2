#ifndef TEXTREADER_H
#define TEXTREADER_H

#include "documentreader.h"

class TextReader : public virtual DocumentReader{
public:
    TextReader();
    TextReader(QString filename);
    QString getAll();
signals:

public slots:

private:
    QFile * _file;
};

#endif // TEXTREADER_H
