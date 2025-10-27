/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QStackedWidget *stackedWidget;
    QWidget *Conexion;
    QLineEdit *ipInput;
    QLineEdit *nameInput;
    QPushButton *hostButton;
    QPushButton *joinButton;
    QLabel *label_2;
    QLabel *label_3;
    QWidget *page;
    QLineEdit *teamNameInput;
    QPushButton *addPlayerButton;
    QTextEdit *lobbyDisplay;
    QPushButton *startGameButton;
    QLabel *label;
    QWidget *page_2;
    QTextEdit *logDisplay;
    QPushButton *nextTurnButton;
    QScrollArea *scrollArea;
    QWidget *gameAreaWidget;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *gameLayout;
    QWidget *page_3;
    QLabel *winnerLabel;
    QPushButton *lobbyButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName("stackedWidget");
        Conexion = new QWidget();
        Conexion->setObjectName("Conexion");
        ipInput = new QLineEdit(Conexion);
        ipInput->setObjectName("ipInput");
        ipInput->setGeometry(QRect(100, 90, 171, 22));
        nameInput = new QLineEdit(Conexion);
        nameInput->setObjectName("nameInput");
        nameInput->setGeometry(QRect(100, 160, 661, 22));
        hostButton = new QPushButton(Conexion);
        hostButton->setObjectName("hostButton");
        hostButton->setGeometry(QRect(70, 240, 81, 24));
        joinButton = new QPushButton(Conexion);
        joinButton->setObjectName("joinButton");
        joinButton->setGeometry(QRect(180, 240, 91, 24));
        label_2 = new QLabel(Conexion);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(100, 70, 49, 16));
        label_3 = new QLabel(Conexion);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(100, 140, 61, 16));
        stackedWidget->addWidget(Conexion);
        page = new QWidget();
        page->setObjectName("page");
        teamNameInput = new QLineEdit(page);
        teamNameInput->setObjectName("teamNameInput");
        teamNameInput->setGeometry(QRect(20, 40, 751, 22));
        addPlayerButton = new QPushButton(page);
        addPlayerButton->setObjectName("addPlayerButton");
        addPlayerButton->setGeometry(QRect(20, 80, 241, 24));
        lobbyDisplay = new QTextEdit(page);
        lobbyDisplay->setObjectName("lobbyDisplay");
        lobbyDisplay->setGeometry(QRect(10, 120, 381, 371));
        lobbyDisplay->setReadOnly(true);
        startGameButton = new QPushButton(page);
        startGameButton->setObjectName("startGameButton");
        startGameButton->setGeometry(QRect(140, 500, 101, 24));
        label = new QLabel(page);
        label->setObjectName("label");
        label->setGeometry(QRect(20, 10, 181, 16));
        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        logDisplay = new QTextEdit(page_2);
        logDisplay->setObjectName("logDisplay");
        logDisplay->setGeometry(QRect(20, 30, 251, 501));
        nextTurnButton = new QPushButton(page_2);
        nextTurnButton->setObjectName("nextTurnButton");
        nextTurnButton->setGeometry(QRect(300, 30, 75, 24));
        scrollArea = new QScrollArea(page_2);
        scrollArea->setObjectName("scrollArea");
        scrollArea->setGeometry(QRect(380, 60, 351, 441));
        scrollArea->setWidgetResizable(true);
        gameAreaWidget = new QWidget();
        gameAreaWidget->setObjectName("gameAreaWidget");
        gameAreaWidget->setGeometry(QRect(0, 0, 349, 439));
        verticalLayoutWidget = new QWidget(gameAreaWidget);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(10, 10, 331, 421));
        gameLayout = new QVBoxLayout(verticalLayoutWidget);
        gameLayout->setObjectName("gameLayout");
        gameLayout->setContentsMargins(0, 0, 0, 0);
        scrollArea->setWidget(gameAreaWidget);
        stackedWidget->addWidget(page_2);
        page_3 = new QWidget();
        page_3->setObjectName("page_3");
        winnerLabel = new QLabel(page_3);
        winnerLabel->setObjectName("winnerLabel");
        winnerLabel->setGeometry(QRect(180, 160, 411, 191));
        QFont font;
        font.setPointSize(26);
        font.setBold(true);
        font.setItalic(true);
        winnerLabel->setFont(font);
        winnerLabel->setTextFormat(Qt::TextFormat::AutoText);
        lobbyButton = new QPushButton(page_3);
        lobbyButton->setObjectName("lobbyButton");
        lobbyButton->setGeometry(QRect(120, 500, 111, 31));
        stackedWidget->addWidget(page_3);

        verticalLayout->addWidget(stackedWidget);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        ipInput->setText(QCoreApplication::translate("MainWindow", "127.0.0.1", nullptr));
        nameInput->setText(QCoreApplication::translate("MainWindow", "nombre", nullptr));
        hostButton->setText(QCoreApplication::translate("MainWindow", "Crear Partida", nullptr));
        joinButton->setText(QCoreApplication::translate("MainWindow", "Unirse a Partida", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "ip", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "tu nombre", nullptr));
        teamNameInput->setText(QString());
        addPlayerButton->setText(QCoreApplication::translate("MainWindow", "Unirse a equipo", nullptr));
        startGameButton->setText(QCoreApplication::translate("MainWindow", "Empezar Juego", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Ingresa nombre de tu equipo", nullptr));
        nextTurnButton->setText(QCoreApplication::translate("MainWindow", "Jugar", nullptr));
        winnerLabel->setText(QCoreApplication::translate("MainWindow", "\302\241\302\241Equipo X ha ganado!!", nullptr));
        lobbyButton->setText(QCoreApplication::translate("MainWindow", "Volver al Lobby", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
