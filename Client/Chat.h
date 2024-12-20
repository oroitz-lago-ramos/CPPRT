#ifndef CHAT_H
#define CHAT_H

#include <QMainWindow>
#include <QPushButton>
#include <QLineEdit>
#include <QListView>
#include <QListWidget>
#include <QLabel>
#include <QFrame>

QT_BEGIN_NAMESPACE
namespace Ui {
class ChatWindow;
}
QT_END_NAMESPACE

class ChatWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ChatWindow(QWidget *parent = nullptr);
    ~ChatWindow();

private slots:
    void on_pushButton_Send_clicked();
    void on_pushButton_Quit_clicked();

private:
    // UI elements
    QPushButton *pushButton_send;
    QPushButton *pushButton_quit;
    QLineEdit *lineEdit_message_input;
    QListView *listView_user_online;
    QListWidget *listWidget_message_box;
    QLabel *label;
    QFrame *frame;
    QPushButton *pushButton; // Inside the frame

    // Pointer to the UI class (for auto-generated UI code, if applicable)
    Ui::ChatWindow *ui;
};

#endif // CHAT_H
