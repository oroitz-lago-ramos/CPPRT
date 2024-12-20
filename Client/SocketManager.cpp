#include "SocketManager.h"
#include <QDebug>

SocketManager* SocketManager::m_instance = nullptr;

SocketManager::SocketManager(QObject *parent)
    : QObject(parent), m_socket(new QTcpSocket(this))
{
    connect(m_socket, &QTcpSocket::readyRead, this, &SocketManager::onReadyRead);
    connect(m_socket, &QTcpSocket::connected, this, &SocketManager::onConnected);
    connect(m_socket, &QTcpSocket::disconnected, this, &SocketManager::onDisconnected);
    connect(m_socket, &QTcpSocket::errorOccurred, this, &SocketManager::onError);
}

SocketManager* SocketManager::instance()
{
    if (!m_instance) {
        m_instance = new SocketManager();
    }
    return m_instance;
}

void SocketManager::sendMessage(const QString& message)
{
    if (m_socket->state() == QTcpSocket::ConnectedState) {
        m_socket->write(message.toUtf8());
    }
}

void SocketManager::disconnectFromServer()
{
    m_socket->disconnectFromHost();
}

void SocketManager::onReadyRead()
{
    QByteArray data = m_socket->readAll();
    emit messageReceived(QString::fromUtf8(data));
}

void SocketManager::onDisconnected()
{
    emit disconnected();
}


void SocketManager::connectToServer(const QString &host, quint16 port)
{
    if (m_socket->state() == QAbstractSocket::ConnectedState) {
        emit connectedToServer(); // Already connected
        return;
    }

    connect(m_socket, &QTcpSocket::connected, this, &SocketManager::onConnected);
    connect(m_socket, &QTcpSocket::errorOccurred, this, &SocketManager::onError);

    m_socket->connectToHost(host, port);
}

void SocketManager::onConnected()
{
    qDebug() << "Connected to the server.";
    emit connectedToServer(); // Signal success
}

void SocketManager::onError(QAbstractSocket::SocketError socketError)
{
    Q_UNUSED(socketError);
    qDebug() << "Connection error: " << m_socket->errorString();
    emit connectionFailed(); // Signal failure
}
