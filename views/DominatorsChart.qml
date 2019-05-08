import QtQuick 2.9
import QtQuick.Controls 2.9
import QtQuick.Window 2.2
import QtQuick.Layouts 1.12
import QtQuick.Shapes 1.12

Rectangle {
    id: cRect
    color: "white"

    anchors.fill: parent
    property int xCenter: parent.width/2
    property int yCenter: parent.height/2
    property int centerRadius: 50
    property int layerWidth: 20

    Repeater {
        model: modelSize
        Shape {
            anchors.fill: parent

            ShapePath {
                id: shape
                fillColor: modelColors[index]
                property int curRadius: cRect.centerRadius + modelShifts[index] * 20
                property int extRadius: cRect.centerRadius + (modelShifts[index] + 1) * 20

                property var modelStartX: cRect.xCenter + curRadius * xStarts[index]
                property var modelStartY: cRect.yCenter + curRadius * yStarts[index]
                property var modelEndX: cRect.xCenter + curRadius * xEnds[index]
                property var modelEndY: cRect.yCenter + curRadius * yEnds[index]

                property var modelExtStartX: cRect.xCenter + extRadius * xStarts[index]
                property var modelExtStartY: cRect.yCenter + extRadius * yStarts[index]
                property var modelExtEndX: cRect.xCenter + extRadius * xEnds[index]
                property var modelExtEndY: cRect.yCenter + extRadius * yEnds[index]


                strokeColor: "blue"
                startX: modelStartX
                startY: modelStartY
                PathArc {
                    x: shape.modelEndX
                    y: shape.modelEndY
                    radiusX: shape.curRadius
                    radiusY: shape.curRadius
                }
                PathLine {
                    x: shape.modelExtEndX;
                    y: shape.modelExtEndY;
                }
                PathArc {
                    direction: PathArc.Counterclockwise
                    x: shape.modelExtStartX
                    y: shape.modelExtStartY
                    radiusX: shape.extRadius
                    radiusY: shape.extRadius
                }
            }
        }
    }
}
