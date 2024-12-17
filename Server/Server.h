#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QMap>

class Server : public QObject {
    Q_OBJECT

public:
    explicit Server(QObject* parent = nullptr);
    bool startServer(quint16 port);

private slots:
    void onNewConnection();
    void onClientDisconnected();
    void onReadyRead();

private:
    QTcpServer* tcpServer;               // The TCP server
    QMap<QTcpSocket*, QString> clients; // Map of connected clients to usernames
};

#endif // SERVER_H
