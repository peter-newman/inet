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

import inet.common.IHook;
import inet.linklayer.contract.IExternalInterface;
import inet.linklayer.ethernet.IEtherEncap;


//
// Implements an interface that corresponds to a real interface
// on the host running the simulation. Suitable for hardware-in-the-loop
// simulations.
//
// Requires RealTimeScheduler to be configured as scheduler in omnetpp.ini.
//
module TapInterface like IExternalInterface
{
    parameters:
        @class(InterfaceEntry);
        @display("i=block/ifcard;bgl=53");
        string interfaceTableModule;   // path to the InterfaceTable module
        int mtu @unit(B) = default(4470B);
        int numOutputHooks = default(0);
        int numInputHooks = default(0);
        *.interfaceTableModule = default(absPath(interfaceTableModule));
    gates:
        input upperLayerIn;
        output upperLayerOut;
    submodules:
        outputHook[numOutputHooks]: <default("Nop")> like IHook if numOutputHooks>0 {
            @display("p=117,67");
        }
        inputHook[numInputHooks]: <default("Nop")> like IHook if numInputHooks>0 {
            @display("p=335,67");
        }
        tap: Tap {
            parameters:
                @display("p=234,254");
        }
        encap: <default("EtherEncap")> like IEtherEncap {
            parameters:
                @display("p=234,154");
        }
    connections:
        upperLayerIn --> { @display("m=n"); } --> outputHook[0].in if numOutputHooks > 0;

        upperLayerIn --> { @display("m=n"); } --> encap.upperLayerIn if numOutputHooks == 0;
        for i=0..numOutputHooks-2 {
            outputHook[i].out --> outputHook[i+1].in;
        }
        outputHook[numOutputHooks-1].out --> encap.upperLayerIn if numOutputHooks > 0;

        encap.upperLayerOut --> { @display("m=n"); } --> upperLayerOut if numInputHooks == 0;

        encap.upperLayerOut --> inputHook[0].in if numInputHooks > 0;
        for i=0..numInputHooks-2 {
            inputHook[i].out --> inputHook[i+1].in;
        }
        inputHook[numInputHooks-1].out --> { @display("m=n"); } --> upperLayerOut if numInputHooks > 0;

        encap.lowerLayerOut --> tap.upperLayerIn;
        tap.upperLayerOut --> encap.lowerLayerIn;
}

