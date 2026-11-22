#pragma once

#include <QObject>
#include <QTcpSocket>
#include <QTimer>

class PiScanClient : public QObject
{
    Q_OBJECT
public:
    explicit PiScanClient(QObject *parent = nullptr);

    void connectToServer(const QString &host = "127.0.0.1", quint16 port = 1234);
    void sendScan();
    void sendHold();
    void sendManual(qint64 freqHz = 0, const QString &mod = "NFM");
    void sendSql(float level = 50.0f);

signals:
    void statusUpdated(const QString &freq, const QString &state);
    void connected();
    void disconnected();

private slots:
    void onReadyRead();
    void onConnected();
    void requestContext();

private:
    QTcpSocket *m_socket;
    QTimer *m_pollTimer;
    int m_handle = 1;

    void sendClientMessage(const QByteArray &payload);
};
