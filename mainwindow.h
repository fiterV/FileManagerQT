#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileSystemModel>
#include <QDebug>
#include <QDir>
#include <QtCore>
#include <QtGui>
#include <QDialog>
#include <QInputDialog>
#include <QDirModel>
#include <QMessageBox>
#include "texteditor.h"
#include <QGraphicsEffect>
#include <QAbstractTableModel>
#include <QTreeView>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_drivesRight_activated(const QString &arg1);

    void on_drivesLeft_activated(const QString &arg1);


    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_actionOpen_triggered();


    void on_actionOpen_Right_triggered();

    void on_pushButton_5_clicked();
    void createDirectory(QTreeView *tree, QDirModel *model);
    void removeDirectory(QTreeView *tree, QDirModel *model);

private:
    Ui::MainWindow *ui;
    //QFileSystemModel
    QDirModel *modelLeft, *modelRight;
    void refresh();
};

#endif // MAINWINDOW_H
