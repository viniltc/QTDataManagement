#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDomDocument>
#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QtXml>

void retrievElements(QDomElement root, QString tag, QString att)
{
    QDomNodeList nodes = root.elementsByTagName(tag);

    qDebug() << "# nodes = " << nodes.count();
    for(int i = 0; i < nodes.count(); i++)
    {
        QDomNode elm = nodes.at(i);
        if(elm.isElement())
        {
            QDomElement e = elm.toElement();
            qDebug() << e.attribute(att);
        }
    }
}
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    stagetwonew = new StageTwoNew(this);
    stagetwonew-> show();
}

void MainWindow::on_pushButton_2_clicked()
{
     QDomDocument domDocument;
     QString  errorMsg;
     int errorLine,errorColumn;


         QString path = QCoreApplication::applicationDirPath()+"/data/";
         QString xmlerror;

         QString filename = QFileDialog::getOpenFileName(this, ("Open file"), path, "Xml files (*.xml)");

        // Open a file for reading
        QFile file(filename);
        if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {

            qDebug() << "Failed to open the file for reading.";

        }


        else
        {
            // loading

            if(!domDocument.setContent(&file,&errorMsg, &errorLine, &errorColumn))
            {


                qDebug () << file<<errorMsg << errorLine << errorColumn;
                qDebug() << "Failed to load the file for reading.";

            }
            file.close();
        }



        qDebug() << "Reading finished";




         domDocument.setContent(&file);
        QDomElement topElement = domDocument.documentElement();
       QDomNode domNode = topElement.elementsByTagName("Name").at(0).firstChild();

       QString name = topElement.elementsByTagName("Name").at(0).firstChild().nodeValue();
       QString sname = topElement.elementsByTagName("Surname").at(0).firstChild().nodeValue();
       QString note = topElement.elementsByTagName("Clinician_Note").at(0).firstChild().nodeValue();

        qDebug()<<topElement.elementsByTagName("Name").at(0).firstChild().nodeValue();
        qDebug()<<topElement.elementsByTagName("Surname").at(0).firstChild().nodeValue();
        qDebug()<<topElement.elementsByTagName("Patient_ID").at(0).firstChild().nodeValue();
        qDebug()<<topElement.elementsByTagName("Date").at(0).firstChild().nodeValue();
        qDebug()<<topElement.elementsByTagName("Clinician_Note").at(0).firstChild().nodeValue();


        emit editdetails(name, sname, note);
//        modify_window = new MainWindow(this);
//        modify_window-> show();

//        while (!domNode.isNull())
//         {
//            QDomElement domElement = domNode.toElement();
//             if (!domElement.isNull())
//                {
//                 qDebug()<<"Tag name"<<topElement.tagName();
//                 qDebug()<<topElement.text();
//               //  qDebug()<<domElement.toString;
//                }
//          domNode = domNode.nextSibling();
//         }




//         <!DOCTYPE detailsentry>
//         <subject_details>
//          <Name>Pete</Name>
//          <Surname>Batty</Surname>
//          <Patient_ID>GH34TRM</Patient_ID>
//          <Date>06/11/2019 16:00</Date>
//          <Clinician_Note>test note to display</Clinician_Note>
//         </subject_details>

}
