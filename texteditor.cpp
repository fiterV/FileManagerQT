#include "texteditor.h"
#include "ui_texteditor.h"

TextEditor::TextEditor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TextEditor)
{
    ui->setupUi(this);

}

TextEditor::~TextEditor()
{
    delete ui;
}

void TextEditor::setPath(QString Path){
    path = Path;
    this->setWindowTitle(path);
    on_pushButton_clicked();
}

void TextEditor::on_pushButton_clicked()
{
    QFile file(path);
    if(file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
      ui->textEdit->setPlainText(file.readAll());
    }

}

void TextEditor::on_pushButton_2_clicked()
{
    QFile file(path);
    if(file.open(QIODevice::WriteOnly|QIODevice::Text))
    {
      file.write(ui->textEdit->toPlainText().toUtf8());
    }

}
