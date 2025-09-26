import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15


Window {
    visible: true
    width: 1280
    height: 720
    title: "Kamera Görüntüsü"

    Image {
        id: cameraImage
        anchors.fill: parent
        source: "image://live/image"
        fillMode: Image.PreserveAspectFit
        smooth: true
        cache:false
        property bool updateFrame: false
        function reload()
        {
            updateFrame = !updateFrame
            source = "image://live/image?id=" + Math.random()
        }

        onStatusChanged: {
            console.log("Source updated:", cameraImage.source)
        }
    }
    Connections
    {
        target: ImageProvider
        function onImageChanged()
        {
            cameraImage.reload()
        }
    }

}
