#include "Chat.h"
#include "SocketManager.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>

ChatWindow::ChatWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Set the main window's geometry and style
    this->setGeometry(0, 0, 1092, 602);
    this->setStyleSheet("background-color: rgba(232, 220, 202, 220);");

    // Create the central widget
    QWidget *centralWidget = new QWidget(this);
    this->setCentralWidget(centralWidget);

    // Create the main layout
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    // Create and configure the message box
    listWidget_message_box = new QListWidget(this);
    listWidget_message_box->setGeometry(30, 10, 771, 421);
    listWidget_message_box->setStyleSheet("color: rgb(0, 0, 0);");
    mainLayout->addWidget(listWidget_message_box);

    // Create and configure the user online list view
    listView_user_online = new QListView(this);
    listView_user_online->setGeometry(820, 10, 261, 421);
    mainLayout->addWidget(listView_user_online);

    // Create the input area (frame)
    frame = new QFrame(this);
    frame->setGeometry(30, 440, 1051, 161);
    frame->setStyleSheet("background-color: rgb(31, 31, 31);");
    mainLayout->addWidget(frame);

    // Input layout for the frame
    QHBoxLayout *inputLayout = new QHBoxLayout(frame);

    // Create and configure the label
    label = new QLabel("Message", this);
    label->setGeometry(50, 450, 63, 20);
    label->setStyleSheet("color: rgb(255, 255, 255);");
    inputLayout->addWidget(label);

    // Create and configure the message input line edit
    lineEdit_message_input = new QLineEdit(this);
    lineEdit_message_input->setGeometry(180, 450, 471, 28);
    lineEdit_message_input->setStyleSheet("color: rgb(255, 255, 255);");
    inputLayout->addWidget(lineEdit_message_input);

    // Create and configure the send button
    pushButton_send = new QPushButton("Send", this);
    pushButton_send->setGeometry(670, 450, 83, 29);
    pushButton_send->setStyleSheet("background-color: rgba(232, 220, 202, 220); color: rgb(0, 0, 0);");
    inputLayout->addWidget(pushButton_send);

    // Create and configure the quit button
    pushButton_quit = new QPushButton("Quit", this);
    pushButton_quit->setGeometry(770, 450, 83, 29);
    pushButton_quit->setStyleSheet("background-color: rgba(232, 220, 202, 220); color: rgb(0, 0, 0);");
    inputLayout->addWidget(pushButton_quit);

    // Connect buttons to their respective slots
    connect(pushButton_send, &QPushButton::clicked, this, &ChatWindow::on_pushButton_Send_clicked);
    connect(pushButton_quit, &QPushButton::clicked, this, &ChatWindow::on_pushButton_Quit_clicked);

    // Connect SocketManager signals to ChatWindow slots
    connect(SocketManager::instance(), &SocketManager::messageReceived, this, &ChatWindow::onMessageReceived);
    connect(SocketManager::instance(), &SocketManager::disconnected, this, &ChatWindow::onDisconnected);
}

ChatWindow::~ChatWindow()
{
    delete listWidget_message_box;
    delete listView_user_online;
    delete lineEdit_message_input;
    delete label;
    delete pushButton_send;
    delete pushButton_quit;
    delete frame;
}

void ChatWindow::on_pushButton_Send_clicked()
{
    QString message = lineEdit_message_input->text().trimmed();
    if (!message.isEmpty()) {
        // Send message to server
        SocketManager::instance()->sendMessage(message);

        // Display the sent message in the chat box
        listWidget_message_box->addItem("Me: " + message);

        // Clear the input field
        lineEdit_message_input->clear();
    }
}

void ChatWindow::on_pushButton_Quit_clicked()
{
    QMessageBox::StandardButton reply = QMessageBox::question(
        this, "Exit Confirmation", "Are you sure you want to quit?",
        QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        SocketManager::instance()->disconnectFromServer();
        close();
    }
}

void ChatWindow::onMessageReceived(const QString &message)
{
    // Display received messages in the chat box
    listWidget_message_box->addItem(message);
}

void ChatWindow::onDisconnected()
{
    QMessageBox::warning(this, "Disconnected", "You have been disconnected from the server.");
    close();
}
