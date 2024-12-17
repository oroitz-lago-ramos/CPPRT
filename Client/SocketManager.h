#ifndef SOCKETMANAGER_H
#define SOCKETMANAGER_H

#include <QObject>
#include <QTcpSocket>

class SocketManager : public QObject
{
    Q_OBJECT

public:
    static SocketManager* instance();
    void connectToServer(const QString& host, quint16 port);
    void sendMessage(const QString& message);
    void disconnectFromServer();

signals:
    void messageReceived(const QString& message);
    void connected();
    void disconnected();
    void errorOccurred(const QString& error);

private slots:
    void onReadyRead();
    void onConnected();
    void onDisconnected();
    void onError(QAbstractSocket::SocketError error);

private:
    explicit SocketManager(QObject *parent = nullptr);
    static SocketManager* m_instance;
    QTcpSocket* m_socket;
};

#endif // SOCKETMANAGER_H
