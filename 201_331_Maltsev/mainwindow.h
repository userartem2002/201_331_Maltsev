#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QSignalMapper"
#include "QListWidgetItem"
#include "QVBoxLayout"
#include "QPushButton"
#include "QMessageBox"
#include "QLabel"
#include "QLineEdit"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    //Переменные для окна ввода пин кода
    QWidget *pin_window;
    QLineEdit *input_pincode;
    void show_pin_check_window();//Функция показа окна для ввода pincode
    QVector<QVector<QString>> hero_info;
    int readJsonFile(const QString &filename);
    QString salt = "12345";

    int show_game_window();
    int add_to_window(int current_card);
    int current_card = 0;
private slots:
    int check_pin_code();
    void on_pushButton_next_clicked();

    void on_pushButton_back_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
