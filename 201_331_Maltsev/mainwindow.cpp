#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QPushButton"
#include "QMessageBox"
#include "QRandomGenerator"

#include "QByteArray"
#include "QFile"
#include "QJsonDocument"
#include "QJsonObject"

#include "QDebug"
#include "QByteArray"
#include "QBuffer"
#include "QFile"
#include "QJsonParseError"
#include "QJsonObject"
#include "QJsonArray"
#include "QDir"

#include "QCryptographicHash"


MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::show_pin_check_window() {

    pin_window = new QWidget(); //Создание виджета как окна для ввода пин кода
    pin_window->setGeometry(683, 350, 270, 120);

    QVBoxLayout* layout_pin = new QVBoxLayout;

    QLabel* pin_code_label = new QLabel("Пин код"); //Лейбл для пинкода
    input_pincode = new QLineEdit(); // Инпут для пинкода
    input_pincode->setEchoMode(QLineEdit::Password);

    QPushButton* check_pin_btn = new QPushButton("Вход"); //Кнопка для проверки
    connect(check_pin_btn, SIGNAL(clicked()), this, SLOT(check_pin_code())); //При нажатии на кнопку отправляемся в функцию проверки

    //Добавляем в окно лейбл кнопку и инпут
    layout_pin->addWidget(pin_code_label);
    layout_pin->addWidget(input_pincode);
    layout_pin->addWidget(check_pin_btn);
    pin_window->setLayout(layout_pin);

    pin_window->show();
}

int MainWindow::check_pin_code() {
    const QString orig_code = "1234";
    QString code = input_pincode->text();

    if (orig_code == code) {
        delete[] pin_window;
        this->show_game_window(); //запускаем основное окно
        this->show();
        return 0;

    }
    else {
        QMessageBox::critical(NULL, QObject::tr("Ошибка"), tr("Ошибка ввода пин-кода"));
        return 0;
    }
}


int MainWindow::show_game_window() {


    readJsonFile("D:/201_331_Maltsev/201_331_Maltsev/hero.json");
    add_to_window(current_card);

    //    // Вывод данных
    //    for (const QVector<QString> &heroData : hero_info) {
    //        for (const QString &info : heroData) {
    //            qDebug() << info;
    //        }
    //        qDebug() << "------------";
    //    }
    return 0;
}


int MainWindow::readJsonFile(const QString& filename) {
    // Открытие файла
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Ошибка при открытии файла";
        return 0;
    }

    // Чтение JSON из файла
    QByteArray jsonData = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(jsonData);

    // Проверка на корректность JSON
    if (!doc.isObject()) {
        qDebug() << "Ошибка в структуре JSON";
        return 0;
    }

    QJsonObject json = doc.object();

    // Итерация по каждому герою в JSON
    for (const QString& heroName : json.keys()) {
        QJsonObject hero = json[heroName].toObject();

        QVector<QString> heroData;
        heroData.push_back(hero["Weapon_Type"].toString());
        heroData.push_back(QString::number(hero["Health_Points"].toInt()));
        heroData.push_back(QString::number(hero["View_Range"].toDouble()));
        heroData.push_back(hero["hash"].toString());
        hero_info.push_back(heroData);
    }

    return 0;
}

int MainWindow::add_to_window(int current_card) {

    ui->lineGun->setText(hero_info[current_card][0]);
    ui->lineHealth->setText(hero_info[current_card][1]);
    ui->lineObsor->setText(hero_info[current_card][2]);

    QString str_for_hash = hero_info[current_card][0] + hero_info[current_card][1] + hero_info[current_card][2] + salt;

    QByteArray pin_hash_code_current = QCryptographicHash::hash(QByteArray(str_for_hash.toUtf8()), QCryptographicHash::Sha256).toHex(); // Хэшируем по Sha256

    if (pin_hash_code_current != hero_info[current_card][3].toUtf8()) {
        QMessageBox::critical(NULL, QObject::tr("Ошибка"), tr("Код изменен!!!"));
        QCoreApplication::quit();
        return 0;
    }
    return 0;
}

//int check_sha() {

//}

void MainWindow::on_pushButton_next_clicked()
{
    current_card += 1;
    if (current_card == 3) {
        current_card = 0;
    }

    qDebug() << "current_card" << current_card;
    add_to_window(current_card);

}


void MainWindow::on_pushButton_back_clicked()
{

    current_card -= 1;
    if (current_card == -1) {
        current_card = 2;
    }
    qDebug() << "current_card" << current_card;

    add_to_window(current_card);
}

