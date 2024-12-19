#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "SocketManager.h"
#include <QMessageBox>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Connect signals from SocketManager
    connect(SocketManager::instance(), &SocketManager::connectedToServer, this, &MainWindow::onConnectionSuccess);
    connect(SocketManager::instance(), &SocketManager::connectionFailed, this, &MainWindow::onConnectionFailure);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_Login_clicked()
{
    QString username = ui->lineEdit_username->text();
    if (username.isEmpty()) {
        QMessageBox::information(this, "Login", "Enter a user name");
        return;
    }

    m_pendingUsername = username; // Store the username temporarily

    qDebug() << "Attempting to connect...";
    SocketManager::instance()->connectToServer("localhost", 1234);
}

void MainWindow::onConnectionSuccess()
{
    qDebug() << "Connection successful. Sending username: " << m_pendingUsername;

    // Send username to the server
    SocketManager::instance()->sendMessage(m_pendingUsername);

    QMessageBox::information(this, "Login", "Welcome " + m_pendingUsername);

    // Transition to the chat page or enable chat UI
    // Example: emit signal or call method to change page
}

void MainWindow::onConnectionFailure()
{
    QMessageBox::critical(this, "Error", "Failed to connect to the server. Please try again.");
}
