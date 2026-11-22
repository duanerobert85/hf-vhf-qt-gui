#pragma once

#include <QObject>
#include <QTcpSocket>

class PiScanClient : public QObject
{
    Q_OBJECT
public:
    explicit PiScanClient(QObject *parent = nullptr);

    void connectToServer(const QString &host = "127.0.0.1", quint16 port = 1234);
    void sendScan();
    void sendHold();
    void sendManual(qint64 freqHz = 0, const QString &mod = "NFM");
    void sendSql(int level = 50);

signals:
    void statusUpdated(const QString &freq, const QString &state);

private slots:
    void onReadyRead();

private:
    QTcpSocket *m_socket;
    void sendRaw(const QByteArray &data);
};
