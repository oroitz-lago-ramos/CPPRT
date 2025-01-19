#include "Chat.h"
#include <QPushButton>
#include <QListView>
#include <QListWidget>
#include <QLineEdit>
#include <QLabel>
#include <QFrame>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QCloseEvent>

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
    listWidget_message_box->setStyleSheet("");
    mainLayout->addWidget(listWidget_message_box);

    // Create and configure the user online list view
    listView_user_online = new QListView(this);
    listView_user_online->setGeometry(820, 10, 261, 421);
    mainLayout->addWidget(listView_user_online);

    // Create the input area (frame)
    frame = new QFrame(this);
    frame->setGeometry(30, 440, 1051, 161);
    frame->setStyleSheet("background-color: rgb(31, 31, 31);");
    frame->setFrameShape(QFrame::StyledPanel);
    frame->setFrameShadow(QFrame::Raised);
    mainLayout->addWidget(frame);

    // Input layout for the frame
    QHBoxLayout *inputLayout = new QHBoxLayout(frame);

    // Create and configure the label
    label = new QLabel("Message", this);
    label->setGeometry(50, 450, 63, 20);
    label->setStyleSheet("color: rgb(255, 255, 255); background-color: rgb(31, 31, 31);");
    inputLayout->addWidget(label);

    // Create and configure the message input line edit
    lineEdit_message_input = new QLineEdit(this);
    lineEdit_message_input->setGeometry(180, 450, 471, 28);
    lineEdit_message_input->setStyleSheet("color: rgb(0, 0, 0);");
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

    // Connect the buttons to their respective slots
    connect(pushButton_send, &QPushButton::clicked, this, &ChatWindow::on_pushButton_Send_clicked);
    connect(pushButton_quit, &QPushButton::clicked, this, &ChatWindow::on_pushButton_Quit_clicked);
}

ChatWindow::~ChatWindow()
{
    // Cleanup UI components
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
    // Add your functionality for the send button here
}

void ChatWindow::on_pushButton_Quit_clicked()
{
    QMessageBox::StandardButton reply = QMessageBox::question(
        this, "Exit Confirmation", "Are you sure you want to quit?",
        QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        close();
    }
}

void ChatWindow::closeEvent(QCloseEvent *event)
{
    emit chatClosed();
    QMainWindow::closeEvent(event);
}
