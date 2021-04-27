QT += quick

CONFIG += c++17
#QMAKE_CXXFLAGS = -std=c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        source/Cryptor.cpp \
        source/main.cpp \
        source/alg.cpp \
        source/duthomhas/csprng.cpp \
        source/file_encrypter.cpp \


RESOURCES +=

TRANSLATIONS += \
    ../languages/cryptor_en_US.ts

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH = ../pages/qml

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH = ../pages/qml

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    source/Cryptor.h \
    source/alg.hpp \
    source/duthomhas/csprng.h \
    source/duthomhas/csprng.hpp \
    source/duthomhas/is_iterable.hpp \
    source/file_encrypter.hpp \

unix:!macx {
#    LIBS += -L/path/to -lcrypto
}

macx: {
    LIBS += -L/usr/local/Cellar//openssl@1.1/1.1.1j/lib -lcrypto
    INCLUDEPATH +=  /usr/local/opt/openssl/include
    QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.15
}

RESOURCES += \
    pages/qml/DecryptPage.qml \
    pages/qml/EncryptPage.qml \
    pages/qml/HomeForm.qml \
    pages/qml/MainPage.qml \
    pages/qml/Page1Form.ui.qml \
    pages/qml/Page2Form.ui.qml \
    pages/qml/main.qml
