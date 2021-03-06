#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
     void chooseInputFile();
     void chooseOutputFile();
     void allCheck(bool checked);
     void research();
     void about();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
