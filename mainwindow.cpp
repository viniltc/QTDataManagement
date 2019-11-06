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
     QDomDocument document;
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

            if(!document.setContent(&file,&errorMsg, &errorLine, &errorColumn))
            {


                qDebug () << file<<errorMsg << errorLine << errorColumn;
                qDebug() << "Failed to load the file for reading.";

            }
            file.close();
        }

        // Getting root element
        QDomElement root = document.firstChildElement();

        //retrievelements(QDomElement root, QString tag, QString att)
        //retrievElements(root, "Dorm", "Name");

        qDebug() << "Reading finished";
}
