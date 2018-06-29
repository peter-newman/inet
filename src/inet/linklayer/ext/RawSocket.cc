//
// Copyright (C) OpenSim Ltd.
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
//

#define WANT_WINSOCK2

#include <omnetpp/platdep/sockets.h>
#include <net/if.h>
#include <arpa/inet.h>

#include "inet/common/INETUtils.h"
#include "inet/common/ModuleAccess.h"
#include "inet/common/packet/chunk/BytesChunk.h"
#include "inet/common/packet/Packet.h"
#include "inet/common/ProtocolTag_m.h"
#include "inet/linklayer/ext/RawSocket.h"
#include "inet/networklayer/common/InterfaceEntry.h"

namespace inet {

Define_Module(RawSocket);

RawSocket::~RawSocket()
{
    close(fd);
    fd = INVALID_SOCKET;
}

void RawSocket::initialize(int stage)
{
    cSimpleModule::initialize(stage);
    if (stage == INITSTAGE_LOCAL) {
        device = par("device");
        fd = socket(AF_INET, SOCK_RAW, IPPROTO_RAW);
        if (fd == INVALID_SOCKET)
            throw cRuntimeError("RawSocket interface: Root privileges needed");
        const int32 on = 1;
        if (setsockopt(fd, IPPROTO_IP, IP_HDRINCL, (char *)&on, sizeof(on)) < 0)
            throw cRuntimeError("RawSocket: couldn't set sockopt for raw socket");
        // bind to interface:
        struct ifreq ifr;
        memset(&ifr, 0, sizeof(ifr));
        snprintf(ifr.ifr_name, sizeof(ifr.ifr_name), "%s", device);
        if (setsockopt(fd, SOL_SOCKET, SO_BINDTODEVICE, (void *)&ifr, sizeof(ifr)) < 0)
            throw cRuntimeError("RawSocket: couldn't bind raw socket to '%s' interface", device);

        numSent = numDropped = 0;
        WATCH(numSent);
        WATCH(numDropped);
    }
}

void RawSocket::handleMessage(cMessage *msg)
{
    Packet *packet = check_and_cast<Packet *>(msg);
    auto protocol = packet->getTag<PacketProtocolTag>()->getProtocol();
    if (protocol != &Protocol::ipv4)
        throw cRuntimeError("ExtInterface accepts ipv4 packets only");

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
#if !defined(linux) && !defined(__linux) && !defined(_WIN32)
    addr.sin_len = sizeof(struct sockaddr_in);
#endif // if !defined(linux) && !defined(__linux) && !defined(_WIN32)
    addr.sin_port = htons(0);
    auto bytesChunk = packet->peekAllAsBytes();
    uint8 buffer[1 << 16];
    size_t packetLength = bytesChunk->copyToBuffer(buffer, sizeof(buffer));
    ASSERT(packetLength == (size_t)packet->getByteLength());

    sendBytes(buffer, packetLength, (struct sockaddr *)&addr, sizeof(struct sockaddr_in));
    numSent++;
    delete packet;
}

void RawSocket::sendBytes(uint8 *buf, size_t numBytes, struct sockaddr *to, socklen_t addrlen)
{
    //TODO check: is this an IPv4 packet --OR-- is this packet acceptable by fd socket?
    if (fd == INVALID_SOCKET)
        throw cRuntimeError("RawSocket::sendBytes(): no raw socket.");

    int sent = sendto(fd, buf, numBytes, 0, to, addrlen);    //note: no ssize_t on MSVC

    if ((size_t)sent == numBytes)
        EV << "Sent " << sent << " bytes packet.\n";
    else
        EV << "Sending packet FAILED! (sendto returned " << sent << " (" << strerror(errno) << ") instead of " << numBytes << ").\n";
    return;
}

void RawSocket::refreshDisplay() const
{
    char buf[80];
    sprintf(buf, "device: %s\nsnt:%d", device, numSent);
    getDisplayString().setTagArg("t", 0, buf);
}

void RawSocket::finish()
{
    std::cout << getFullPath() << ": " << numSent << " packets sent, " << numDropped << " packets dropped.\n";
    close(fd);
    fd = INVALID_SOCKET;
}

} // namespace inet

