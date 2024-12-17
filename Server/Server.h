#ifndef SERVEUR_H
#define SERVEUR_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QList>
#include <QHostAddress>
#include <QHash>

class Server : public QTcpServer {
    Q_OBJECT
public:
    explicit Server(QObject *parent = nullptr);

protected:
    void incomingConnection(qintptr socketDescriptor) override;

private slots:
    void onReadyRead();
    void onClientDisconnected();
    void onUsernameReceived();

private:
    QList<QTcpSocket*> clients;
    QHash<QTcpSocket*, QString> clientUsernames; // Maps client socket to username
};

#endif // SERVEUR_H
