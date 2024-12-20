#include "mainwindow.h"
#include "Chat.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    ChatWindow c;
    c.show();
    w.show();
    return a.exec();
}
