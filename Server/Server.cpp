#include "server.h"
#include <QDebug>

Server::Server(QObject *parent) : QTcpServer(parent) {
    qDebug() << "Server initialized.";
}

void Server::incomingConnection(qintptr socketDescriptor) {
    qDebug() << "Incoming connection with descriptor:" << socketDescriptor;
    QTcpSocket *clientSocket = new QTcpSocket(this);
    if (clientSocket->setSocketDescriptor(socketDescriptor)) {
        clients.append(clientSocket);
        connect(clientSocket, &QTcpSocket::readyRead, this, &Server::onReadyRead);
        connect(clientSocket, &QTcpSocket::disconnected, this, &Server::onClientDisconnected);
        qDebug() << "Client connected successfully.";
    } else {
        qDebug() << "Failed to set socket descriptor.";
        delete clientSocket;
    }
}

void Server::onReadyRead() {
    QTcpSocket *clientSocket = qobject_cast<QTcpSocket*>(sender());
    if (!clientSocket) {
        qDebug() << "Invalid client socket in onReadyRead.";
        return;
    }

    QByteArray data = clientSocket->readAll();
    if (clientUsernames.contains(clientSocket)) {
        // If the username has been set, forward the message to other clients
        QString message = clientUsernames[clientSocket] + ": " + QString::fromUtf8(data);
        qDebug() << "Message received from " << clientUsernames[clientSocket] << ": " << message;

        // Broadcast the message to all other clients
        for (QTcpSocket *socket : clients) {
            if (socket != clientSocket) {
                socket->write(message.toUtf8());
            }
        }
    } else {
        // If no username has been set, treat the data as a username
        QString username = QString::fromUtf8(data).trimmed();
        if (!username.isEmpty()) {
            clientUsernames[clientSocket] = username;
            qDebug() << "Username set for client: " << username;
            clientSocket->write("Welcome, " + username.toUtf8() + "\n");
        } else {
            clientSocket->write("Invalid username.\n");
        }
    }
}

void Server::onClientDisconnected() {
    QTcpSocket *clientSocket = qobject_cast<QTcpSocket*>(sender());
    if (clientSocket) {
        // Remove the client from the list and delete it
        clientUsernames.remove(clientSocket);
        clients.removeAll(clientSocket);
        clientSocket->deleteLater();
        qDebug() << "Client disconnected.";
    } else {
        qDebug() << "Error: Disconnected signal from an invalid socket.";
    }
}
