#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H

#include <QWidget>
#include <QFile>
#include <QSyntaxHighlighter>
#include <QMessageBox>
#include <QDebug>


namespace Ui {
class TextEditor;
}

class TextEditor : public QWidget
{
    Q_OBJECT

public:
    void setPath(QString Path);
    explicit TextEditor(QWidget *parent = 0);
    ~TextEditor();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::TextEditor *ui;
    QString path;
};

#endif // TEXTEDITOR_H
