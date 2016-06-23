#ifndef WEBREADER_H
#define WEBREADER_H

#include "documentreader.h"
#include <QObject>

class WebReader : public DocumentReader
{
    Q_OBJECT

public:
    WebReader();
    WebReader(QString filename);
    QString getAll();
    ~WebReader();
signals:

public slots:
    void save();

private:
    QString * _content;
};

#endif // WEBREADER_H
