import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import com.mycompany.ball 1.0
import com.mycompany.PhysicalEngine 1.0

ApplicationWindow
{
    visible: true
    width: 800
    height: 400
    SequentialAnimation
    {
        id:anim
       running: true
       loops: 1000
       NumberAnimation { target: play; property: "scale"; from : 1 ;to: 2.0; duration: 500 }
       NumberAnimation { target: play; property: "scale"; from : 2.0 ; to: 1.0; duration: 500 }
    }
    SequentialAnimation
    {
        id:anim1
       NumberAnimation { target: game_parent; property: "opacity"; from : 0 ;to: 1.0; duration: 500 }
    }
    Image
    {
        id: play
        source: "Button_3-512.png"
        height:  parent.height/4
        width:   parent.width/8
        y:  parent.height/3
        x:   parent.width/2.5
        opacity: 0.6
        antialiasing: true
        visible: true
        MouseArea
        {
            anchors.fill: parent

            onClicked: {
            anim.stop()
            game_parent.visible = true;
                play.visible = false;
                anim1.start()

            }
        }

    }
    Item
    {
        visible: false
        id: game_parent
        anchors.fill: parent
        Ball
        {
            id:first
            property int b_id: 0
            objectName: "gBall"
            x:parent.width/2
            y:parent.height/2
            width: parent.width/20
            height:parent.height/10
            z:1
            Image
            {
                anchors.fill:parent
                id: ball_image
                source: "Metal_ball_body.png"
                z:1
            }
        }
//        Ball
//        {
//            id:second
//            property int b_id: 1
//            objectName: "fBall"
//            x:parent.width/3;
//            y:parent.height/3
//            width: parent.width/20
//            height:parent.height/10
//            z:1
//            Image
//            {
//                anchors.fill:parent
//                id: ball_image1
//                source: "Metal_ball_body.png"
//                z:1
//            }
//        }
        PhysicalEngine
        {
            id: main_game
            z:-2
            width:  parent.height
            height: parent.width
        }
        Component.onCompleted: main_game.initPointers()
    }
}
