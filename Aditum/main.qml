import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQml 2.0
import QtQuick.Dialogs 1.1

ApplicationWindow {
    visible: true
    width: 350
    height: 480
    color: "#a0a0a0"
    title: qsTr("Restaurant Checker")
    function appendList(newElement, length){
        lista.clear();
        for(var i = 0; i < length; i++){
            lista.append({"index":i, "name": newElement[i]})
        }
    }


    Button {
        id: send
        x: 232
        y: 161
        text: "Solicitar"
        visible: false
        onClicked: appendList(dataStore.pickRestaurants(fileDialog.fileUrl, solicitacao.text), dataStore.qtdAvaiableRestaurants())

    }


    TextField {
        id: solicitacao
        x: 26
        y: 161
        placeholderText: "Digite um horário: HH:mm"
    }

    ListView {
        id: listView
        x: 26
        y: 283
        width: 306
        height: 160
        delegate: Item {
            x: 5
            width: 80
            height: 40
            Row {
                id: row1
                Rectangle {
                    width: 40
                    height: 40
                    Text {
                        text: index
                        anchors.centerIn: parent
                    }
                }

                Text {
                    text: name
                    anchors.verticalCenter: parent.verticalCenter
                    font.bold: true
                }
                spacing: 10
            }
        }
        model: ListModel {
            id: lista
        }
    }

    Text {
        id: element
        x: 59
        y: 215
        width: 206
        height: 35
        text: qsTr("Lista de Restaurantes")
        font.capitalization: Font.Capitalize
        font.strikeout: false
        font.underline: false
        font.italic: true
        font.bold: true
        wrapMode: Text.NoWrap
        lineHeight: 1.3
        fontSizeMode: Text.FixedSize
        renderType: Text.NativeRendering
        textFormat: Text.RichText
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        font.pixelSize: 15

    }

    Button {
        id: send1
        x: 26
        y: 115
        width: 306
        height: 40
        text: "Selecione um arquivo .csv"
        visible: true
        onClicked: fileDialog.open()
    }

    ProgressBar {
        id: progressBar
        x: 26
        y: 94
        width: 306
        height: 15
        layer.mipmap: false
        layer.format: ShaderEffectSource.RGBA
        layer.enabled: true
        value: 0.0
    }

    FileDialog {
        id: fileDialog
        folder: shortcuts.home
        selectMultiple: false
        selectFolder: false
        onAccepted: {
            send.visible = true
            progressBar.value = 1.0
        }
        onRejected: {
            console.log("Canceled")
        }

    }
}
/*##^##
Designer {
    D{i:0;formeditorColor:"#ffffff";formeditorZoom:0.6600000262260437}
}
##^##*/
