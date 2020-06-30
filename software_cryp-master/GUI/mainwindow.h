#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>

#include <QLineEdit>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

   public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

   signals:
    void finish();

    void setText(QLineEdit *le, QString s);

   private slots:
    void on_cry_algorithm_currentIndexChanged(const QString &arg1);

    void on_cry_operation_enc_toggled(bool checked);

    void on_cry_operation_dec_toggled(bool checked);

    void on_cry_file_remove_clicked();

    void on_cry_file_add_clicked();

    void add_dir_dialog();

    void on_cry_key_in_open_clicked();

    void on_hash_operation_file_clicked();

    void on_hash_operation_string_clicked();

    void on_hash_file_in_open_clicked();

    void on_cry_begin_clicked();

    void on_hash_begin_clicked();

    void enable_tab();

    void setTextFun(QLineEdit *le, QString s);

    void on_gen_pri_open_clicked();

    void on_gen_pub_open_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    void UpdataUI();
};

#endif  // MAINWINDOW_H
