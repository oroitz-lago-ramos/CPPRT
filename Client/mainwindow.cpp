#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "SocketManager.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(SocketManager::instance(), &SocketManager::messageReceived, this, [](const QString& message) {
        QMessageBox::information(nullptr, "Message Received", message);
    });
    connect(SocketManager::instance(), &SocketManager::connected, this, []() {
        qDebug() << "Connected to the server.";
    });
    connect(SocketManager::instance(), &SocketManager::disconnected, this, []() {
        qDebug() << "Disconnected from the server.";
    });
    connect(SocketManager::instance(), &SocketManager::errorOccurred, this, [](const QString& error) {
        qDebug() << "Error: " << error;
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_Login_clicked()
{
    QString username = ui->lineEdit_username->text();
    if(username.isEmpty()){
        QMessageBox::information(this,"Login","Enter a user Name");
    }
    else{
        // Connect to the server when user logs in
        SocketManager::instance()->connectToServer("localhost", 1234);
        SocketManager::instance()->sendMessage(username); // Send username to server as the first message

        // Optionally, notify the user they are logged in
        QMessageBox::information(this, "Login", "Welcome " + username);
    }
}

