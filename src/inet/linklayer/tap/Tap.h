//
// Copyright (C) 2004 Andras Varga
// Copyrigth (C) 2005 Christian Dankbar, Irene Ruengeler, Michael Tuexen
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, see <http://www.gnu.org/licenses/>.
//

// This file is based on the Ppp.h of INET written by Andras Varga.

#ifndef __INET_EXT_H
#define __INET_EXT_H

#ifndef MAX_MTU_SIZE
#define MAX_MTU_SIZE    4000
#endif // ifndef MAX_MTU_SIZE

#include <pcap.h>
#include "inet/common/INETDefs.h"
#include "inet/common/scheduler/RealTimeScheduler.h"
#include "inet/linklayer/base/MacBase.h"

namespace inet {

// Forward declarations:
class InterfaceEntry;

/**
 * Implements an interface that corresponds to a real interface
 * on the host running the simulation. Suitable for hardware-in-the-loop
 * simulations.
 *
 * Requires RealTimeScheduler to be configured as scheduler in omnetpp.ini.
 *
 * See NED file for more details.
 */
class INET_API Tap : public MacBase, public RealTimeScheduler::ICallback
{
  protected:
    RealTimeScheduler *rtScheduler = nullptr;
    bool connected = false;
    uint8_t buffer[1 << 16];      //TODO allocate buffer related on MTU value
    unsigned long bufferLength = sizeof(buffer);
    std::string device;
    MacAddress macAddress;
    Ipv4Address ipv4Address;
    Ipv4Address ipv4Netmask;
    int mtu;

    // statistics
    int numSent = 0;
    int numRcvd = 0;
    int numDropped = 0;

    // access to tap interface via Scheduler class:
    int fd = INVALID_SOCKET;        // tap socket ID
    int datalink = -1;

  protected:
    virtual void refreshDisplay() const override;

    // MacBase functions
    InterfaceEntry *createInterfaceEntry() override;
    virtual void flushQueue() override;
    virtual void clearQueue() override;
    virtual bool isUpperMsg(cMessage *msg) override { return msg->arrivedOn("upperLayerIn"); }
    void initializeMacAddress();
    void initializeIpv4Address();
    void encapsulate(Packet *frame);
    void decapsulate(Packet *packet);

    // RealTimeScheduler::ICallback:
    virtual bool notify(int fd) override;

    // utility functions
    void sendBytes(unsigned char *buf, size_t numBytes, struct sockaddr *from, socklen_t addrlen);

  public:
    virtual ~Tap();
    virtual int numInitStages() const override { return NUM_INIT_STAGES; }
    virtual void initialize(int stage) override;
    virtual void handleMessage(cMessage *msg) override;

    virtual void finish() override;
};

} // namespace inet

#endif // ifndef __INET_EXTINTERFACE_H

