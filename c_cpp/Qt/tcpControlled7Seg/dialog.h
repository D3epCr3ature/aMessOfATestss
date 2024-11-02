#ifndef DIALOG_H
#define DIALOG_H

#include <QComboBox>
#include <QDialog>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>

#include "segmentDisplay.h"

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

private slots:
    void toggleConnection(void);
    void connectionSucessToClient(void);
    void readCltRequest(void);

private:
    void initServer(void);
    void fillIpComboBox(void);

    QGridLayout *mainLayout = nullptr;

    QComboBox *ipComboBox  = nullptr;
    QLabel *ipLbl   = nullptr;
    QLineEdit *portLinEdit = nullptr;
    QLabel *portLbl = nullptr;

    bool serverStatus = false;
    QTcpServer *tcpServer = nullptr;
    QDataStream inStream;
    QTcpSocket *cltConnection = nullptr;

    QPushButton *toggleSvrStatusBtn = nullptr;

    SegmentsDisplay display;
};
#endif // DIALOG_H
