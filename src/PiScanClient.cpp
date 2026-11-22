#include "PiScanClient.h"
#include <QDebug>

PiScanClient::PiScanClient(QObject *parent)
    : QObject(parent)
    , m_socket(new QTcpSocket(this))
{
    connect(m_socket, &QTcpSocket::readyRead, this, &PiScanClient::onReadyRead);
}

void PiScanClient::connectToServer(const QString &host, quint16 port)
{
    m_socket->connectToHost(host, port);
}

void PiScanClient::sendRaw(const QByteArray &data)
{
    if (m_socket->state() == QAbstractSocket::ConnectedState)
        m_socket->write(data);
}

void PiScanClient::sendScan()
{
    // TODO: build proper protobuf ScannerStateRequest SCAN
    qDebug() << "SCAN requested";
}

void PiScanClient::sendHold()
{
    qDebug() << "HOLD requested";
}

void PiScanClient::sendManual(qint64 freqHz, const QString &mod)
{
    qDebug() << "MANUAL" << freqHz << mod;
}

void PiScanClient::sendSql(int level)
{
    qDebug() << "SQL" << level;
}

void PiScanClient::onReadyRead()
{
    QByteArray data = m_socket->readAll();
    // TODO: parse ServerToClient protobuf and emit statusUpdated
    emit statusUpdated("154.280 MHz", "SCAN");
}
