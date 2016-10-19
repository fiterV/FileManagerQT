#include "mainwindow.h"
#include "ui_mainwindow.h"




MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QDir mdir;
    foreach (QFileInfo a, mdir.drives()){
        ui->drivesLeft->addItem(a.absoluteFilePath());
        ui->drivesRight->addItem(a.absoluteFilePath());
    }
    modelLeft = new QDirModel(this);
    modelLeft->setReadOnly(false);
    modelLeft->setSorting(QDir::DirsFirst);

    ui->treeLeft->setModel(modelLeft);
    ui->treeLeft->setColumnWidth(0, 250);

    modelRight = new QDirModel(this);
    modelRight->setReadOnly(false);
    modelRight->setSorting(QDir::DirsFirst);

    ui->treeRight->setModel(modelRight);
    ui->treeRight->setColumnWidth(0, 250);


    QGraphicsOpacityEffect *op= new QGraphicsOpacityEffect(ui->treeLeft);
    op->setOpacity(0.3);
    ui->treeLeft->setGraphicsEffect(op);


    QPixmap bkgnd("/home/anon/Downloads/os_x_el_capitan-wallpaper-1366x768.jpg");
    bkgnd = bkgnd.scaled(1366, 768);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);
    //this->setStyleSheet("background: url(\"/home/anon/Downloads/os_x_el_capitan-wallpaper-1366x768.jpg\")");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::refresh(){
    modelLeft->refresh();
    modelRight->refresh();
    ui->treeRight->setModel(modelRight);
    ui->treeLeft->setModel(modelLeft);
}

void MainWindow::on_drivesRight_activated(const QString &arg1)
{
    //modelRight->setRootPath(arg1);
}

void MainWindow::on_drivesLeft_activated(const QString &arg1)
{
   // modelLeft->setRootPath(arg1);
}

void MainWindow::createDirectory(QTreeView *tree, QDirModel *model){
    QModelIndex index = tree->currentIndex();

    if (!index.isValid()) return;
    QString name = QInputDialog::getText(this, "Name", "Enter the name" );

    if (name.isEmpty()) return;
    model->mkdir(index, name);
    refresh();
}

void MainWindow::removeDirectory(QTreeView *tree, QDirModel *model){
    QModelIndex index = tree->currentIndex();
    if (!index.isValid()) return;

    if (model->fileInfo(index).isDir()){
           model->rmdir(index);
    } else model->remove(index);
    refresh();
}

void MainWindow::on_pushButton_clicked()
{
    createDirectory(ui->treeLeft, modelLeft);
}

void MainWindow::on_pushButton_2_clicked()
{
    removeDirectory(ui->treeLeft, modelLeft);
}
void MainWindow::on_pushButton_3_clicked()
{
    createDirectory(ui->treeRight, modelRight);
}
void MainWindow::on_pushButton_4_clicked()
{
    removeDirectory(ui->treeRight, modelRight);
}

void MainWindow::openFile(QTreeView *tree, QDirModel *model){
    QModelIndexList list = tree->selectionModel()->selectedIndexes();

    if (list.size()==0) return void(QMessageBox::warning(this, "Warning", "You have to pick up the file"));
    QModelIndex index = list[0];
    QString file_path = model->filePath(index);
    QFileInfo *pp = new QFileInfo(file_path);

    if (pp->isDir()) return void(QMessageBox::warning(this, "Warning", "You have to pick up the file"));

    QMessageBox::StandardButton x = QMessageBox::question(this, "ask","Do you want to use standart program?", QMessageBox::Yes|QMessageBox::No);

    if (x==QMessageBox::Yes){
         QProcess *process = new QProcess(this);
         process->start("xdg-open", QStringList() << file_path);
    } else
      {
        TextEditor *xss = new TextEditor();
        xss->setPath(file_path);

        xss->show();
      }
}


void MainWindow::createFile(QTreeView *tree, QDirModel *model){
    QModelIndexList list = tree->selectionModel()->selectedIndexes();
    if (list.isEmpty()) return;

    QString name = QInputDialog::getText(this, "Name", "Enter the name of file that you want to create" );
    if (name.isEmpty()) return;


    QModelIndex index = list[0];
    QString file_path = model->filePath(index);
    QFileInfo *x = new QFileInfo(file_path);
    if (x->isDir()) {
        file_path+="/"+name;
        QFile file(file_path);
        file.open(QIODevice::ReadWrite | QIODevice::Text);
        QTextStream stream(&file);
        stream<<"";
        file.close();

    } else
    {
        qDebug() << "It's not a directory , it's file\n";
    }
    refresh();
}

void MainWindow::on_actionOpen_triggered()
{
    openFile(ui->treeLeft, modelLeft);
}

void MainWindow::on_actionOpen_Right_triggered()
{
    openFile(ui->treeRight, modelRight);
}

void MainWindow::on_pushButton_5_clicked()
{
    createFile(ui->treeLeft, modelLeft);
}

void MainWindow::on_pushButton_6_clicked()
{
    createFile(ui->treeRight, modelRight);
}
