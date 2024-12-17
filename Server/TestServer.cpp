#include "TestServer.h"
#include <QTcpSocket>
#include <QDebug>

// Initialize the server before tests
void TestServer::initTestCase() {
    server = new Server();  // Create a new server instance
}

// Cleanup after all tests
void TestServer::cleanupTestCase() {
    delete server;  // Delete the server instance
}

// Test server start functionality
void TestServer::testServerStart() {
    QVERIFY(server->startServer(12345));  // Assert server starts on port 12345
}

// Test handling a new connection
void TestServer::testHandleNewConnection() {
    QTcpSocket* clientSocket = new QTcpSocket();
    clientSocket->connectToHost("localhost", 12345);
    QVERIFY(clientSocket->waitForConnected(5000));  // Assert connection is successful

    // Assert that the server has at least one connected client (it should be the test client)
    QVERIFY(server->clients.size() > 0);
}

// Test broadcasting a message to all clients
void TestServer::testClientMessageBroadcast() {
    QTcpSocket* client1 = new QTcpSocket();
    client1->connectToHost("localhost", 12345);
    QVERIFY(client1->waitForConnected(5000));

    // Send a message from client1
    client1->write("Hello from Client1");

    // Test if client1's message is broadcasted correctly
    QTcpSocket* client2 = new QTcpSocket();
    client2->connectToHost("localhost", 12345);
    QVERIFY(client2->waitForConnected(5000));

    client2->waitForReadyRead(5000);  // Wait for the message from client1
    QCOMPARE(client2->readAll(), QByteArray("Hello from Client1"));
}

QTEST_MAIN(TestServer)
