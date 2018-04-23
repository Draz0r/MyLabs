import QtQuick 2.10
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3
import QtQuick.Window 2.3
ApplicationWindow {
    signal sendAuth(string login, string password)
    visible: true
    width: 240
    height: 280
    title: qsTr("Tabs")
    SwipeView {
        id: swipeView
        anchors.fill: parent
        currentIndex: tabBar.currentIndex

        Page{
            title: "Лр1: Безопасная аутентификация"
            ColumnLayout{
                anchors.fill: parent; //привязка к границам окна

                Item{//пустой заполнитель
                    Layout.fillHeight: true
                }
                TextField{
                    id: editLogin
                    Layout.alignment: Qt.AlignHCenter //центровка
                    placeholderText: "Login"
                    horizontalAlignment: TextInput.AlignHCenter
                    background:  Rectangle{
                        id: loginHightLight
                        anchors.fill: parent
                        implicitWidth: Screen.pixelDensity * 40
                        color: "transparent"
                        border.color: "transparent"
                        ScaleAnimator{
                            id: animation
                            target: loginHightLight //цель анимации
                            easing.type: Easing.OutElastic //тип кривой анимации
                            from: 0.5 // от
                            to: 1 // до
                            duration: 500 //длительность
                            running: false //по умолчанию анимация остановлена
                        }
                    }
                }
                TextField{
                    id: editPassword
                    Layout.alignment: Qt.AlignHCenter
                    placeholderText: "Passwrd"
                    horizontalAlignment: TextInput.AlignHCenter
                    passwordMaskDelay: 800
                    echoMode: TextInput.Password //TextInput.PasswordEchoOnEdit
                    background:  Rectangle{
                        id: passwordHightLight
                        anchors.fill: parent
                        implicitWidth: 200
                        color: "transparent"
                        border.color: "transparent"
                        ScaleAnimator{
                            id: animation2
                            target: loginHightLight //цель анимации
                            easing.type: Easing.OutElastic //тип кривой анимации
                            from: 0.5 // от
                            to: 1 // до
                            duration: 500 //длительность
                            running: false //по умолчанию анимация остановлена
                        }
                    }
                }
                Button{
                    id: btnAuth
                    //x: 300;
                    // y: 90;
                    text: "Вход"
                    Layout.alignment: Qt.AlignHCenter
                    Layout.minimumHeight: Screen.pixelDensity * 15
                    Layout.minimumWidth: Screen.pixelDensity * 15
                    onClicked: {
                        console.log("Log = " + editLogin.text + ", Pass = " + editPassword.text)
                        if(editLogin.text == ""){
                            //изменение цвета прямоугольника на красный
                            loginHightLight.border.color = "red";
                            animation.start()
                            return
                        }
                        if(editPassword.text == ""){
                            //подсветка красным
                            passwordHightLight.border.color = "red";
                            animation2.start()
                            return
                        }
                        sendAuth(editLogin.text,editPassword.text)
                    }
                }
                Item{//пустой заполнитель
                    Layout.fillHeight: true
                }
            }
        }
        //PAGE!!!!!!!!!!!

        //MVC
        Page{
            ListView{// V из MVC
                anchors.fill: parent
                model:5 // M из MVC
                delegate:
                    Rectangle{
                    width: parent.width;
                    height: Screen.pixelDensity * 10
                    radius: 1
                    border.width: 1
                    border.color: "red"
                    GridLayout{
                        anchors.fill: parent;
                        Text{ // C из MVC
                            text:index;
                            font.bold: true;
                            font.pixelSize: 20
                        }
                        Text{ // C из MVC
                            text:index;
                            font.bold: true;
                            font.pixelSize: 20
                        }
                    }
                }
            }
        }
    }
    /*
        footer: TabBar {
            id: tabBar
            currentIndex: swipeView.currentIndex

            TabButton {
                text: qsTr("Page 1")
            }
            TabButton {
                text: qsTr("Page 2")
            }
        }*/
    Connections{
        target: authController // подсвеычивается синим - значит успешно введен
        // в область видимости QML из С++
        onSignalAuthSuccess:{
            console.log("Вызван обработчик");
            swipeView.currentIndex = 1
        }
    }
}