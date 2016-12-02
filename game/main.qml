import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import com.mycompany.ball 1.0
import com.mycompany.PhysicalEngine 1.0

ApplicationWindow {
    visible: true
    width: 800
    height: 400
    title: qsTr("Hello World")
//    function repaint
//    {

//    }
    Image {
        id: background
        x: 200
        y: -200
        width:  parent.height
        height: parent.width
        rotation: 90
        source: "paper.jpg"
    }

    Ball
    {
        id:first
        objectName: "gBall"
        x:parent.width/2
        y:parent.height/2
        width: parent.width/20
        height:parent.height/10
        Image {
            anchors.fill:parent
            id: ball_image
            antialiasing: true
            source: "Metal_ball_body.png"
        }
    }


}
