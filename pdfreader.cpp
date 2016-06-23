#include "pdfreader.h"
#include <poppler/qt5/poppler-qt5.h>

PdfReader::PdfReader(){

}

PdfReader::PdfReader(QString filename){
    _content = new QString();
    Poppler::Document * document = Poppler::Document::load(filename);
    Poppler::TextBox * textBox;
    QList<Poppler::TextBox *> list;
    for(int i=0;i<document->numPages();i++){
        list = document->page(i)->textList();
        for(QList<Poppler::TextBox *>::iterator it=list.begin();it!=list.end();it++){
            textBox = *it;
            *_content+=textBox->text();
        }
    }
}

QString PdfReader::getAll(){
    return *_content;
}
