#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("EDITOR'S DREAM - HEAP EDITION");
    orchard = new heap[26];
    summaries = new heapSummarize[26];
    documentLoaded = false;
    connectSignalsAndSlots();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete [] orchard;
    delete [] summaries;
    largest.clear();
}

void MainWindow::connectSignalsAndSlots()
{
    connect(ui->actionOpen_File,SIGNAL(triggered(bool)),this,SLOT(actionOpen()));
    connect(ui->actionGenerateReport,SIGNAL(triggered(bool)),this,SLOT(generatePressed()));
    connect(ui->clearSummary,SIGNAL(pressed()),this,SLOT(clearPressed()));
    connect(ui->tabSelections,SIGNAL(currentIndexChanged(int)),this,SLOT(tabChanged(int)));
    connect(ui->resetButton,SIGNAL(pressed()),this,SLOT(resetPressed()));
    connect(ui->quickSummary,SIGNAL(pressed()),this,SLOT(quickSummarize()));
}

void MainWindow::actionOpen()
{
    string fileName = (QFileDialog::getOpenFileName(this,"Open File","/home","Text Files *.txt")).toStdString();
    if(documentLoaded)
    {
        for(size_t i = 0; i < 26; ++i)
            orchard[i].reset();
        parser.reset();
        summaries->reset();
        largest.clear();
        documentLoaded = false;
        QMessageBox::information(this,"SUCCESS","Loaded document contents successfully erased!");
    }
    if(fileName.empty())
    {
        QMessageBox::warning(this,"WARNING","Empty file name!");
        return;
    }
    processTimer = clock();
    parser.parse(fileName,orchard);
    readTime = (clock() - processTimer) / (CLOCKS_PER_SEC/1000);
    QMessageBox::information(this,"SUCCESS","File Successfully Read in " + QString::number(readTime) + " ms!");
    documentLoaded = true;
    for(int i = 25; i >= 0; --i)
    {
        summaries[i].createReport(orchard,i);
        summaries[i].getTopTen(largest);
    }
    std::sort(largest.begin(),largest.end(),[](word &x, word &y)
    {
        return x.occurences > y.occurences;
    });
}

void MainWindow::generatePressed()
{
    if(documentLoaded)
    {
        QString fileName = QFileDialog::getSaveFileName((QWidget*)NULL,"Open File",QString());
        ofstream report(fileName.toStdString());
        report<<"TEXT ANALYSIS REPORT"<<endl;
        parser.printInfo(report);
        report<<"FLESSCH READING EASE: "<<parser.getReadingEase()<<endl;
        report<<"FLESCH-KINCAID READING LEVEL: "<<parser.getReadingLevel()<<endl;
        report<<"TOTAL DOCUMENT PROCESSING TIME: "<<readTime<<" milliseconds"<<endl<<endl;
        report<<"TOP TEN WORDS"<<endl;
        for(int i = 0; i < 10; ++i)
            report<<i+1<<") "<<*largest[i].data<<" with: "<<largest[i].occurences<<endl;
        report<<endl;
        for(int i = 25; i >= 0; --i)
        {
            report<<(char)(122-i)<<" words in text"<<endl<<endl;
            report<<summaries[i];
        }
        report.close();
        QMessageBox::information(this,"SUCCESS","Report successfully generated!");
    }
    else
        QMessageBox::warning(this,"WARNING","Please load in a document first!");
}

void MainWindow::clearPressed()
{
    ui->summaryBox->clear();
}

void MainWindow::tabChanged(int index)
{
    ui->summaryBox->clear();
    if(documentLoaded)
    {
        if(!index)
            QMessageBox::warning(this,"WARNING","Please select an alphabetical character!");
        else
        {
            ui->summaryBox->append(ui->tabSelections->currentText() + " words in text");
            summaries[-index+26].print(ui->summaryBox);
        }
    }
    else
        QMessageBox::warning(this,"WARNING","Please load in a document first!");
}

void MainWindow::resetPressed()
{
    for(size_t i = 0; i < 26; ++i)
        orchard[i].reset();
    parser.reset();
    summaries->reset();
    largest.clear();
    documentLoaded = false;
    QMessageBox::information(this,"SUCCESS","Loaded document contents successfully erased!");
}

void MainWindow::quickSummarize()
{
    if(documentLoaded)
    {
        ui->summaryBox->clear();
        int words, sentences, syllables, lines, paragraphs;
        parser.getInfo(words,sentences,syllables,paragraphs,lines);
        ui->summaryBox->append("QUICK SUMMARY");
        ui->summaryBox->append("WORDS: " + QString::number(words));
        ui->summaryBox->append("SENTENCES: " + QString::number(sentences));
        ui->summaryBox->append("SYLLABLES: " + QString::number(syllables));
        ui->summaryBox->append("LINES: " + QString::number(lines));
        ui->summaryBox->append("PARAGRAPHS: " + QString::number(paragraphs));
        ui->summaryBox->append("FLESCH READING EASE: " + QString::number(parser.getReadingEase()));
        ui->summaryBox->append("FLESCH-KINCAID READING LEVEL: " + QString::number(parser.getReadingLevel()));
        ui->summaryBox->append("TOTAL DOCUMENT PROCESSING TIME: " + QString::number(readTime) + "ms \n");
        ui->summaryBox->append("TOP TEN MOST FREQUENT WORDS");
        for(int i = 0; i < 10; ++i)
            ui->summaryBox->append(QString::number(i+1) + ") " +
                                   QString::fromStdString(*largest[i].data) + " with " +
                                   QString::number(largest[i].occurences));
    }
    else
        QMessageBox::warning(this,"WARNING","Please load in a document first!");
}
