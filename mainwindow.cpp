#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->menu->setFlat(true);

//Загрузка контента
    chapters = QString("lvl_1,lvl_2,lvl_3,lvl_4,").split(",");
    QFile file(QDir::homePath() + QDir::separator() + "boa/content_json");
    QTextStream *in = new QTextStream(&file);
    QString val;
    if (file.open(QIODevice::ReadOnly)) {
        val = in->readAll();
    }
    file.close();
    content = QJsonDocument::fromJson(val.toUtf8()).object();
    qDebug()<<content;
    NewGame();
}

void MainWindow::NewGame() {
//Обнуляем всё
    level = 0;
    life = 3;
    current_chapter = -1;
    ui->hero->hide();
    ui->quote->hide();
    ui->level->setPixmap(QPixmap(":/menu/"+QString::number(level)+".png"));

//Соединяем кнопки
    connect (ui->butt_1, SIGNAL(clicked()), this, SLOT(CheckResult()));
    connect (ui->butt_2, SIGNAL(clicked()), this, SLOT(CheckResult()));
    connect (ui->butt_3, SIGNAL(clicked()), this, SLOT(CheckResult()));
    connect (ui->butt_4, SIGNAL(clicked()), this, SLOT(CheckResult()));
    connect (ui->head, SIGNAL(clicked()), this, SLOT(NextContent()));
    connect (ui->new_game, SIGNAL(triggered()), this, SLOT(NewGame()));
    connect (ui->see_lvl, SIGNAL(triggered()), this, SLOT(LvlShow()));
    connect (ui->menu, SIGNAL(clicked()), this, SLOT(MenuShow()));
    connect (ui->go_away, SIGNAL(clicked()), this, SLOT(close()));
    connect (ui->new_game_but, SIGNAL(clicked()), this, SLOT(LvlShow()));

    MenuShow();

//грузим контент
//    NextContent();
}

void MainWindow::CheckResult() {
    QJsonObject item = content.value(chapters.at(current_chapter)).toObject();
    if (-1 != current_chapter) {
//Проверка предыдущего результата
    QPushButton *pressedButton = qobject_cast<QPushButton *> (QObject::sender());
    if (pressedButton)
        if (pressedButton->text() == item["answer"].toString()) {
            level ++;
            ui->level->setPixmap(QPixmap(":/menu/"+QString::number(level)+".png"));
        }
        else {
            life--;
            switch (life) {
//                case -1: EndGame(); break;
                case -1: MenuShow(); break;
                case 0: ui->heart_3->setPixmap(QPixmap(":/menu/resourse/hrt1_dis.png")); break;
                case 1: ui->heart_2->setPixmap(QPixmap(":/menu/resourse/hrt2_dis.png")); break;
                case 2: ui->heart_1->setPixmap(QPixmap(":/menu/resourse/hrt3_dis.png")); break;
                }
        }
    }
//Показ экрана с ответом
    ui->butt_1->setDisabled(true);
    ui->butt_2->setDisabled(true);
    ui->butt_3->setDisabled(true);
    ui->butt_4->setDisabled(true);
    ui->head->setIcon(QIcon(":/boa/resourse/udaf2.png"));
    ui->med->setPixmap(QPixmap(":/boa/med.png"));
    ui->ans->setPixmap(QPixmap(item["image_answer"].toString()));
    ui->ans->show();
}

void MainWindow::NextContent() {
    ui->logo->hide();
    ui->new_game_but->hide();
    ui->go_away->hide();
    ui->butt_1->setDisabled(false);
    ui->butt_2->setDisabled(false);
    ui->butt_3->setDisabled(false);
    ui->butt_4->setDisabled(false);
    ui->med->setPixmap(QPixmap(":/boa/green.png"));
    ui->ans->hide();
    current_chapter++;
    if (current_chapter == chapters.length()) MenuShow();
    ui->head->setIcon(QIcon(":/boa/resourse/udaf.png"));
    QJsonObject item = content.value(chapters.at(current_chapter)).toObject();
    qDebug()<<item["image"].toString();
    qDebug()<<item["button_1"].toString();
    ui->quizz->setPixmap(QPixmap(item["image"].toString()));
    ui->butt_1->setStyleSheet("border-image: url("+item["button_1"].toString()+") stretch;");
    ui->butt_2->setStyleSheet("border-image: url("+item["button_2"].toString()+") stretch;");
    ui->butt_3->setStyleSheet("border-image: url("+item["button_3"].toString()+") stretch;");
    ui->butt_4->setStyleSheet("border-image: url("+item["button_4"].toString()+") stretch;");
}
void MainWindow::MenuShow() {
    ui->butt_1->hide();
    ui->butt_2->hide();
    ui->butt_3->hide();
    ui->butt_4->hide();
    ui->head->hide();
    ui->tail->hide();
    ui->ans->hide();
    ui->ans_1->hide();
    ui->ans_2->hide();
    ui->ans_3->hide();
    ui->ans_4->hide();
    ui->med->hide();
    ui->lvl_0->hide();
    ui->lvl_1->hide();
    ui->lvl_2->hide();
    ui->lvl_3->hide();
    ui->heart_1->hide();
    ui->heart_2->hide();
    ui->heart_3->hide();
    ui->level->hide();
    ui->menu->hide();
    ui->logo->show();
    ui->new_game_but->show();
    ui->go_away->show();
}

void MainWindow::LvlShow() {
    ui->lvl_0->show();
    ui->lvl_1->show();
    ui->lvl_2->show();
    ui->lvl_3->show();
    ui->logo->hide();
    ui->go_away->hide();
    ui->new_game_but->hide();
    connect (ui->lvl_0, SIGNAL(clicked()), this, SLOT(LoadGame()));
    connect (ui->lvl_1, SIGNAL(clicked()), this, SLOT(LoadGame()));
    connect (ui->lvl_2, SIGNAL(clicked()), this, SLOT(LoadGame()));
    connect (ui->lvl_3, SIGNAL(clicked()), this, SLOT(LoadGame()));
}

void MainWindow::LoadGame() {
    QPushButton *pressedButton = qobject_cast<QPushButton *> (QObject::sender());
    if (pressedButton)
        if ("0" == pressedButton->text() || "1" == pressedButton->text()
                    || "2" == pressedButton->text() || "3" == pressedButton->text())
        current_chapter = pressedButton->text().toInt()-1;

    ui->butt_1->show();
    ui->butt_2->show();
    ui->butt_3->show();
    ui->butt_4->show();
    ui->head->show();
    ui->tail->show();
    ui->ans->show();
    ui->ans_1->show();
    ui->ans_2->show();
    ui->ans_3->show();
    ui->ans_4->show();
    ui->med->show();
    ui->lvl_0->show();
    ui->lvl_1->show();
    ui->lvl_2->show();
    ui->lvl_3->show();
    ui->heart_1->show();
    ui->heart_2->show();
    ui->heart_3->show();
    ui->level->show();
    ui->menu->show();
    ui->lvl_0->hide();
    ui->lvl_1->hide();
    ui->lvl_2->hide();
    ui->lvl_3->hide();

    NextContent();
}

void MainWindow::EndGame() {

}

void MainWindow::QuoteMaker() {

}

MainWindow::~MainWindow()
{
    delete ui;
}
