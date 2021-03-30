import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.0

Page {
    id: page

    width: 600
    height: 400

    title: qsTr("Main Page")

    ColumnLayout {
        anchors.centerIn: parent

        Label {
            Layout.alignment: Qt.AlignCenter

            text: qsTr("Welcome to the best cryptor ever")
        }
        Button {
            Layout.alignment: Qt.AlignCenter

            text: qsTr("Encrypt")
            padding: 12
            onClicked: {
                page.StackView.view.push("EncryptPage.qml")
            }
        }
        Button {
            Layout.alignment: Qt.AlignCenter

            text: qsTr("Decrypt")
            padding: 12
            onClicked: {
                page.StackView.view.push("DecryptPage.qml")
            }
        }
    }
}
