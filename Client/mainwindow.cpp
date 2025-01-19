#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "SocketManager.h"
#include <QMessageBox>
#include <QDebug>
#include <QCloseEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_isClosed(false) // Initialisation
{
    ui->setupUi(this);
    connect(SocketManager::instance(), &SocketManager::connectedToServer, this, &MainWindow::onConnectionSuccess);
    connect(SocketManager::instance(), &SocketManager::connectionFailed, this, &MainWindow::onConnectionFailure);
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::isClosed() const
{
    return m_isClosed;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    m_isClosed = true;
    QMainWindow::closeEvent(event);
}

void MainWindow::on_pushButton_Login_clicked()
{
    QString username = ui->lineEdit_username->text();
    if (username.isEmpty()) {
        QMessageBox::information(this, "Login", "Enter a user name");
        return;
    }

    m_pendingUsername = username;

    qDebug() << "Attempting to connect...";
    SocketManager::instance()->connectToServer("localhost", 1234);
}

void MainWindow::onConnectionSuccess()
{
    static bool isCalled = false;
    if (isCalled) {
        return;
    }
    isCalled = true;

    qDebug() << "Connection successful. Sending username: " << m_pendingUsername;
    SocketManager::instance()->sendMessage(m_pendingUsername);
    this->close();
}

void MainWindow::onConnectionFailure()
{
    QMessageBox::critical(this, "Error", "Failed to connect to the server. Please try again.");
}
