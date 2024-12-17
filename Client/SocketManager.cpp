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

void SocketManager::connectToServer(const QString& host, quint16 port)
{
    m_socket->connectToHost(host, port);
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

void SocketManager::onConnected()
{
    emit connected();
}

void SocketManager::onDisconnected()
{
    emit disconnected();
}

void SocketManager::onError(QAbstractSocket::SocketError error)
{
    emit errorOccurred(m_socket->errorString());
}
