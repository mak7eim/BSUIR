#ifndef DIALOGNUMIN_H
#define DIALOGNUMIN_H

#include <QDialog>
#include <QString>

namespace Ui {
class DialogNumIn;
}

class DialogNumIn : public QDialog {
    Q_OBJECT

   public:
    explicit DialogNumIn(QWidget* parent = nullptr);
    ~DialogNumIn();

   private slots:
    void on_lineEdit_editingFinished();

   private:
    Ui::DialogNumIn* ui;

   private:
    int chosen_number = 0;

   public:
    int get_value();
};

#endif	// DIALOGNUMIN_H
