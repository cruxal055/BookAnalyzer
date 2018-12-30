#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "heapsummarizer.h"
#include "myparser.h"
#include <ctime>
#include <cstdlib>
#include <QAction>
#include <QString>
#include <QMessageBox>
#include <QFileDialog>
#include <sstream>
#include <string>

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
    void actionOpen();
    void generatePressed();
    void clearPressed();
    void tabChanged(int index);
    void resetPressed();
    void quickSummarize();

private:
    Ui::MainWindow *ui;
    heap *orchard;
    myParser parser;
    std::clock_t processTimer;
    heapSummarize *summaries;
    vector<word> largest;
    bool documentLoaded;
    double readTime;
    void connectSignalsAndSlots();
    void resetHeapAndSummarizer();
};

#endif // MAINWINDOW_H
