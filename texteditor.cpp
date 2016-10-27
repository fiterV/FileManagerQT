#include "texteditor.h"
#include "ui_texteditor.h"
#include <map>
#include <vector>
#include <algorithm>

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

void TextEditor::on_pushButton_3_clicked()
{
    QString p = ui->textEdit->toPlainText(), s="";

    std::map<QString, int> m;
    m.clear();

    QStringList xx2 = p.split(QRegExp("\\W+"), QString::SkipEmptyParts);
            //.split("!@#$%^&*()[]:;.,/\></?,{} ~");
    for (int i=0; i<xx2.size(); i++) m[xx2[i]]++;

    /*for (int i=0; i<p.size(); i++){
        QChar c = p[i];
        if (QString("!@#$%^&*()[]:;.></?,{} ").contains(c)) {
            if (s!="") m[s]++;
            s="";
        } else s+=c;
    }*/
    std::vector< std::pair<int, QString> > v;
    for (std::map<QString, int>::iterator it = m.begin(); it!=m.end(); it++){
        v.push_back(std::make_pair(it->second, it->first));
    }
    std::sort(v.begin(), v.end());
    std::reverse(v.begin(), v.end());
    QString result="";
    int xx = (int)v.size();
    qDebug()<<xx;
    for (int i=0; i<std::min(10, (int)v.size()); i++) result+=v[i].second+" "+QString::number(v[i].first)+"\n";



    QMessageBox::information(this, "none", result);
}

void TextEditor::on_pushButton_4_clicked()
{
    QString s = ui->textEdit->toPlainText();
    QString p="";
    QChar pr = s[0];
    s[0] = s[0].toUpper();
    for (int i=1; i<s.size(); i++){
        if (s[i].isLetter()) {
            if (pr=='.' || pr=='!') {
                s[i] = s[i].toUpper();
            }
        }
        if (s[i]!='\n' && s[i]!=' ') pr = s[i];
    }

    ui->textEdit->setPlainText(s);
}

void TextEditor::on_pushButton_5_clicked()
{
    //QApplication::quit();
    close();

}
