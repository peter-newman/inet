

package inet.examples.emulation.tap;

import inet.networklayer.configurator.ipv4.Ipv4NetworkConfigurator;
import inet.node.ethernet.Eth100M;
import inet.node.ethernet.EtherSwitch;
import inet.node.inet.Router;
import inet.node.inet.StandardHost;
import inet.visualizer.integrated.IntegratedVisualizer;

network TapNetPing
{
    @display("bgb=400,400");
    submodules:
        host: StandardHost {
            @display("p=184,181");
        }
        configurator: Ipv4NetworkConfigurator {
            @display("p=76,61");
        }
        visualizer: IntegratedVisualizer {
            @display("p=250,51");
        }
}

network TapNetPingSwitch
{
    @display("bgb=400,400");
    submodules:
        host: StandardHost {
            @display("p=184,181");
        }
        configurator: Ipv4NetworkConfigurator {
            @display("p=76,61");
        }
        visualizer: IntegratedVisualizer {
            @display("p=250,51");
        }
        switch: EtherSwitch {
            @display("p=182,289");
        }
    connections:
        host.ethg++ <--> Eth100M <--> switch.ethg++;
}
