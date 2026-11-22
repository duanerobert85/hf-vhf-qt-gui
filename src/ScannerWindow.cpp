#include "ScannerWindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>

ScannerWindow::ScannerWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("HF/VHF Scanner");
    resize(800, 480);

    auto *central = new QWidget(this);
    setCentralWidget(central);

    m_freqLabel = new QLabel("---.--- MHz", this);
    m_freqLabel->setAlignment(Qt::AlignCenter);
    m_freqLabel->setStyleSheet("font-size: 48px; color: #00ff80;");

    m_stateLabel = new QLabel("CONNECTING", this);
    m_stateLabel->setAlignment(Qt::AlignCenter);
    m_stateLabel->setStyleSheet("font-size: 24px; color: #ffc800;");

    auto *btnLayout = new QHBoxLayout;
    auto *scanBtn = new QPushButton("SCAN", this);
    auto *holdBtn = new QPushButton("HOLD", this);
    auto *manBtn  = new QPushButton("MAN", this);
    auto *sqlBtn  = new QPushButton("SQL", this);

    btnLayout->addWidget(scanBtn);
    btnLayout->addWidget(holdBtn);
    btnLayout->addWidget(manBtn);
    btnLayout->addWidget(sqlBtn);

    auto *layout = new QVBoxLayout(central);
    layout->addWidget(m_freqLabel);
    layout->addWidget(m_stateLabel);
    layout->addLayout(btnLayout);

    m_client = new PiScanClient(this);
    connect(m_client, &PiScanClient::statusUpdated, this, &ScannerWindow::onStatusUpdated);
    connect(scanBtn, &QPushButton::clicked, this, &ScannerWindow::onScanClicked);
    connect(holdBtn, &QPushButton::clicked, this, &ScannerWindow::onHoldClicked);
    connect(manBtn,  &QPushButton::clicked, this, &ScannerWindow::onManualClicked);
    connect(sqlBtn,  &QPushButton::clicked, this, &ScannerWindow::onSqlClicked);

    m_client->connectToServer();
}

void ScannerWindow::onStatusUpdated(const QString &freq, const QString &state)
{
    m_freqLabel->setText(freq);
    m_stateLabel->setText(state);
}

void ScannerWindow::onScanClicked()  { m_client->sendScan(); }
void ScannerWindow::onHoldClicked()  { m_client->sendHold(); }
void ScannerWindow::onManualClicked(){ m_client->sendManual(); }
void ScannerWindow::onSqlClicked()   { m_client->sendSql(); }
