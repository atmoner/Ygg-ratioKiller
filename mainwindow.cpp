#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QCoreApplication>
#include <QDebug>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QUrl>
#include <QUrlQuery>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnHello_clicked()
{
    QString info;
    QString info_2;
    QString comboBox;
    QString varUrl;
    QString Gb;
    QTime myTimer;
    QString nMilliseconds;

    // display text message in label
    info = ui->lineEdit->text();
    // ui->lblHello->setText(info);
    info_2 = ui->lineEdit2->text();

    if (ui->comboBox->currentText() == "1 Gb") {
        Gb = "1073741824";
    } else if( ui->comboBox->currentText() == "5 Gb") {

        Gb = "5368709120";
    } else if( ui->comboBox->currentText() == "10 Gb") {

        Gb = "10737418240";
    } else {
        Gb = "0";
    }
    qDebug() << "Debug: " <<Gb;

    // ui->lblHello2->setText(info_2);
    // create custom temporary event loop on stack
    QEventLoop eventLoop;

    // "quit()" the event-loop, when the network request "finished()"
    QNetworkAccessManager mgr;
    QObject::connect(&mgr, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));

    // the HTTP request =)
    varUrl = "http://jack.yggtorrent.com:8080/";
    varUrl += info; //
    varUrl += "/announce?peer_id=";
    varUrl += info_2; //
    varUrl += "&port=6881&uploaded=";
    varUrl += Gb;
    varUrl += "&downloaded=0";
    varUrl += "&left=0&compact=1&numwant=0&key=1859874386&event=stopped&info_hash=%3d1%0a%7d%fd%3d%04%c5%f5%aa%8b%60%f7%e6%ef%3a%c5%07%86%e2";
    QNetworkRequest req(QUrl::fromUserInput(varUrl));
    QNetworkReply *reply = mgr.get(req);
    eventLoop.exec(); // blocks stack until "finished()" has been called

    if (reply->error() == QNetworkReply::NoError) {
        //success
           myTimer.start();
           nMilliseconds = myTimer.elapsed();
        ui->label_4->setText("OKKK");
        qDebug() << "Success" <<varUrl;
        delete reply;
    }
    else {
        //failure
        QPalette palette = ui->label_4->palette();
        palette.setColor(ui->label_4->foregroundRole(), Qt::red);
        ui->label_4->setPalette(palette);
        // ui->label_4->setPixmap(QPixmap::fromImage("/home/atmoner/Bureau/Sign-Error-icon.png"));
        //ui->label_4->setStyleSheet("background-image: url(:/home/atmoner/Bureau/Sign-Error-icon.png);");
        ui->label_4->setText(reply->errorString());
        qDebug() << "Failure" << reply->errorString();
        delete reply;
    }
}
