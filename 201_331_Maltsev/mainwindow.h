#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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
    QVector<QVector<QString>> hero_info; //Вектор, который хранит данные о персонажей
    int readJsonFile(const QString &filename);//Функция считывания файла
    QString salt = "12345"; //Соль

    int show_game_window();//Отображение основного аккаунта
    int add_to_window(int current_card);//Функция добавление данные в окно
    int current_card = 0;//переменная которая отвечает за номер карточки
private slots:
    void on_pushButton_next_clicked();//Сигнал на кнопку вперед
    void on_pushButton_back_clicked();//Сигнал на кнопку назад
    int check_pin_code();//Функция проверки пинкода


private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
