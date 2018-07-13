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

import inet.linklayer.tap.TapInterface;
import inet.networklayer.common.InterfaceTable;


//
// A ghost host with one Tap interface for connecting the simulation to real world.
//
module TapHost
{
    parameters:
        @networkNode();
        @labels(node,ethernet-node);
        @display("i=device/pc2");
        *.interfaceTableModule = default(absPath(".interfaceTable"));
    gates:
        inout ethg @labels(EtherFrame-conn);
    submodules:
        interfaceTable: InterfaceTable {
            @display("p=100,200;is=s");
        }
        tapInterface: TapInterface {
            @display("p=200,400;q=txQueue");
        }
    connections:
        tapInterface.phys <--> { @display("m=s"); } <--> ethg;
}


