#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <QMessageBox>

int count_words();
int count_characters();
int count_lines();

char fileName[200];
std::string content;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(800,600);
    ui->lineEdit->hide();
    ui->find_btn->hide();
    ui->find_btn_2->hide();
    ui->textEdit->setReadOnly(true);
    ui->apply_btn->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_13_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Choose"), "", tr("textfile (*.txt)"));
           if (QString::compare(filename, QString()) != 0 )
           {
               std::fstream file;
               std::string name = filename.toUtf8().constData();
               for (int i = 0; i < filename.length(); i++)
                    {
                        fileName[i] = name[i];
                    }
               file.open(fileName, std::ios::in);
                       char ch;
                       file.get(ch);
                       while (!file.eof())
                       {
                           content += ch;
                           file.get(ch);
                       }
                   file.close();
                      ui->frame->hide();
                      QString Qcontent = QString::fromStdString(content);
                      ui->textEdit->setText(Qcontent);
           }
    ui->lines->setText(QString::number(count_lines()));
    ui->words->setText(QString::number(count_words()));
    ui->chars->setText(QString::number(count_characters()));
}


void MainWindow::on_createnew_btn_clicked()
{
    std::fstream file;
    string name = "Untitled.txt";
    for (int i = 0; i < 12; i++)
         {
             fileName[i] = name[i];
         }

    file.open(fileName, std::ios::out);
    file.close();
    ui->frame->hide();
}


void MainWindow::on_addcontent_btn_clicked()
{
    ui->textEdit->setReadOnly(false);

}


void MainWindow::on_apply_btn_clicked()
{
    QString Qtext = ui->textEdit->toPlainText();
    content = Qtext.toUtf8().constData();
    ui->textEdit->setReadOnly(true);
    ui->lines->setText(QString::number(count_lines()));
    ui->words->setText(QString::number(count_words()));
    ui->chars->setText(QString::number(count_characters()));
}


void MainWindow::on_erase_btn_clicked()
{
    ui->textEdit->setText("");
    content = "";
    ui->lines->setText(QString::number(count_lines()));
    ui->words->setText(QString::number(count_words()));
    ui->chars->setText(QString::number(count_characters()));
}

void encryptContent()
{
    string encrypt = "";
    for (char i : content)
    {
        if (i == '\n')
        {
            encrypt += '\n';
        }
        else
        {
            encrypt += char(int(i) + 1);
        }
    }
    content = encrypt;
}

void MainWindow::on_encrypt_btn_clicked()
{
    encryptContent();
    QString Qcontent = QString::fromStdString(content);
    ui->textEdit->setText(Qcontent);
}

void decryptContent()
{
    string decrypt = "";
    for (char i : content)
    {
        if (i == '\n')
        {
            decrypt += '\n';
        }
        else
        {
            decrypt += char(int(i) - 1);
        }
    }
    content = decrypt;
}

void MainWindow::on_decrypt_btn_clicked()
{
    decryptContent();
    QString Qcontent = QString::fromStdString(content);
    ui->textEdit->setText(Qcontent);
}


void MainWindow::on_merge_btn_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Choose"), "", tr("textfile (*.txt)"));
           if (QString::compare(filename, QString()) != 0 )
           {
               std::fstream file;
               std::string name = filename.toUtf8().constData();
                   char ch;
                   file.open(name);
                       file.get(ch);
                       content += '\n';
                       while (!file.eof())
                       {
                           content += ch;
                           file.get(ch);
                       }
                       file.close();

                      QString Qcontent = QString::fromStdString(content);
                      ui->textEdit->setText(Qcontent);
           }
           ui->lines->setText(QString::number(count_lines()));
           ui->words->setText(QString::number(count_words()));
           ui->chars->setText(QString::number(count_characters()));
}

string toLower(string str)
{
    for (int i = 0; i < str.length(); i++)
    {
        str[i] = tolower(str[i]);
    }
    return str;
}

bool find_word(string word)
{
    int count = 0;
    vector<string> splited_words;
    string store_str;
    char lowerStr[2000];
    bool check = false;

    word = toLower(word);

    for (int i = 0; i < content.length(); i++)
    {
        lowerStr[i] = tolower(content[i]);
    }

    for (int i = 0; i < content.length(); i++)
    {
        if (lowerStr[i] != ' ' && lowerStr[i] != '\n')
        {
            store_str += lowerStr[i];
        }
        else
        {
            splited_words.push_back(store_str);
            store_str = "";
        }
    }
    splited_words.push_back(store_str);

    for (int i = 0; i < splited_words.size(); i++)
    {
        if (word == splited_words[i])
        {
            check = true;
            return check;
        }
    }
    return check;
}

void MainWindow::on_find_btn_clicked()
{
    QString Qtext = ui->lineEdit->text();
    string word = Qtext.toUtf8().constData();
    bool isFound = find_word(word);
    QMessageBox msgBox;
    if (word == "")
    {
        msgBox.setText("Write word to find!!");
    }
    else
    {
        if (isFound)
        {
            msgBox.setText("word was found 😍😍😍");
        }
        else
        {
            msgBox.setText("word wasn't found 😢😢😢");
        }
    }
    msgBox.exec();
    ui->lineEdit->clear();
}

int n_WordExist(string word)
{
    int count = 0;
    vector<string> splited_words;
    string store_str;
    char lowerStr[2000];

    word = toLower(word);

    for (int i = 0; i < content.length(); i++)
    {
        lowerStr[i] = tolower(content[i]);
    }

    for (int i = 0; i < content.length(); i++)
    {
        if (lowerStr[i] != ' ' && lowerStr[i] != '\n')
        {
            store_str += lowerStr[i];
        }
        else
        {
            splited_words.push_back(store_str);
            store_str = "";
        }
    }
    splited_words.push_back(store_str);

    for (int i = 0; i < splited_words.size(); i++)
    {
        if (word == splited_words[i])
        {
            count++;
        }
    }
    return count;
}

void MainWindow::on_find_btn_2_clicked()
{
    QString Qtext = ui->lineEdit->text();
    string word = Qtext.toUtf8().constData();
    int count = n_WordExist(word);
    QMessageBox msgBox;
    if (word == "")
    {
        msgBox.setText("Write word to find!!");
    }
    else
    {
        msgBox.setText("The Word \"" + Qtext + "\" Was Found " + QString::number(count) + " Times");
    }
    msgBox.exec();
    ui->lineEdit->clear();
}

void contentToUpper()
{
    for (int i = 0; i < content.length(); i++)
    {
        content[i] = toupper(content[i]);
    }
}

void MainWindow::on_uppercase_btn_clicked()
{
    contentToUpper();
    QString Qcontent = QString::fromStdString(content);
    ui->textEdit->setText(Qcontent);
}

void contentToLower()
{
    content = toLower(content);
}

void MainWindow::on_lowercase_btn_clicked()
{
    contentToLower();
    QString Qcontent = QString::fromStdString(content);
    ui->textEdit->setText(Qcontent);
}

void firstCap()
{
    for (int i = 0; i < content.length(); i++)
    {
        if (content[i - 1] == ' ' || content[i - 1] == '\n' || i == 0)
        {
            content[i] = toupper(content[i]);
        }
        else
        {
            content[i] = tolower(content[i]);
        }
    }
}

void MainWindow::on_cap_btn_clicked()
{
    firstCap();
    QString Qcontent = QString::fromStdString(content);
    ui->textEdit->setText(Qcontent);
}

int count_words()
{
    unsigned count = 0;
    int state = 0, i = 0, out = 0, in = 1;

    while (content[i] != '\0')
    {
        if (content[i] == ' ' || content[i] == '\n' || content[i] == '\t')
            state = out;
        else if (state == out)
        {
            state = in;
            ++count;
        }

        ++i;
    }
    return count;
}

int count_characters()
{
    return content.length();
}

int count_lines()
{

    int count = 1, i = 0;
    while (content[i] != '\0')
    {
        if (content[i] == '\n')
        {
            count++;
        }
        ++i;
    }
    return count;
}

void MainWindow::on_save_btn_clicked()
{
    QString filepath = QFileDialog::getSaveFileName(this, "Choose", fileName, "textfile (*.txt)");
    string name =  filepath.toUtf8().constData();
    for (int i = 0; i < filepath.length(); i++)
    {
        fileName[i] = name[i];
    }
    fstream file;
    file.open(fileName, ios::out);
    for (int i = 0; i < content.length(); i++)
    {
        file << content[i];
    }
    file.close();
}

