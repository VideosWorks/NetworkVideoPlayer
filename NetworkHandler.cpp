#include "NetworkHandler.h"

char* CommandStrings[11] = {
	"START",
	"BODY",
	"ATTENTION",
	"TRACKED",
	"ENGAGED",
	"LEFT_HAND",
	"RIGHT_HAND",
	"CLOSE",
	"OPEN",
	"UNKNOWN_STATE",
	"END"
};


NetworkHandler::NetworkHandler()
{
	m_udpSocket = new QUdpSocket(this);
}


NetworkHandler::~NetworkHandler()
{
}

bool NetworkHandler::connect()
{
	if (!m_udpSocket) return false;

	m_udpSocket->bind(QHostAddress::LocalHost, 4242);

	QObject::connect(m_udpSocket, &QUdpSocket::readyRead, this, &NetworkHandler::read);
	return true;
}

void NetworkHandler::read()
{
	while (m_udpSocket->hasPendingDatagrams()) {
		QNetworkDatagram datagram = m_udpSocket->receiveDatagram();
		emit incomingData(QString(datagram.data()));
	}
}

void NetworkHandler::write(const QByteArray & data)
{
	if (!m_udpSocket) return;

	m_udpSocket->writeDatagram(data, QHostAddress::LocalHost, 4242);
}
