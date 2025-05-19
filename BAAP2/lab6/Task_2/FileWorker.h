#ifndef FILEWORKER_H
#define FILEWORKER_H
#include <QCoreApplication>
#include <QFile>
#include <QInputDialog>
#include <QMessageBox>
#include <QStringList>
#include <QTextBrowser>
#include <QTextStream>
#include <fstream>
#include "StructInputDialog.h"
#include "wristWatch.h"

class FileWorker {
   public:
    FileWorker(QTextBrowser*);

    QString inputText;

    const QStringList files = {"ShpakovskeyLab20.txt", "ShpakovskeyLab20_0.txt",
                               "ShpakovskeyLab20_1.txt",
                               "ShpakovskeyLab20_2.bin",
                               "ShpakovskeyLab20_3.txt"};
    void CreateNonExistingFiles();

    void SaveTextToFile(const QString&);
    void LoadTextFromFile(const QString&);

    void SaveArrayToFile(const QString&);
    void LoadArrayFromFile(const QString&);

    void SaveStructToFile(const QString&);
    void LoadStructsFromFile(const QString&);

    void SaveStructToBinaryFile(const QString&);
    void LoadStructsFromBinaryFile(const QString&);

    void SaveSentenceToFile(const QString&);
    void LoadSentencesFromFile(const QString&);

   private:
    WristWatch w;
    StructInputDialog* structDialog;

    QTextBrowser* output;
    QTextStream outputStream;
    QString outputText;
};

#endif	// FILEWORKER_H
