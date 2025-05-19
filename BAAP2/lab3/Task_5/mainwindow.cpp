#include "mainwindow.h"
#include <QFileDialog>
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui_(new Ui::MainWindow) {
    ui_->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui_;
}


void MainWindow::CountFileAndFolders(const QString& folder_path,
                                     long long& count_file,
                                     long long& count_folder) {
    QDir dir(folder_path);
    QFileInfoList list =
        dir.entryInfoList(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot);


    for (const QFileInfo& file_info : list) {
        if (file_info.isDir()) {
            count_folder++;
            CountFileAndFolders(file_info.absoluteFilePath(), count_file,
                                count_folder);
        } else if (file_info.isFile()) {
            count_file++;
        }
    }
}

void MainWindow::on_open_file_button_clicked() {
    QString folder_path = QFileDialog::getExistingDirectory(
        this, tr("Выберите папку"), QDir::homePath(),
        QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);


    long long file_count = 0, folder_count = 0;
    CountFileAndFolders(folder_path, file_count, folder_count);
    ui_->podpapki->setText(QString::number(folder_count));
    ui_->file->setText(QString::number(file_count));
}
