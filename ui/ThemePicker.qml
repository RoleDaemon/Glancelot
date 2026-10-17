import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Dialog {
    id: picker
    title: "Appearance"
    modal: true
    width: Math.min(780, parent.width - 40)
    height: Math.min(660, parent.height - 48)
    standardButtons: Dialog.Close
    readonly property bool compact: height < 450
    onOpened: search.forceActiveFocus()
    ColumnLayout {
        anchors.fill: parent
        spacing: picker.compact ? 6 : 14
        RowLayout {
            Layout.fillWidth: true
            ColumnLayout {
                spacing: picker.compact ? 0 : 4
                Layout.fillWidth: true
                Label { text: picker.compact ? "Palette" : "Choose your palette"; font.pixelSize: picker.compact ? 14 : 20; font.weight: Font.DemiBold; Layout.fillWidth: true; elide: Text.ElideRight }
                Label { visible: !picker.compact; text: "40 palettes · light and dark"; color: theme.colors.muted; font.pixelSize: 12 }
            }
            Item { Layout.fillWidth: true }
            ComboBox {
                id: modeSelect
                model: ["Follow system", "Dark", "Light"]
                currentIndex: ["system", "dark", "light"].indexOf(theme.mode)
                onActivated: theme.mode = ["system", "dark", "light"][currentIndex]
                Accessible.name: "Theme appearance mode"
            }
        }
        TextField { id: search; Layout.fillWidth: true; placeholderText: "Search themes…"; Accessible.name: "Search themes" }
        ScrollView {
            Layout.fillWidth: true
            Layout.fillHeight: true
            clip: true
            contentWidth: availableWidth
            Flow {
                width: parent.width
                spacing: 10
                Repeater {
                    model: theme.families
                    delegate: ItemDelegate {
                        id: card
                        required property var modelData
                        property var preview: theme.dark ? modelData.dark : modelData.light
                        visible: modelData.name.toLowerCase().indexOf(search.text.toLowerCase()) >= 0
                        width: (picker.availableWidth - (picker.availableWidth >= 600 ? 20 : 10)) / (picker.availableWidth >= 600 ? 3 : 2)
                        height: picker.compact ? 76 : 106
                        checked: theme.family === modelData.id
                        Accessible.name: modelData.name + (checked ? ", selected" : "")
                        onClicked: theme.family = modelData.id
                        background: Rectangle {
                            color: card.preview.background
                            radius: 6
                            border.width: card.checked || card.visualFocus ? 2 : 1
                            border.color: card.checked || card.visualFocus ? theme.colors.primary : card.preview.border
                        }
                        contentItem: ColumnLayout {
                            spacing: 10
                            RowLayout {
                                Layout.fillWidth: true
                                Label { text: card.modelData.name; color: card.preview.text; font.weight: Font.Medium; Layout.fillWidth: true }
                                Label { text: card.checked ? "✓" : ""; color: card.preview.primary }
                            }
                            Row {
                                spacing: 5
                                Repeater {
                                    model: [card.preview.surface, card.preview.text, card.preview.primary, card.preview.accent, card.preview.border]
                                    delegate: Rectangle { required property string modelData; width: 23; height: 23; radius: 4; color: modelData; border.color: card.preview.border }
                                }
                            }
                        }
                    }
                }
            }
        }
        Label { visible: !picker.compact || theme.error.length > 0; Layout.fillWidth: true; text: theme.error || "Theme changes apply immediately and are saved. Photo pixel colors stay unchanged."; color: theme.error ? theme.colors.danger : theme.colors.muted; wrapMode: Text.Wrap }
    }
}
