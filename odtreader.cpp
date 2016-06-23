#include "odtreader.h"
#include <quazip/JlCompress.h>
#include <quazip/quazip.h>
#include <iostream>
#include <string>

OdtReader::OdtReader(QString filename){

    std::cout<<filename.toStdString()<<std::endl;
    JlCompress::extractDir(filename,"./testsdir");
}

QString OdtReader::getAll(){
    return *_content;
}

