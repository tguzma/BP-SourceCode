#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDialog>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QStackedWidget>
#include <QGraphicsPixmapItem>
#include <QDebug>
#include <QProcess>
#include <QCoreApplication>
#include <QDesktopServices>
#include <QDir>
#include <iostream>
#include <string>
#include "gameinstance.h"
#include "engine.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    GameInstance* currentGame;
    QString path = QDir::currentPath();
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_exitButton_clicked();
    void on_stopButton_clicked();
    void on_newButton_clicked();
    void changeWidgetIndex(int index);
    void announceGameResult(QString result);
    void showAlghoritmNames();
    void on_startPlayingButton_clicked();

    void on_historyButton_clicked();

    void on_backButton_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QGraphicsRectItem *rectangle;
};

#endif // MAINWINDOW_H
