#include "dialog.h"

#include <cstdint>
#include <QComboBox>
#include <QDataStream>
#include <QDialog>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QtNetwork/QNetworkInterface>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include <QPushButton>
#include <QRegularExpression>

#define HEXA_16BITS_NDIGITS  2*sizeof(uint16_t)
#define HEXA_32BITS_NDIGITS  2*sizeof(uint32_t)
#define NUMERICAL_BASE_16   16
#define TO_UINT8(DIGIT) (DIGIT) - '0'

/** **************************************************************************
 * @brief Main dialog window's constructor
 *************************************************************************** */
Dialog::Dialog(QWidget *parent) : QDialog(parent) {
    display.setPainterScaleX(.6);
    display.setPainterScaleY(.6);
    display.setSegmentColor(0, QColor(10,10,10));
    display.setSegmentColor(1, QColor(10,10,10));
    display.setSegmentColor(2, QColor(10,10,10));
    display.setSegmentColor(3, QColor(10,10,10));
    display.setSegmentColor(4, QColor(10,10,10));
    display.setSegmentColor(5, QColor(10,10,10));
    display.setSegmentColor(6, QColor(10,10,10));

    ipLbl = new QLabel("IP   :");
    ipLbl->setFont({ "Source Code Pro" });
    ipComboBox = new QComboBox;
    fillIpComboBox();

    portLbl = new QLabel("Port :");
    portLbl->setFont({ "Source Code Pro" });
    portLinEdit = new QLineEdit;
    portLinEdit->setText("XXXX");
    portLinEdit->setReadOnly(true);

    toggleSvrStatusBtn = new QPushButton("Launch server into space");
    connect(toggleSvrStatusBtn, &QPushButton::clicked,
            this, &Dialog::toggleConnection);

    tcpServer = new QTcpServer(this);
    connect(tcpServer, &QTcpServer::newConnection,
            this, &Dialog::connectionSucessToClient);

    inStream.setByteOrder(QDataStream::LittleEndian);

    mainLayout = new QGridLayout(this);
    mainLayout->addWidget(ipLbl, 0, 0);
    mainLayout->addWidget(ipComboBox, 0, 1);
    mainLayout->addWidget(portLbl, 1, 0);
    mainLayout->addWidget(portLinEdit, 1, 1);
    mainLayout->addWidget(toggleSvrStatusBtn, 2, 0, 1, 2);
    mainLayout->addWidget(&display, 3, 0, 1, 2);

    resize(220, 505);
}

/** **************************************************************************
 * @brief Dialog window's destructor
 *************************************************************************** */
Dialog::~Dialog() {
    delete(ipLbl);
    delete(ipComboBox);
    delete(portLbl);
    delete(portLinEdit);
    delete(toggleSvrStatusBtn);
    delete(tcpServer);
    delete(mainLayout);
}

/** **************************************************************************
 * @brief Client's request reader
 *************************************************************************** */
void Dialog::readCltRequest(void) {
    inStream.startTransaction();

    QByteArray streamAsBytes;
    inStream >> streamAsBytes;

    if ( ! inStream.commitTransaction() )   return;

    /* REGEX part: ^\!
     *             C[3-4]
     *             N(([A-F]|[a-f]|[0-9]){4}),
     *             (([A-F]|[a-f]|[0-9]){8})+
     *             \$$
     * Accept data, like:  1data  - !C3N0001,00123456$
                          10datas - !C3N000A,00112233...AABBCCDD$ */
    static QRegularExpression re("^\\!C[3-4]N(([A-F]|[a-f]|[0-9]){4}),"
                                 "(([A-F]|[a-f]|[0-9]){8})+\\$$");
    if (re.match(streamAsBytes).hasMatch()) {
        /* Remove starting "!C" & terminating '$' sequences */
        streamAsBytes.remove(0, 2);
        streamAsBytes.removeLast();

        uint16_t n;
        uint32_t tmp;
        uint8_t  comp;
        uint8_t  r, g, b, w;

        /* Extract composants & # of data (16bits <=> 4 hexa digits) */
        bool okDbg = true;
        comp = TO_UINT8(streamAsBytes.at(0));   /* -'0': From char to uint8 */
        streamAsBytes.remove(0, 2);             /* Remove digit + 'N' */
        /* ISSUE: Below not working?!?!
         * Hypothesis: Not isolated, so doesn't work with suffix */
        //n = streamAsBytes.toUShort(&okDbg, NUMERICAL_BASE_16);
        n = streamAsBytes.first(HEXA_16BITS_NDIGITS)
                            .toUShort(&okDbg, NUMERICAL_BASE_16);
        /* Remove digits + ',' before datas */
        streamAsBytes.remove(0, HEXA_16BITS_NDIGITS+1);

        /* Check MAX limit & overwrite value if needed */
        if (n > display.getNSegments())
            n = display.getNSegments();

        if (comp == 3) {
            for (uint16_t i = 0; i < n; i++) {
                /* ISSUE: Below not working?!?!
                 * Hypothesis: Not isolated on last value,
                 *             so doesn't work with suffix */
                //tmp = streamAsBytes.toUInt(&okDbg, NUMERICAL_BASE_16);
                tmp = streamAsBytes.first(HEXA_32BITS_NDIGITS)
                                    .toUInt(&okDbg, NUMERICAL_BASE_16);
                streamAsBytes.remove(0, HEXA_32BITS_NDIGITS);

                r = (tmp & 0x000000FF);
                g = (tmp & 0x0000FF00) >>  8;
                b = (tmp & 0x00FF0000) >> 16;
                display.setSegmentColor(i, QColor(r, g, b));
            }
        } else if (comp == 4) {
            /* Treat 4 components as one WHITE channel
             * and, for now, set all channels to this value */
            for (uint32_t i = 0; i < n; i++) {
                //tmp = streamAsBytes.toUInt(&okDbg, NUMERICAL_BASE_16);
                tmp = streamAsBytes.first(HEXA_32BITS_NDIGITS)
                                    .toUInt(&okDbg, NUMERICAL_BASE_16);
                streamAsBytes.remove(0, 8);

                w = (tmp & 0xFF000000) >> 24;
                display.setSegmentColor(i, QColor(w, w, w));
            }
        } else  return; /* Do nothing and end function */

        display.update();
    }

    /** Detect client's leave
     *  + toLower() Hypothesis:
     *  Upper -> Lower is optimized because UpperCase + offset = LowerCase
     *  instead of a substraction LowerCase - offset = UpperCase */
    if (streamAsBytes.toLower() == QByteArray("leaving"))
        cltConnection = nullptr;
}

/** Not a working solution for the above function, but MIGHT investigate
 *  how-to do it properly, to compare performance */
/*QDataStream ds(streamAsBytes);
ds.setByteOrder(QDataStream::LittleEndian);
QChar c;
quint8 r, g, b, w;
ds >> c;
ds >> r;
ds >> g;
ds >> b;
if (streamAsBytes.size() == 10)
    ds >> w;
QMessageBox::information(this, tr("RGB"),
                         tr("Matching with length %1 & "
                            "R[%2], G[%3], B[%4]")
                             .arg(streamAsBytes.size())
                             .arg(r).arg(g).arg(b));*/

/** **************************************************************************
 * @brief Client's connection approval
 *************************************************************************** */
void Dialog::connectionSucessToClient(void) {
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setByteOrder(QDataStream::LittleEndian);

    /* /!\ Doesn't work properly using C string (out << "Hi";) /!\
     * Answer: It might be because a C-string is then cast as a QString and
     *         this stores each data as uint16_t instead of uint8_t */
    out << QByteArray("Connection successful");

    if ( ! cltConnection ) {
        cltConnection = tcpServer->nextPendingConnection();
        connect(cltConnection, &QAbstractSocket::disconnected,
                cltConnection, &QObject::deleteLater);

        inStream.setDevice(cltConnection);
        connect(cltConnection, &QIODevice::readyRead,
                this, &Dialog::readCltRequest);
    }

    cltConnection->write(block);
    cltConnection->flush();
}

/** **************************************************************************
 * @brief TCP Server toggling connection
 *************************************************************************** */
void Dialog::toggleConnection(void) {
    ipComboBox->setEnabled(serverStatus);

    serverStatus = !serverStatus;

    if (serverStatus) {
        toggleSvrStatusBtn->setText("Kill server");

        initServer();
        portLinEdit->setText(QString("%1").arg(tcpServer->serverPort()));
    } else {
        toggleSvrStatusBtn->setText("Launch server into space");
        if (cltConnection) {
            /* Send a leaving message to inform the client and
             * allow it to reset its state as
             * QTcpSocket::disconnectFromHost() is used below */
            QByteArray block;
            QDataStream out(&block, QIODevice::WriteOnly);
            out.setByteOrder(QDataStream::LittleEndian);

            /* /!\ Does not work properly using C string (out << "Hi";) /!\
             * Answer: It might be because a C-string is then cast as
             *         a QString and this stores each data
             *         as uint16_t instead of uint8_t */
            out << QByteArray("Leaving");

            cltConnection->write(block);
            cltConnection->flush();

            cltConnection->disconnectFromHost();
            cltConnection = nullptr;
        }
        tcpServer->close();
    }
}

/** **************************************************************************
 * @brief TCP Server initialization
 * @note  Generate a new port each time, just as a coding simplification
 *************************************************************************** */
void Dialog::initServer(void) {
    if ( ! tcpServer->listen(QHostAddress(ipComboBox->currentText())) ) {
        QMessageBox::critical(this, tr("Socket's server"),
                              tr("Unable to start the server: %1.")
                                  .arg(tcpServer->errorString()));
        close();
        return;
    }

    portLinEdit->setText(QString("%1").arg(tcpServer->serverPort()));
}

/** **************************************************************************
 * @brief IP finder to fill dedicated ComboBox
 *************************************************************************** */
void Dialog::fillIpComboBox(void) {
    // Add IPv4 localhost
    ipComboBox->addItem(QHostAddress(QHostAddress::LocalHost).toString());

    // Add non-localhost IPv4 addresses
    const QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    for (const QHostAddress &entry : ipAddressesList) {
        if (entry != QHostAddress::LocalHost && entry.toIPv4Address())
            ipComboBox->addItem(entry.toString());
    }
}
