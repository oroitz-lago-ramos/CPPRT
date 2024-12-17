#ifndef TESTSERVER_H
#define TESTSERVER_H

#include <QObject>
#include <QtTest>
#include "Server.h"

class TestServer : public QObject {
    Q_OBJECT

private slots:
    void initTestCase();  // Called before any tests
    void cleanupTestCase();  // Called after all tests
    void testServerStart();  // Test server start
    void testHandleNewConnection();  // Test handling new connections
    void testClientMessageBroadcast();  // Test message broadcasting

private:
    Server* server;  // Server instance for testing
};

#endif // TESTSERVER_H
