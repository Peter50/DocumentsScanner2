#ifndef DOCUMENTANALYSER_H
#define DOCUMENTANALYSER_H

#include <QString>
#include <QSet>
#include <QStringList>
#include <QMap>

class DocumentAnalyser{
public:
    DocumentAnalyser(bool ordered,bool pie, bool charts,QString regex);
    void analysis(QString string);
    QString getAllStatistics();
    QString getWordsStatistics();
    QString getLettersStatistics();
    QString getDoubleStatistics();
    QString getTripleStatistics();
    QString getRegexStatistics();
    QString getCSVStatistics(QString string);
    void displayGraphics(QMap<QString,int> map,int size,QString title);
    void displayPie(QMap<QString,int> map,int size,QString title);

private:
    int _sentenesNumber;
    int _wordsNumber;
    int _charNumber;

    bool _ordered;
    bool _pie;
    bool _charts;

    int _displayLimit=100;

    QString _content;
    QStringList _words;
    QStringList _sentences;

    QString _sentenceSpace=".!?;\n";
    QString _wordsSpace=",\s\u00a0\u202f ";

    QString _regex;
    QSet<QString> _regexString;

    QMap<QString,int> _tripleMap;
    QMap<QString,int> _doubleMap;
    QMap<QString,int> _letterMap;
    QMap<QString,int> _hashmap;
    QMap<QString,int> _csvmap;

    QString displayQMap(QMap<QString,int> map,int size,QString title);
    static bool sorting(const QPair<QString,int>& e1, const QPair<QString,int>& e2);
};

#endif // DOCUMENTANALYSER_H
