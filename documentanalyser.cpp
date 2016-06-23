#include <iostream>
#include <QPair>
#include <algorithm>
#include "documentanalyser.h"
#include <QChart>

#include <QBarSet>
#include <QBarSeries>
#include <QBarCategoryAxis>
#include <QChartView>
#include <QMainWindow>

#include <QPieSeries>
#include <QPieLegendMarker>
#include <QPieModelMapper>
#include <QPieSlice>

using namespace QtCharts;

DocumentAnalyser::DocumentAnalyser(bool ordered,bool pie,bool charts, QString regex){
    _regex = regex;
    _ordered = ordered;
    _pie=pie;
    _charts=charts;
}

void DocumentAnalyser::analysis(QString string){
    QStringList _sentences = string.split(QRegExp("["+_sentenceSpace+"]"), QString::SkipEmptyParts);
    QStringList listWords;
    _charNumber=0;
    _wordsNumber=0;
    _sentenesNumber=_sentences.size();
    _hashmap.clear();

    for(int i=0;i<_sentenesNumber;i++){
        listWords=_sentences[i].split(QRegExp("["+_wordsSpace+"]"),QString::SkipEmptyParts);
        _wordsNumber+=listWords.size();
        for(int j=0;j<listWords.size();j++){
            _words.append(listWords[j]);
            _charNumber+=listWords[j].size();
            _hashmap.insert(listWords[j],_hashmap.take(listWords[j])+1);
            if(_regex!= ""){
                if(listWords[j].contains(QRegExp(_regex))){
                    _regexString.insert(listWords[j]);
                }
            }
        }
    }
    for(int i=0;i<string.size();i++){
        _letterMap.insert(string.mid(i,1).replace("\n","\\n"),_letterMap.take(string.mid(i,1).replace("\n","\\n"))+1);
        if(i<(string.size()-1)){
            _doubleMap.insert(string.mid(i,2).replace("\n","\\n"),_doubleMap.take(string.mid(i,2).replace("\n","\\n"))+1);
            if(i<(string.size()-2)){
                _tripleMap.insert(string.mid(i,3).replace("\n","\\n"),_tripleMap.take(string.mid(i,3).replace("\n","\\n"))+1);
            }
        }
    }
}

QString DocumentAnalyser::getAllStatistics()
{
    QString string = DocumentAnalyser::getWordsStatistics();
    string += DocumentAnalyser::getLettersStatistics();
    string += DocumentAnalyser::getDoubleStatistics();
    string += DocumentAnalyser::getTripleStatistics();
    return string;
}

QString DocumentAnalyser::getWordsStatistics(){
    QString stats("Number of lines :");
    stats.append(QString::number(_sentenesNumber));
    stats.append("\n");
    stats.append("Number of words :");
    stats.append(QString::number(_wordsNumber));
    stats.append("\n");
    stats.append("Number of caractere in words :");
    stats.append(QString::number(_charNumber));
    stats.append("\n");

    stats = displayQMap(_hashmap,_wordsNumber,stats);
    return stats;
}

QString DocumentAnalyser::getLettersStatistics(){
    QString string="";

    string.append("Letters Statistics :\n");

    string = displayQMap(_letterMap,_charNumber,string);
    return string;
}

QString DocumentAnalyser::getDoubleStatistics(){
    QString string="";

    string.append("Letters Double Statistics :\n");
    string = displayQMap(_doubleMap,_charNumber-1,string);
    return string;
}

QString DocumentAnalyser::getTripleStatistics(){
    QString string="";

    string.append("Letters Triple Statistics :\n");

    string = displayQMap(_tripleMap,_charNumber-2,string);
    return string;
}

QString DocumentAnalyser::getRegexStatistics(){
    QString stats;
    if(_regex!=""){
        stats.append("Number of words corresponding to the regex :");
        stats.append(QString::number(_regexString.size()));
        stats.append("\n");
        QSetIterator<QString> j(_regexString);
        QString tmp;
        while (j.hasNext()) {
            tmp=j.next();
            stats.append(tmp);
            stats.append("\n");
        }
    }
    return stats;
}

QString DocumentAnalyser::getCSVStatistics(QString string){
    QStringList _sentences = string.split(QRegExp("[\n]"), QString::SkipEmptyParts);
    QStringList listWords;
    QString stats;
    QString tmp;
    int sentencesNumber = _sentences.size();
    int inputNumber = 0;
    _csvmap.clear();
    for(int i=0;i<sentencesNumber;i++){
        listWords=_sentences[i].split(QRegExp("[,]"),QString::SkipEmptyParts);
        if(listWords.at(1) == "K"){
            if(listWords.at(2) == "D"){
                inputNumber++;
                tmp = listWords.at(3);
                if(!_csvmap.contains(tmp)){
                    _csvmap.insert(tmp,1);
                }
                else{
                    _csvmap.insert(tmp,_csvmap.value(tmp)+1);
                }
            }
        }
    }
    stats.append("CSV Statistics, Number of input : ");
    stats.append(QString::number(inputNumber));
    stats.append("\n");

    stats = displayQMap(_csvmap,inputNumber,stats);

    return stats;
}

void DocumentAnalyser::displayGraphics(QMap<QString,int> map, int size,QString title){
    if(_charts){
        QBarSet *set0 = new QBarSet(title);
        QMapIterator<QString, int> i(map);
        QStringList categories;
        int rest;
        while(i.hasNext()){
            i.next();
            if(i.value() > size/_displayLimit){
                *set0 << i.value();
                categories << "'"+i.key()+"'";
            }
            else{
                rest += i.value();
            }
        }
        *set0 << rest;
        categories << "rest";

        QBarSeries *series = new QBarSeries();
        series->append(set0);

        QChart *chart = new QChart();
        chart->addSeries(series);
        chart->setTitle(title);
        chart->setAnimationOptions(QChart::SeriesAnimations);

        QBarCategoryAxis *axis = new QBarCategoryAxis();
        axis->append(categories);
        chart->createDefaultAxes();
        chart->setAxisX(axis, series);

        chart->legend()->setVisible(true);
        chart->legend()->setAlignment(Qt::AlignBottom);

        QChartView *chartView = new QChartView(chart);
        chartView->setRenderHint(QPainter::Antialiasing);
        chartView->show();
    }
}

void DocumentAnalyser::displayPie(QMap<QString,int> map, int size,QString title){
    if(_pie){
       QPieSeries *series = new QPieSeries();
       QMapIterator<QString, int> i(map);
       int rest;
       while(i.hasNext()){
           i.next();
           if(i.value() > size/_displayLimit){
                series->append("'"+i.key()+"'",i.value());
           }
           else{
               rest += i.value();
           }
       }
       //series->append("Rest",rest);

       for(int j=0;j<series->slices().size();j++){
           QPieSlice *slice = series->slices().at(j);
           slice->setLabelVisible();
       }

       QChart *chart = new QChart();
       chart->addSeries(series);
       chart->setTitle(title);
       chart->legend()->hide();

       QChartView *chartView = new QChartView(chart);
       chartView->setRenderHint(QPainter::Antialiasing);
       chartView->show();
    }
}


QString DocumentAnalyser::displayQMap(QMap<QString, int> map, int size,QString title){
    QString stats;
    QMapIterator<QString, int> i(map);
    stats.append(title);
    stats.append("\n");
    if(_ordered){
        QList<QPair<QString,int>> list;
        QPair<QString, int> tmp;
        int j=0;
        while(i.hasNext()){
            i.next();
            list.insert(j,QPair<QString,int>(i.key(),i.value()));
            j++;
        }
        std::sort(list.begin(),list.end(),DocumentAnalyser::sorting);
        QListIterator<QPair<QString,int>> iterator(list);
        while(iterator.hasNext()){
            tmp=iterator.next();
            stats.append("'"+((QPair<QString, int>)tmp).first+"'");
            stats.append("\t");
            stats.append(QString::number(((QPair<QString, int>)tmp).second));
            stats.append("\t");
            stats.append(QString::number(((float)((QPair<QString, int>)tmp).second*100/size)));
            stats.append("\n");
        }
    }
    else{
        while (i.hasNext()) {
            i.next();
            stats.append("'"+i.key()+"'");
            stats.append("\t");
            stats.append(QString::number(i.value()));
            stats.append("\t");
            stats.append(QString::number(((float)i.value()*100/size)));
            stats.append("\n");
        }
    }
    displayGraphics(map,size,title);
    displayPie(map,size,title);
    return stats;
}

bool DocumentAnalyser::sorting(const QPair<QString,int>& e1, const QPair<QString,int>& e2) {
    if(e1.second > e2.second){
        return true;
    }
    if(e1.second == e2.second){
        if(e1.first < e2.first){
            return true;
        }
    }
    return false;
}

