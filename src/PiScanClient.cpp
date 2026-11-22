#include "PiScanClient.h"
#include "messages.pb.h"
#include "request.pb.h"
#include "context.pb.h"
#include <QDebug>

PiScanClient::PiScanClient(QObject *parent)
    : QObject(parent)
    , m_socket(new QTcpSocket(this))
    , m_pollTimer(new QTimer(this))
{
    connect(m_socket, &QTcpSocket::readyRead, this, &PiScanClient::onReadyRead);
    connect(m_socket, &QTcpSocket::connected, this, &PiScanClient::onConnected);
    connect(m_pollTimer, &QTimer::timeout, this, &PiScanClient::requestContext);
    m_pollTimer->setInterval(1000);
}

void PiScanClient::connectToServer(const QString &host, quint16 port)
{
    m_socket->connectToHost(host, port);
}

void PiScanClient::onConnected()
{
    emit connected();
    requestContext();
    m_pollTimer->start();
}

void PiScanClient::requestContext()
{
    piscan_pb::ClientToServer msg;
    msg.set_type(piscan_pb::ClientToServer::GENERAL_REQUEST);
    msg.mutable_generalrequest()->set_type(piscan_pb::GeneralRequest::SCANNER_CONTEXT);
    sendClientMessage(QByteArray::fromStdString(msg.SerializeAsString()));
}

void PiScanClient::sendClientMessage(const QByteArray &payload)
{
    if (m_socket->state() == QAbstractSocket::ConnectedState)
        m_socket->write(payload);
}

void PiScanClient::sendScan()
{
    piscan_pb::ClientToServer msg;
    msg.set_type(piscan_pb::ClientToServer::SCANNER_STATE_REQUEST);
    auto *req = msg.mutable_scanstaterequest();
    req->set_handle(m_handle++);
    req->set_state(piscan_pb::ScannerStateRequest::SCAN);
    sendClientMessage(QByteArray::fromStdString(msg.SerializeAsString()));
}

void PiScanClient::sendHold()
{
    piscan_pb::ClientToServer msg;
    msg.set_type(piscan_pb::ClientToServer::SCANNER_STATE_REQUEST);
    auto *req = msg.mutable_scanstaterequest();
    req->set_handle(m_handle++);
    req->set_state(piscan_pb::ScannerStateRequest::HOLD);
    sendClientMessage(QByteArray::fromStdString(msg.SerializeAsString()));
}

void PiScanClient::sendManual(qint64 freqHz, const QString &mod)
{
    piscan_pb::ClientToServer msg;
    msg.set_type(piscan_pb::ClientToServer::SCANNER_STATE_REQUEST);
    auto *req = msg.mutable_scanstaterequest();
    req->set_handle(m_handle++);
    req->set_state(piscan_pb::ScannerStateRequest::MANUAL);
    if (freqHz > 0)
        req->set_manfreq(freqHz);
    req->set_manmodulation(mod.toStdString());
    sendClientMessage(QByteArray::fromStdString(msg.SerializeAsString()));
}

void PiScanClient::sendSql(float level)
{
    piscan_pb::ClientToServer msg;
    msg.set_type(piscan_pb::ClientToServer::DEMOD_REQUEST);
    auto *req = msg.mutable_demodrequest();
    req->set_handle(m_handle++);
    req->set_type(piscan_pb::DemodRequest::SET_SQUELCH);
    req->set_level(level);
    sendClientMessage(QByteArray::fromStdString(msg.SerializeAsString()));
}

void PiScanClient::onReadyRead()
{
    QByteArray data = m_socket->readAll();
    piscan_pb::ServerToClient msg;
    if (!msg.ParseFromArray(data.constData(), data.size()))
        return;

    if (msg.type() == piscan_pb::ServerToClient::SCANNER_CONTEXT && msg.has_scannercontext()) {
        const auto &ctx = msg.scannercontext();
        QString freq = "---.--- MHz";
        if (ctx.has_entrydata() && ctx.entrydata().freq() > 0) {
            double mhz = ctx.entrydata().freq() / 1'000'000.0;
            freq = QString::number(mhz, 'f', 3) + " MHz";
        }
        QString state;
        switch (ctx.state()) {
        case piscan_pb::ScannerContext::SCAN:    state = "SCAN"; break;
        case piscan_pb::ScannerContext::HOLD:    state = "HOLD"; break;
        case piscan_pb::ScannerContext::RECEIVE: state = "RECEIVE"; break;
        default:                                 state = "INVAL"; break;
        }
        emit statusUpdated(freq, state);
    }
}
