#include "Server.h"
#include <QDebug>

Server::Server(QObject* parent) : QObject(parent) {
    tcpServer = new QTcpServer(this);

    // Connect the signal for new connections to the slot
    connect(tcpServer, &QTcpServer::newConnection, this, &Server::onNewConnection);
}

bool Server::startServer(quint16 port) {
    if (!tcpServer->listen(QHostAddress::Any, port)) {
        qDebug() << "Server failed to start: " << tcpServer->errorString();
        return false;
    }
    qDebug() << "Server started on port" << port;
    return true;
}

void Server::onNewConnection() {
    QTcpSocket* clientSocket = tcpServer->nextPendingConnection();
    clients[clientSocket] = "";  // Initialize client with an empty username

    // Connect client-specific signals
    connect(clientSocket, &QTcpSocket::readyRead, this, &Server::onReadyRead);
    connect(clientSocket, &QTcpSocket::disconnected, this, &Server::onClientDisconnected);

    qDebug() << "New client connected: " << clientSocket->peerAddress().toString();
}

void Server::onClientDisconnected() {
    QTcpSocket* clientSocket = qobject_cast<QTcpSocket*>(sender());
    if (clientSocket) {
        qDebug() << "Client disconnected: " << clients[clientSocket];
        clients.remove(clientSocket);  // Remove client from the map
        clientSocket->deleteLater();
    }
}

void Server::onReadyRead() {
    QTcpSocket* clientSocket = qobject_cast<QTcpSocket*>(sender());
    if (clientSocket) {
        QByteArray data = clientSocket->readAll();
        qDebug() << "Received data:" << data;

        // If the username is empty, this means it's the first message (username setting)
        if (clients[clientSocket].isEmpty()) {
            clients[clientSocket] = QString::fromUtf8(data).trimmed();  // Set username
            qDebug() << "Username set for client: " << clients[clientSocket];
        } else {
            // If the client already has a username, broadcast their message
            QString username = clients[clientSocket];
            qDebug() << "Message from " << username << ": " << data;

            // Broadcast the message to all other clients
            for (QTcpSocket* client : clients.keys()) {
                if (client != clientSocket) {
                    // Include username in the message
                    client->write(username.toUtf8() + ": " + data);
                }
            }
        }
    }
}

QStringList Server::getAllUsernames() {
    return clients.values();  // Return a list of all usernames
}
