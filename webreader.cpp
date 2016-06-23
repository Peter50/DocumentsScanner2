#include "webreader.h"

#include <QtNetwork>
#include <iostream>

WebReader::WebReader(void)
{

}

WebReader::WebReader(QString filename)
{
    // TODO Debug
    _content = new QString("");
    QUrl url(filename);
    QNetworkRequest request(url);

    QSslConfiguration config;
    config.setProtocol(QSsl::SslV3);
    request.setSslConfiguration(config);

    QNetworkAccessManager * networkAccessManager = new QNetworkAccessManager;
    QNetworkReply * networkReply = networkAccessManager->get(request);
    connect(networkReply,SIGNAL(finished()),this,SLOT(save()));
}

QString WebReader::getAll(void){
    return *_content;
}

WebReader::~WebReader(){

}

void WebReader::save(void){
    QNetworkReply *r = qobject_cast<QNetworkReply*>(sender());
    QByteArray byteArray = r->readAll();
    _content= new QString(byteArray);
    r->close();
    std::cout<<_content<<std::endl;
}
