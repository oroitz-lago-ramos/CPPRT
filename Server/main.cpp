#include <QCoreApplication>
#include "Server.h"

#ifdef RUN_TESTS
#include "TestServer.h"
#endif

int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);

    Server server;
    if (!server.startServer(12345)) {
        return -1;  // Exit if the server fails to start
    }
    return app.exec();  // Run the server normally
}
