#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "userinputdialog.h"
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintDialog>
#include <QPrinter>
#include <QTextDocument>
#include <QFileDialog>
#include <QStandardPaths>
#include <QDesktopServices>
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initWithStr();
    initWithCode();
    initWithPtr();
    initWithRef();
    input = new UserInputDialog();
    connect(input, &UserInputDialog::inputInit, this, &MainWindow::initUserInput);
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initWithStr()
{
    strInit = {100, 100000.99, 'M', true, {'R', 'o','l','e','x'}, {-1,2,6,9,-6,-3}};
    QString str = QString::number(strInit.numberOfDiamond) + "|" +QString::number(strInit.price, 'f', 2) + "|" + strInit.Model + "|" + (strInit.isexpensivewristwatch ? "true" : "false") + "|" + QString(strInit.brandNAme) + "|";

    for (int i = 0; i < WristWatch::MAX_TIME_AMOUNT; ++i) {
        str += QString::number(strInit.worldTimeOffsets[i]) + (i == WristWatch::MAX_TIME_AMOUNT - 1 ? "" : ", ");
    }

    ui->textBrowser->setText(str);
}

void MainWindow::initWithCode()
{
    codeInit.numberOfDiamond = 25;
    codeInit.Model = 'O';
    codeInit.price = 5000;
    codeInit.isexpensivewristwatch = false;
    char codeInitName[] = "Omega";
    for (int i = 0; i < 6; ++i)
    {
        codeInit.brandNAme[i] = codeInitName[i];
    }
    int codeInitTimeZones[] = {2, 2, 3, 5, 0, -4};
    for (int i = 0; i < WristWatch::MAX_TIME_AMOUNT; ++i)
    {
        codeInit.worldTimeOffsets[i] = codeInitTimeZones[i];
    }

    QString str = QString::number(codeInit.numberOfDiamond) + "|" +
                  QString::number(codeInit.price, 'f', 2) + "|" +
                  codeInit.Model + "|" +
                  (codeInit.isexpensivewristwatch ? "true" : "false") + "|" +
                  QString(codeInit.brandNAme) + "|";

    for (int i = 0; i < WristWatch::MAX_TIME_AMOUNT; ++i)
    {
        str += QString::number(codeInit.worldTimeOffsets[i]) + (i == WristWatch::MAX_TIME_AMOUNT - 1 ? "" : ", ");
    }
    ui->textBrowser_2->setText(str);
}

void MainWindow::initWithPtr()
{
    ptr->Model = 'C';
    ptr->price = 15000.75;
    ptr->numberOfDiamond = 100;
    ptr->isexpensivewristwatch = true;
    char ptrInitName[] = "Cartier";
    for (int i = 0; i < 8; ++i)
    {
        ptr->brandNAme[i] = ptrInitName[i];
    }
    int ptrInitTimeZones[] = {1, 1, 1, 1, 1, 1};
    for (int i = 0; i < WristWatch::MAX_TIME_AMOUNT; ++i)
    {
        ptr->worldTimeOffsets[i] = ptrInitTimeZones[i];
    }

    QString str = QString::number(ptr->numberOfDiamond) + "|" +
                  QString::number(ptr->price, 'f', 2) + "|" +
                  ptr->Model + "|" +
                  (ptr->isexpensivewristwatch ? "true" : "false") + "|" +
                  QString(ptr->brandNAme) + "|";

    for (int i = 0; i < WristWatch::MAX_TIME_AMOUNT; ++i)
    {
        str += QString::number(ptr->worldTimeOffsets[i]) + (i == WristWatch::MAX_TIME_AMOUNT - 1 ? "" : ", ");
    }
    ui->textBrowser_3->setText(str);
}

void MainWindow::initWithRef()
{
    ref.Model = 'T';
    ref.price = 3000.50;
    ref.numberOfDiamond = 10;
    ref.isexpensivewristwatch = false;
    char refInitName[] = "Tag Heuer";
    for (int i = 0; i < 10; ++i)
    {
        ref.brandNAme[i] = refInitName[i];
    }
    int refInitTimeZones[] = {0, 0, 0, 0, 0, 0};
    for (int i = 0; i < WristWatch::MAX_TIME_AMOUNT; ++i)
    {
        ref.worldTimeOffsets[i] = refInitTimeZones[i];
    }

    QString str = QString::number(ref.numberOfDiamond) + "|" +
                  QString::number(ref.price, 'f', 2) + "|" +
                  ref.Model + "|" +
                  (ref.isexpensivewristwatch ? "true" : "false") + "|" +
                  QString(ref.brandNAme) + "|";

    for (int i = 0; i < WristWatch::MAX_TIME_AMOUNT; ++i)
    {
        str += QString::number(ref.worldTimeOffsets[i]) + (i == WristWatch::MAX_TIME_AMOUNT - 1 ? "" : ", ");
    }
    ui->textBrowser_4->setText(str);
}

void MainWindow::initUserInput(WristWatch userInit)
{
    QString str = QString::number(userInit.numberOfDiamond) + "|" +
                  QString::number(userInit.price, 'f', 2) + "|" +
                  userInit.Model + "|" +
                  (userInit.isexpensivewristwatch ? "true" : "false") + "|" +
                  QString(userInit.brandNAme) + "|";

    for (int i = 0; i < WristWatch::MAX_TIME_AMOUNT; ++i)
    {
        str += QString::number(userInit.worldTimeOffsets[i]) + (i == WristWatch::MAX_TIME_AMOUNT - 1 ? "" : ", ");
    }
    ui->textBrowser_5->setText(str);
}

void MainWindow::on_pushButton_print_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this,"Сохранить как PDF",QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/часы.pdf","PDF Files (*.pdf)");

    if(fileName.isEmpty()) return;
    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(fileName);
    printer.setPageSize(QPageSize::A4);
    printer.setPageMargins(QMarginsF(15, 15, 15, 15), QPageLayout::Millimeter);
    QString fullHtml = "<html><body style='font-family:Arial;'>"
                       "<h1>Полные данные о часах</h1>";
    QStringList titles = {"initWithStr", "initWithCode", "initWithPtr", "initWithRef", "Данные введённые пользователем"};

    for(int i = 0; i < 5; ++i) {
        QTextBrowser* browser = findChild<QTextBrowser*>(QString("textBrowser_%1").arg(i+1));
        if(!browser) browser = ui->textBrowser;

        fullHtml += QString("<h2>%1</h2><div style='margin-left:20px;'>%2</div>")
                        .arg(titles.value(i, QString("Данные %1").arg(i+1)))
                        .arg(browser->toHtml());
    }

    fullHtml += "</body></html>";
    QTextDocument doc;
    doc.setHtml(fullHtml);
    doc.setPageSize(printer.pageRect(QPrinter::Point).size());
    doc.print(&printer);
    QDesktopServices::openUrl(QUrl::fromLocalFile(fileName));
}
void MainWindow::on_pushButton_clicked()
{
    if(input) {
        input->setWindowModality(Qt::ApplicationModal);
        input->show();
    }
}
