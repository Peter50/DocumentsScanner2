#include "textreader.h"
#include <QTextStream>

TextReader::TextReader(QString filename){
     _file = new QFile(filename);
}

QString TextReader::getAll(){



    QTextStream inputStream(_file);

    if (!_file->open(QIODevice::ReadOnly)){
        return "";
    }

    return inputStream.readAll();
}
