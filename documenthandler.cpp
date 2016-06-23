#include <string>
#include <iostream>
#include <QUrl>

#include "documenthandler.h"

#include "textreader.h"
#include "webreader.h"
#include "pdfreader.h"
#include "odtreader.h"

DocumentHandler::DocumentHandler(){

}

DocumentHandler::DocumentHandler(QString filename){
    _filename=filename;
    _extension=filename.split(".",QString::SkipEmptyParts).last();
}

QString DocumentHandler::getAll(){
    /* QUrl * url = new QUrl(_filename);
    if(url->isValid()){
        WebReader reader(_filename);
        return reader.getAll();
    }
    */
    if(_extension == "txt" || _extension == "csv"){
        TextReader reader(_filename);
        return reader.getAll();
    }

    if(_extension == "pdf"){
        PdfReader reader(_filename);
        return reader.getAll();
    }

    if(_extension == "odt"){
        OdtReader reader(_filename);
        return reader.getAll();
    }

    //TODO Others extensions

    return "";
}
