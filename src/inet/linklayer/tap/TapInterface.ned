//
// Copyright (C) 2005 Christian Dankbar, Irene Ruengeler, Michael Tuexen
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

package inet.linklayer.tap;

import inet.linklayer.contract.IEthernetInterface;


//
// Implements an interface that corresponds to a real interface
// on the host running the simulation. Suitable for hardware-in-the-loop
// simulations.
//
// Requires RealTimeScheduler to be configured as scheduler in omnetpp.ini.
//
module TapInterface
{
    parameters:
        @class(InterfaceEntry);
        @display("i=block/ifcard;bgl=53");
        string interfaceTableModule;   // path to the InterfaceTable module
        *.interfaceTableModule = default(absPath(interfaceTableModule));
    gates:
        inout phys @labels(EtherFrame);
    submodules:
        tap: Tap {
            parameters:
                @display("p=234,254");
        }
    connections:
        tap.phys <--> { @display("m=s"); } <--> phys;
}

