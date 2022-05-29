#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>

using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_13_clicked();

    void on_createnew_btn_clicked();

    void on_addcontent_btn_clicked();

    void on_apply_btn_clicked();

    void on_erase_btn_clicked();

    void on_encrypt_btn_clicked();

    void on_decrypt_btn_clicked();

    void on_merge_btn_clicked();

    void on_find_btn_clicked();

    void on_find_btn_2_clicked();

    void on_uppercase_btn_clicked();

    void on_lowercase_btn_clicked();

    void on_cap_btn_clicked();

    void on_save_btn_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
