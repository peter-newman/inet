//
// Copyright (C) 2003 Andras Varga; CTIE, Monash University, Australia
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program; if not, see <http://www.gnu.org/licenses/>.
//

package inet.node.emulation;

import inet.linklayer.contract.IEthernetInterface;
import inet.linklayer.tap.Tap;
import inet.networklayer.common.InterfaceTable;


//
// A ghost host with one Tap interface for connecting the simulation to real world.
//
module TapHost
{
    parameters:
        int numTapInterfaces = default(0);  // minimum number of tap interfaces
        @networkNode();
        @labels(node,ethernet-node);
        @display("i=device/pc2");
        *.interfaceTableModule = default(absPath(".interfaceTable"));
        eth[*].encap.typename = "EtherEncapDummy";
    gates:
        inout ethg[numTapInterfaces] @labels(EtherFrame-conn) @allowUnconnected;
    submodules:
        interfaceTable: InterfaceTable {
            @display("p=76,104;is=s");
        }
        tap[sizeof(ethg)]: Tap {
            @display("p=253,104;q=txQueue");
        }
        eth[sizeof(ethg)]: <default("EthernetInterface")> like IEthernetInterface {
            parameters:
                @display("p=253,240,row,150;q=txQueue");
        }
    connections:
        for i=0..sizeof(ethg)-1 {
            tap[i].lowerLayerOut --> eth[i].upperLayerIn;
            tap[i].lowerLayerIn <-- eth[i].upperLayerOut;
            ethg[i] <--> { @display("m=s"); } <--> eth[i].phys;
        }
}

