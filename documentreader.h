#ifndef DOCUMENTREADER_H
#define DOCUMENTREADER_H
#include <QString>
#include <QFile>
#include <QObject>

class DocumentReader : public QObject{
    public:
        DocumentReader(void){}
        DocumentReader(QString filename){filename=filename;}
        virtual QString getAll(void) = 0;
};
#endif // DOCUMENTREADER_H

