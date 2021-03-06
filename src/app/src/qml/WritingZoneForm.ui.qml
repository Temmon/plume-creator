import QtQuick 2.12
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3

Item {
    id: base
    property alias text: textArea.text
    property bool stretch: stretch
    property int textAreaWidth
    property int maximumTextAreaWidth
    property bool minimapVisibility: minimapVisibility
    property alias scrollView: scrollView
    property alias textArea: textArea
    property alias flickable: flickable
    property alias internalScrollBar: internalScrollBar
    property int scrollBarVerticalPolicy: ScrollBar.AsNeeded
    property alias leftScrollItem: leftScrollItem
    property alias leftTouch1: leftTouch1
    property alias leftScrollTouchArea: leftScrollTouchArea
    property alias leftScrollMouseArea: leftScrollMouseArea

    Pane {
        id: pane
        anchors.fill: parent

        //padding: 0
        ColumnLayout {
            id: columnLayout
            spacing: 1
            anchors.fill: parent
            RowLayout {
                id: rowLayout
                spacing: 1
                Layout.fillHeight: true
                Layout.fillWidth: true
                Item {
                    id: leftScrollItem
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    MultiPointTouchArea {
                        id: leftScrollTouchArea
                        z: 1
                        anchors.fill: parent
                        mouseEnabled: false
                        maximumTouchPoints: 1
                        touchPoints: [
                            TouchPoint {
                                id: leftTouch1
                            }
                        ]
                    }
                    MouseArea {
                        id: leftScrollMouseArea
                        z: 0
                        anchors.fill: parent

                    }
                }
                ScrollView {
                    id: scrollView
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    Layout.fillHeight: true

                    //Layout.preferredWidth: textWidth
                    padding: 2
                    ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
                    ScrollBar.vertical.policy: scrollBarVerticalPolicy
                    clip: true

                    //contentWidth: scrollView.width
                    Flickable {
                        id: flickable
                        flickableDirection: Flickable.VerticalFlick
                        boundsBehavior: Flickable.StopAtBounds
                        interactive: true
                        clip: true
                        ScrollBar.vertical: ScrollBar {
                            id: internalScrollBar
                            parent: flickable.parent
                        }
                        TextArea.flickable: TextArea {
                            id: textArea
                            renderType: Text.NativeRendering
                            font.preferShaping: false
                            font.kerning: false
                            clip: true
                            textFormat: Text.PlainText
                            focus: true
                            selectByMouse: true
                            wrapMode: TextEdit.WrapAtWordBoundaryOrAnywhere

                            //                        background: Rectangle {
                            //                            border.color: "transparent"
                            //                        }
                        }
                    }
                }

                Item {
                    id: rightScrollItem
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                }
            }
        }
    }
    states: [
        State {
            name: "noStretch"
            when: stretch == false

            //            AnchorChanges {
            //                target: textArea
            //                anchors.horizontalCenter: parent.horizontalCenter
            //                anchors.left: undefined
            //                anchors.right: undefined
            //            }
            //            PropertyChanges {
            //                target: textArea
            //                implicitWidth: textAreaWidth
            //            }
            PropertyChanges {
                target: scrollView
                implicitWidth: textAreaWidth
                Layout.fillWidth: false
            }
        },
        State {
            name: "stretch"
            when: stretch == true

            //            AnchorChanges {
            //                target: textArea
            //                anchors.horizontalCenter: undefined
            //                anchors.left: parent.left
            //                anchors.right: parent.right

            //            }
            //            PropertyChanges {
            //                target: textArea
            //                implicitWidth: 0
            //            }
            PropertyChanges {
                target: scrollView
                implicitWidth: 0
                Layout.fillWidth: true
            }
        }
    ]
}






/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
