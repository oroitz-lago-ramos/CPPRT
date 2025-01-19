#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QListView>
#include <QFrame>

class ChatWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ChatWindow(QWidget *parent = nullptr);
    ~ChatWindow();

private slots:
    void on_pushButton_Send_clicked(); // Handles sending messages
    void on_pushButton_Quit_clicked(); // Handles quitting the application
    void onMessageReceived(const QString& message); // Slot to handle incoming messages
    void onDisconnected(); // Slot to handle disconnection from the server

private:
    // UI Components
    QListWidget *listWidget_message_box; // Chat message display area
    QListView *listView_user_online;    // User online display area
    QLineEdit *lineEdit_message_input;  // Input field for typing messages
    QPushButton *pushButton_send;       // Send button
    QPushButton *pushButton_quit;       // Quit button
    QLabel *label;                      // Label for "Message"
    QFrame *frame;                      // Input area frame
};

#endif // CHATWINDOW_H
