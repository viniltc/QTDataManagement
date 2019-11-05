#include "stagetwonew.h"
#include "ui_stagetwonew.h"
#include "mainwindow.h"
#include <QDomDocument>
#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QtXml>

StageTwoNew::StageTwoNew(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::StageTwoNew)
{
    ui->setupUi(this);
     QDir dir(QCoreApplication::applicationDirPath());
     QString location = dir.relativeFilePath("./PatientDat");
     qDebug()<<"This is the location::"<<location;
      //QString path = location+"/"+filename+".xml";
//small change
// one more
// more
}

StageTwoNew::~StageTwoNew()
{
    delete ui;
}

void StageTwoNew::on_pushButton_2_clicked()
{
//    hide();
//    StageOneMain *back =new StageOneMain(this);
//    back ->show();
     hide();
     MainWindow().show();
}

void StageTwoNew::on_pushButton_clicked()
{


   QString filename = ui->lineEdit_3->text();
  // QString location = dir.relativeFilePath("../PatientData");
   QString path = QCoreApplication::applicationDirPath()+"/"+filename+".xml";
   QFile file(path);


//    QString filename = QFileDialog::getSaveFileName(this, "Save Xml", location.append(ui->lineEdit_3->text()), "Xml files (*.xml)");
//    qDebug()<<"file name"<<filename;
//    QFile file(filename);
    if(!file.open(QFile::WriteOnly | QFile::Text))
    {
        qDebug () << "Error saving XML file...."; // replace this with Q Messange box later!!!!!!!!!!!
        file.close();
        return;
    }

    QDomDocument xml("tetragrip");

    QDomElement root = xml.createElement("subject details");
    root.setAttribute("catagory","run session");
    xml.appendChild(root);

    QDomElement tagName = xml.createElement("Name");
    root.appendChild(tagName);
    QDomText textName = xml.createTextNode(ui->lineEdit->text());
    tagName.appendChild(textName);

    QDomElement tagSname = xml.createElement("Surname");
    root.appendChild(tagSname);
    QDomText textSname = xml.createTextNode(ui->lineEdit_2->text());
    tagSname.appendChild(textSname);

    QDomElement tagPID = xml.createElement("Patient ID");
    root.appendChild(tagPID);
    QDomText textPID = xml.createTextNode(ui->lineEdit_3->text());
    tagPID.appendChild(textPID);

    QDomElement tagDateTime = xml.createElement("Date");
    root.appendChild(tagDateTime);
    QDomText textDateTime = xml.createTextNode(ui->dateTimeEdit->text());
    tagDateTime.appendChild(textDateTime);

    QDomElement tagNote = xml.createElement("Clinician Note");
    root.appendChild(tagNote);
    QDomText textNote = xml.createTextNode(ui->textEdit->toPlainText());
    tagNote.appendChild(textNote);


    QTextStream output(&file);
    output << xml.toString();

    file.close();
}
