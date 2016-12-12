
import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import ball 1.0
import PhysicalEngine 1.0
import Pocket 1.0

Item

{
    id: main
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
    ParallelAnimation
    {
        id:ball_gone
        NumberAnimation { target: first; property: "opacity"; from : 1 ;to: 0; duration: 300 }
        NumberAnimation { target: first; property: "scale"; from : 1 ;to: 0.7; duration: 700 }
        onStopped: {first.scale = 1 ; first.opacity = 1;main_game.toStartPos()}
    }
    ParallelAnimation
    {
        id:getCoin
        NumberAnimation { target: coin; property: "opacity"; from : 1 ;to: 0; duration: 700 }
        NumberAnimation { target: coin; property: "scale"; from : 0.5 ;to: 2; duration: 700 }
    }
    Image {
        id: background
        source: "pool_table.jpg"
        anchors.fill: parent
        visible: true
        antialiasing: true
        smooth: true
        z:0
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
        x: 48
        y: 50
        width: 703
        height: 301
        anchors.rightMargin: 50
        anchors.bottomMargin: 51
        anchors.leftMargin: 49
        anchors.topMargin: 51
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
                source: "bill_bal.png"
                z:1
                antialiasing: true
                smooth: true

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
        Image {
            id: coin
            source: "coin.png"
            width: parent.width/20
            height: parent.height/10
            visible: false;
        }
        PhysicalEngine
        {
            id: main_game
            x: 0
            y: 0
            z:-2
            width:  game_parent.width
            height: game_parent.height
            onPocketEx:
            {
                console.log("cach it!")
                coin.x = pos_x
                coin.y = pos_y
                coin.visible = true
                coin.z = 2
                getCoin.start()
                ball_gone.start()
            }

            Pocket {
                id: pocket1
                objectName: "pocket1"
                x: -14
                y: -23
                width: 43
                height: 57
                rotation: 50
                transformOrigin: Item.Center
            }

            Pocket {
                id: pocket2
                objectName: "pocket2"
                x: 324
                y: -31
                width: 54
                height: 51
            }

            Pocket {
                id: pocket3
                objectName: "pocket3"
                x: -18
                y: 268
                width: 43
                height: 57
                transformOrigin: Item.Center
                rotation: -48
            }

            Pocket {
                id: pocket4
                objectName: "pocket4"
                x: 674
                y: 267
                width: 43
                height: 57
                transformOrigin: Item.Center
                rotation: 42
            }

            Pocket {
                id: pocket5
                objectName: "pocket5"
                x: 324
                y: 280
                width: 54
                height: 51
            }

            Pocket {
                id: pocket6
                objectName: "pocket6"
                x: 674
                y: -23
                width: 43
                height: 57
                transformOrigin: Item.Center
                rotation: -48
            }
        }


    }
    Component.onCompleted: main_game.initPointers()
}
