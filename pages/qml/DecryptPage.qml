import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.0
import QtQuick.Dialogs 1.3

Page {
    width: 600
    height: 400

    property var cryptor

    title: qsTr("Decryption")

    ColumnLayout {
        anchors.centerIn: parent

        Label {
            Layout.alignment: Qt.AlignCenter
            text: qsTr("Specify parameters:")
        }
        ComboBox {
            id: cipherType

            Layout.alignment: Qt.AlignCenter
            Layout.preferredWidth: cipherType.font.pixelSize * 10

            displayText: qsTr("Select cipher")

            model: typeModel
            ListModel {
                id: typeModel

                ListElement {
                    text: qsTr("Caesar")
                }
                // Add new ciphers here
            }

            onActivated: {
                decryptButton.visible = true
                fileDialog.open()
            }
        }
        FileDialog {
            id: fileDialog

            Layout.alignment: Qt.AlignCenter
            visible: false

            title: qsTr("Please choose a file")
            folder: shortcuts.home
            onAccepted: {
                console.log("You chose: " + fileDialog.fileUrls)
            }
            onRejected: {
                console.log("Canceled")
            }
        }
        TextField {
            id: passwordField

            Layout.alignment: Qt.AlignCenter

            echoMode: TextInput.Password
            placeholderText: qsTr("Password")
        }
        Button {
            id: decryptButton

            Layout.alignment: Qt.AlignCenter
            visible: false

            text: qsTr("Decrypt")
            padding: 12
            onClicked: {
//                cryptor.file = fileDialog.fileUrl
                resultLabel.text = "U r the best" //cryptor.decryptionResult
                resultLabel.visible = true
            }
        }
        Label {
            id: resultLabel

            Layout.alignment: Qt.AlignCenter
            visible: false
        }
    }
}

