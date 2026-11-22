#pragma once

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include "PiScanClient.h"

class ScannerWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit ScannerWindow(QWidget *parent = nullptr);

private slots:
    void onStatusUpdated(const QString &freq, const QString &state);
    void onScanClicked();
    void onHoldClicked();
    void onManualClicked();
    void onSqlClicked();

private:
    QLabel *m_freqLabel;
    QLabel *m_stateLabel;
    PiScanClient *m_client;
};
