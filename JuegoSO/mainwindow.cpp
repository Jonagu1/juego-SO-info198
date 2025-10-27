// mainwindow.cpp
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug> // Para ver mensajes en la consola de Qt Creator
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_server(nullptr) // <-- ¡AÑADIR ESTA INICIALIZACIÓN!
{
    ui->setupUi(this);

    // 1. Empezamos en la página 0 (Host/Join)
    ui->stackedWidget->setCurrentIndex(0);

    // 2. Inicializamos el socket (esto no cambia)
    m_socket = new QTcpSocket(this);

    // 3. Conectamos las señales del socket (esto no cambia)
    connect(m_socket, &QTcpSocket::connected, this, &MainWindow::onSocketConnected);
    connect(m_socket, &QTcpSocket::readyRead, this, &MainWindow::onSocketReadyRead);
    connect(m_socket, &QTcpSocket::disconnected, this, &MainWindow::onSocketDisconnected);

    // 4. ¡REEMPLAZAR! Conectamos los botones "Host" y "Join"
    connect(ui->hostButton, &QPushButton::clicked, this, &MainWindow::on_hostButton_clicked);
    connect(ui->joinButton, &QPushButton::clicked, this, &MainWindow::on_joinButton_clicked);

    // 5. Conectamos el botón de la pág. de ganador (esto no cambia)
    connect(ui->lobbyButton, &QPushButton::clicked, this, &MainWindow::on_lobbyButton_clicked);
}

MainWindow::~MainWindow()
{
    delete ui;
    // ¡AÑADIR ESTO!
    if (m_server) {
        delete m_server;
    }
}
// ---
// PÁGINA 0: CONEXIÓN
// ---
void MainWindow::on_hostButton_clicked()
{
    m_playerName = ui->nameInput->text();
    if (m_playerName.isEmpty()) {
        QMessageBox::warning(this, "Error", "Debes ingresar un Nombre.");
        return;
    }

    // 1. ¡CREAMOS EL SERVIDOR!
    qDebug() << "Iniciando modo Host...";
    m_server = new Server(this);
    m_server->startServer(); // El servidor empieza a escuchar

    // 2. Nos conectamos a nuestro propio servidor
    m_socket->connectToHost(QHostAddress("127.0.0.1"), 8080);

    // (Desactivamos botones para evitar doble clic)
    ui->hostButton->setEnabled(false);
    ui->joinButton->setEnabled(false);
}

void MainWindow::on_joinButton_clicked()
{
    m_playerName = ui->nameInput->text();
    QString ip = ui->ipInput->text();

    if (ip.isEmpty() || m_playerName.isEmpty()) {
        QMessageBox::warning(this, "Error", "Debes ingresar una IP y un Nombre.");
        return;
    }

    // 1. ¡NO CREAMOS SERVIDOR!
    qDebug() << "Iniciando modo Cliente, conectando a" << ip;

    // 2. Nos conectamos al servidor del Host
    m_socket->connectToHost(QHostAddress(ip), 8080);

    // (Desactivamos botones para evitar doble clic)
    ui->hostButton->setEnabled(false);
    ui->joinButton->setEnabled(false);
}

// ---
// PÁGINA 1: LOBBY
// ---

void MainWindow::on_addPlayerButton_clicked() // Ahora significa "Unirse a Equipo"
{
    QString teamName = ui->teamNameInput->text();
    if (teamName.isEmpty()) return;

    // ¡ACCIÓN NUEVA! Solo envía un mensaje.
    QString message = "JOIN_TEAM:" + teamName + "\n";
    m_socket->write(message.toUtf8());

    ui->teamNameInput->clear();
}

void MainWindow::on_startGameButton_clicked()
{
    // ¡ACCIÓN NUEVA! Solo envía un mensaje.
    m_socket->write("START_GAME\n");

    // ¡NUEVO! Desactivamos el botón para evitar spam
    ui->startGameButton->setEnabled(false);
}
// ---
// PÁGINA 2: JUEGO
// ---

void MainWindow::on_nextTurnButton_clicked()
{
    // ¡ACCIÓN NUEVA! Solo envía un mensaje.
    m_socket->write("NEXT_TURN\n");

    // (El servidor nos responderá con un GAME_UPDATE si el turno es válido)
}

void MainWindow::on_lobbyButton_clicked()
{
    // 1. Reactivamos el botón de "Start" SI SOMOS EL ADMIN
    //    (El cliente sabe que es admin si el botón es visible)
    if (ui->startGameButton->isVisible()) {
        ui->startGameButton->setEnabled(true);
    }

    // 2. Volvemos a la página de Lobby (índice 1)
    ui->stackedWidget->setCurrentIndex(1);
}
void MainWindow::onSocketConnected()
{
    qDebug() << "Cliente: Conectado al servidor.";
    // Reactivar botones de Host/Join (por si nos desconectamos y volvemos)
    ui->hostButton->setEnabled(true);
    ui->joinButton->setEnabled(true);

    // Esto funciona igual para Host y Cliente
    QString message = "CONNECT:" + m_playerName + "\n";
    m_socket->write(message.toUtf8());

    ui->stackedWidget->setCurrentIndex(1); // Ir al Lobby
}

void MainWindow::onSocketDisconnected()
{
    qDebug() << "Cliente: Desconectado del servidor.";
    QMessageBox::critical(this, "Desconectado", "Se perdió la conexión con el servidor.");

    // Reactivar botones
    ui->hostButton->setEnabled(true);
    ui->joinButton->setEnabled(true);

    // ¡AÑADIR ESTO! Si éramos el Host, matamos el servidor.
    if (m_server) {
        qDebug() << "Cerrando el servidor local.";
        delete m_server;
        m_server = nullptr;
    }

    // Volver a la pantalla de conexión (índice 0)
    ui->stackedWidget->setCurrentIndex(0);
}
void MainWindow::clearGameWidgets()
{
    for (QLabel* label : m_teamLabels) {
        delete label;
    }
    m_teamLabels.clear();

    for (QProgressBar* bar : m_teamProgressBars) {
        delete bar;
    }
    m_teamProgressBars.clear();
}
// mainwindow.cpp
// Reemplaza toda la función onSocketReadyRead por esta:

void MainWindow::onSocketReadyRead()
{
    // El servidor envió un mensaje, ¡hay que leerlo!
    QByteArray data = m_socket->readAll();
    QStringList messages = QString(data).trimmed().split('\n', Qt::SkipEmptyParts);

    for (const QString& message : messages)
    {
        qDebug() << "Cliente: Mensaje recibido:" << message;

        // ---
        // MENSAJES DEL LOBBY
        // ---
        if (message.startsWith("CONNECT_OK:")) {
            QString role = message.section(':', 1);
            if (role == "ADMIN") {
                ui->startGameButton->setVisible(true); // Mostramos el botón
            } else {
                ui->startGameButton->setVisible(false); // Ocultamos el botón
            }
        }
        else if (message.startsWith("LOBBY_UPDATE:")) {
            // "LOBBY_UPDATE:Azul:Ana,Carlos;Rojo:Bea"
            QString data = message.section(':', 1);
            ui->lobbyDisplay->clear();
            ui->lobbyDisplay->append("--- Estado del Lobby ---");

            QStringList teams = data.split(';', Qt::SkipEmptyParts);
            for (const QString& team : teams) {
                QStringList parts = team.split(':');
                if (parts.length() < 2) continue; // Ignorar equipos mal formados

                QString teamName = parts[0];
                QString players = parts[1];

                ui->lobbyDisplay->append("Equipo [" + teamName + "]: " + players.replace(",", ", "));
            }
        }
        else if (message.startsWith("ERROR:")) {
            // "ERROR:No se puede iniciar"
            QString errorMsg = message.section(':', 1);
            QMessageBox::warning(this, "Error del Servidor", errorMsg);

            // ¡Importante! Reactivamos el botón de Start si somos Admin
            if (ui->startGameButton->isVisible()) {
                ui->startGameButton->setEnabled(true);
            }
        }

        // ---
        // MENSAJES DEL JUEGO (¡LA PRUEBA ESTÁ AQUÍ!)
        // ---
        else if (message.startsWith("JUEGO_INICIADO:")) {

            qDebug() << "[DEBUG] Entrando a JUEGO_INICIADO...";

            // 1. Limpiamos widgets de partidas anteriores
            clearGameWidgets();
            qDebug() << "[DEBUG] 1. clearGameWidgets() OK.";

            ui->logDisplay->clear();
            qDebug() << "[DEBUG] 2. logDisplay->clear() OK. (¡Significa que ui->logDisplay NO es nulo!)";

            ui->logDisplay->append("¡El juego ha comenzado!");
            qDebug() << "[DEBUG] 3. logDisplay->append() OK.";

            // 2. Obtenemos la lista de equipos
            QString teamData = message.section(':', 1);
            QStringList teams = teamData.split(';', Qt::SkipEmptyParts);
            qDebug() << "[DEBUG] 4. Lista de equipos procesada:" << teams;

            // 3. Creamos los labels y barras (como hacíamos antes)
            for (const QString& teamName : teams) {
                qDebug() << "[DEBUG] 5. Creando widgets para equipo:" << teamName;
                QLabel* nameLabel = new QLabel(teamName);
                nameLabel->setStyleSheet("font-weight: bold; font-size: 14px;");

                QProgressBar* bar = new QProgressBar();

                ui->gameLayout->addWidget(nameLabel);
                qDebug() << "[DEBUG] 6. nameLabel añadido a gameLayout OK.";

                ui->gameLayout->addWidget(bar);
                qDebug() << "[DEBUG] 7. bar añadido a gameLayout OK.";

                m_teamLabels.push_back(nameLabel);
                m_teamProgressBars.push_back(bar);
            }

            qDebug() << "[DEBUG] 8. Bucle de creación de widgets finalizado.";

            // 4. Cambiamos a la página de Juego (índice 2)
            ui->stackedWidget->setCurrentIndex(2);
            qDebug() << "[DEBUG] 9. ¡¡CAMBIO DE PÁGINA REALIZADO!!";
        }
        else if (message.startsWith("GAME_UPDATE:")) {
            // "GAME_UPDATE:Azul:10;Rojo:5;Goal:20"
            // (La lógica de actualización de la barra de progreso...)

            QStringList parts = message.section(':', 1).split(';', Qt::SkipEmptyParts);
            int winGoal = 20; // Default

            if (!parts.isEmpty() && parts.last().startsWith("Goal:")) {
                winGoal = parts.last().section(':', 1).toInt();
                parts.removeLast();
            }

            for (const QString& teamData : parts) {
                QString teamName = teamData.section(':', 0, 0);
                int score = teamData.section(':', 1, 1).toInt();

                for (size_t i = 0; i < m_teamLabels.size(); ++i) {
                    if (m_teamLabels[i]->text() == teamName && i < m_teamProgressBars.size()) {
                        m_teamProgressBars[i]->setMaximum(winGoal);
                        m_teamProgressBars[i]->setValue(score);
                        QString text = (teamName + " (%1/%2)").arg(score).arg(winGoal);
                        m_teamProgressBars[i]->setFormat(text);
                        break;
                    }
                }
            }
        }
        else if (message.startsWith("LOG:")) {
            // "LOG:Turno de...|  > lanzó un 5...|  Total..."
            QString logMsg = message.section(':', 1);

            // ¡CAMBIO! Reemplazamos el "|" por un salto de línea
            logMsg.replace("|", "\n");

            ui->logDisplay->append(logMsg); // Añadimos al log del juego
        }
        else if (message.startsWith("GAME_OVER:")) {
            // "GAME_OVER:Azul"
            QString winner = message.section(':', 1);
            ui->winnerLabel->setText("¡El equipo '" + winner + "' ha ganado!");
            ui->stackedWidget->setCurrentIndex(3); // Pág. de ganador (índice 3)
        }
    }
}
