#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDir>
#include <QTextStream>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    int level;
    int life;
    int current_chapter;
    QStringList chapters;
    QJsonObject content;
//    QJsonObject item;

private slots:
    void NewGame();
    void EndGame();
    void MenuShow();
    void LvlShow();
    void LoadGame();
    void QuoteMaker();
    void CheckResult();
    void NextContent();
};

#endif // MAINWINDOW_H
