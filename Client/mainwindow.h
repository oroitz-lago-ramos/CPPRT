#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_Login_clicked();
    void onConnectionSuccess(); // Called when connection succeeds
    void onConnectionFailure(); // Called when connection fails

private:
    QString m_pendingUsername; // Store username temporarily
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
