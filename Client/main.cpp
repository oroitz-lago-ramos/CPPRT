#include "mainwindow.h"
#include "Chat.h"
#include <QApplication>
#include "mainwindow.h"
#include <QDebug>

#include "mainwindow.h"
#include "Chat.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    ChatWindow c;
    w.show();
    int result = a.exec();
    if (w.isClosed()) {
        c.show();
        result = a.exec();
    }

    return result;
}


