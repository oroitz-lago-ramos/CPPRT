QT += core network testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

SOURCES += \
    Server.cpp \
    main.cpp

HEADERS += \
    Server.h

# Ensure moc is called for the test header
FORMS +=

# Optional: For deployment rules
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
