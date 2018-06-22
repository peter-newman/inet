Working with Sockets
====================

Overview
--------

The INET Socket API provides special C++ abstractions on top of the
standard OMNeT++ message passing interface for several communication
protocols.

Sockets are most often used by applications and routing protocols to
acccess the corresponding protocol services. Sockets are capable of
communicating with the underlying protocol in a bidirectional way. They
can assemble and send service requests and packets, and they can also
receive service indications and packets.

Applications can simply call the socket class member functions (e.g. , ,
, ) to create and configure sockets, and to send and receive packets.
They may also use several different sockets simulatenously.

The following sections first introduce the shared functionality of
sockets, and then list all INET sockets in detail, mostly by shedding
light on many common usages through examples.

Code fragments in this chapter have been somewhat simplified for
brevity. For example, some modifiers and qualifiers have been omitted,
and some algorithms have been simplified to ease understanding.

Socket Interfaces
~~~~~~~~~~~~~~~~~

Although sockets are always implemented as protocol specific C++
classes, INET also provides C++ socket interfaces. These interfaces
allow writing general C++ code which can handle many different kinds of
sockets all at once.

For example, the interface is implemented by all sockets, and the
interface is implemented by all network protocol sockets.

Identifying Sockets
~~~~~~~~~~~~~~~~~~~

All sockets have a socket identifier which is unique within the network
node. It is automatically assigned to the sockets when they are created.
The identifier can accessed with throughout the lifetime of the socket.

The socket identifier is also passed along in and packet tags. These
tags allow applications and protocols to identify the socket to which s,
service s, and service s belong.

Configuring Sockets
~~~~~~~~~~~~~~~~~~~

Since all sockets work with message passing under the hoods, they must
be configured prior to use. In order to send packets and service
requests on the correct gate towards the underlying communication
protocol, the output gate must be configured:

In contrast, incoming messages such as service indications from the
underlying communication protocol can be received on any application
gate.

Another mandatory configuration for all sockets is setting the socket
callback interface. The callback interface is covered in more detail in
the following section.

Other socket specific configuration options are also available, these
are discussed in the section of the corresponding socket.

Callback Interfaces
~~~~~~~~~~~~~~~~~~~

To ease centralized message processing, all sockets provide a callback
interface which must be implemented by applications. The callback
interface is usually called , and it’s defined as an inner class of the
socket it belongs to. These interfaces often contain some generic
notification methods along with several socket specific methods.

For example, the most common callback method is the one which processes
incoming packets:

Processing Messages
~~~~~~~~~~~~~~~~~~~

In general, sockets can process all incoming messages and update their
state accordingly if necessary. They can automatically dispatch the
received packets and service indications to the appropriate functions in
the interface of the socket.

For example, an applications can simply go through each knonwn socket in
any order, and decide which one should process the received message as
follows:

Sending Data
~~~~~~~~~~~~

All sockets provide one or more functions which send packets using the
current configuration of the socket. The actual means of packet delivery
depends on the underlying communication protocol, but in general the
state of the socket is expected to affect it.

For example, after the socket is properly configured, the application
can start sending packets without attaching any tags, because the socket
takes care of the necessary technical details:

Receiving Data
~~~~~~~~~~~~~~

For example, the application may directly implement the interface of the
socket and print the received data as follows:

Closing Sockets
~~~~~~~~~~~~~~~

Sockets must be closed before deleting them. Closing a socket allows the
underlying communication protocol to release allocated resources. These
resources are often allocated on the local network node, the remote
nework node, or potentially somewhere else in the network.

For example, a socket for a connection oriented protocol must be closed
to release the allocated resources at the peer:

Using Multiple Sockets
~~~~~~~~~~~~~~~~~~~~~~

If the application needs to manage a large number of sockets, for
example in a server application which handles multiple incoming
connections, the generic class may be useful. This class can manage all
kinds of sockets which implement the interface simultaneously.

For example, processing an incoming packet or service indication can be
done as follows:

In order for the to operate properly, sockets must be added to and
removed from it using the and methods respectively.

UDP Socket
----------

The class provides an easy to use C++ interface to send and receive
datagrams.

Configuring Sockets
~~~~~~~~~~~~~~~~~~~

For receiving datagrams on a socket, it must be bound to an address and
a port. Both the address and port is optional. If the address is
unspecified, than all datagrams with any destination address are
received. If the port is -1, then an unused port is selected
automatically by the module. The address and port pair must be unique
within the same network node.

Here is how to bind to a specific local address and local port to
receive datagrams:

There are several other socket options (e.g. receiving broadcasts,
managing multicast groups, setting type of service) which can also be
configured using the class.

Sending Data
~~~~~~~~~~~~

After the socket has been configured, applications can send datagrams to
a remote address and port via a simple function call:

If the application wants to send several datagrams, it can optionally
connect to the destination.

The protocol is in fact connectionless, so when the module receives the
connect request, it simply remembers the remote address and port, and
use it as default destination for later sends.

The application can call connect several times on the same socket.

Receiving Data
~~~~~~~~~~~~~~

Processing packets and indications which are received from the module is
pretty simple. The incoming message must be processed by the socket
where it belongs as shown in the general section.

The deconstructs the message and uses the interface to notify the
application about received data and error indications. The interface
contains only a few functions which are to be implemented by the
application.

For example, the application may directly implement the interface and
print the received data as follows:

TCP Socket
----------

The class provides an easy to use C++ interface to manage connections,
and to send and receive data.

Configuring Sockets
~~~~~~~~~~~~~~~~~~~

Sending Data
~~~~~~~~~~~~

Receiving Data
~~~~~~~~~~~~~~

SCTP Socket
-----------

Configuring Sockets
~~~~~~~~~~~~~~~~~~~

Sending Data
~~~~~~~~~~~~

Receiving Data
~~~~~~~~~~~~~~

IPv4 Socket
-----------

The class provides an easy to use C++ interface to send and receive
datagrams.

Configuring Sockets
~~~~~~~~~~~~~~~~~~~

In order to only receive datagrams which are sent to a specific local
address or contain a specific protocol, the socket can be bound to the
desired local address or protocol.

For example, the following code fragment shows how the INET binds to the
protocol to receive all incoming Echo Reply messages:

For only receiving datagrams from a specific remote address, the socket
can be connected to the desired remote address:

Sending Data
~~~~~~~~~~~~

After the socket has been configured, applications can immediately start
sending datagrams to a remote address via a simple function call:

If the application wants to send several datagrams to the same
destination address, it can optionally connect to the destination:

The protocol is in fact connectionless, so when the module receives the
connect request, it simply remembers the remote address, and uses it as
the default destination address for later sends.

The application can call several times on the same socket.

Receiving Data
~~~~~~~~~~~~~~

Messages received from the module must be processed by the socket where
they belong as shown in the general section. The deconstructs the
message and uses the interface to notify the application about the
received data:

For example, the application may directly implement the interface and
print the received data as follows:

IPv6 Socket
-----------

The class provides an easy to use C++ interface to send and receive
datagrams.

Configuring Sockets
~~~~~~~~~~~~~~~~~~~

In order to only receive datagrams which are sent to a specific local
address or contain a specific protocol, the socket can be bound to the
desired local address or protocol.

For example, the following code fragment shows how the INET binds to the
protocol to receive all incoming Echo Reply messages:

For only receiving datagrams from a specific remote address, the socket
can be connected to the desired remote address:

Sending Data
~~~~~~~~~~~~

After the socket has been configured, applications can immediately start
sending datagrams to a remote address via a simple function call:

If the application wants to send several datagrams to the same
destination address, it can optionally connect to the destination:

The protocol is in fact connectionless, so when the module receives the
connect request, it simply remembers the remote address, and uses it as
the default destination address for later sends.

The application can call several times on the same socket.

Receiving Data
~~~~~~~~~~~~~~

Messages received from the module must be processed by the socket where
they belong as shown in the general section. The deconstructs the
message and uses the interface to notify the application about received
data:

For example, the application may directly implement the interface and
print the received data as follows:

L3 Socket
---------

The class provides an easy to use C++ interface to send and receive
datagrams using the conceptual network protocols: , , , and .

Configuring Sockets
~~~~~~~~~~~~~~~~~~~

Since the class is network protocol agnostic, it must be configured to
connect to a desired network protocol:

In order to only receive datagrams which are sent to a specific local
address or contain a specific protocol, the socket can be bound to the
desired local address or protocol. The conceptual network protocols can
work with the class which contains a of the desired network interface.

For example, the following code fragment shows how the INET binds to the
protocol to receive all incoming Reply messages:

For only receiving datagrams from a specific remote address, the socket
can be connected to the desired remote address:

Sending Data
~~~~~~~~~~~~

After the socket has been configured, applications can immediately start
sending datagrams to a remote address via a simple function call:

If the application wants to send several datagrams to the same
destination address, it can optionally connect to the destination:

The network protocols are in fact connectionless, so when the protocol
module receives the connect request, it simply remembers the remote
address, and uses it as the default destination address for later sends.

The application can call several times on the same socket.

Receiving Data
~~~~~~~~~~~~~~

Messages received from the network protocol module must be processed by
the associated socket where as shown in the general section. The
deconstructs the message and uses the interface to notify the
application about the received data:

For example, the application may directly implement the interface and
print the received data as follows:

TUN Socket
----------

The class provides an easy to use C++ interface to send and receive
datagrams using a interface.

A interface is basically a virtual network interface which is usually
connected to an application (from the outside) instead of other network
devices. It can be used for many networking tasks such as tunneling, or
virtual private networking.

Configuring Sockets
~~~~~~~~~~~~~~~~~~~

A must be associated to a interface before it can be used:

Sending Packets
~~~~~~~~~~~~~~~

As soon as the is associated to a interface, applications can
immediately start sending datagrams via a simple function call:

When the application sends a datagram to a , the packet appears for the
protocol stack within the network node as if the packet were received
from the network.

Receiving Packets
~~~~~~~~~~~~~~~~~

Messages received from the interface must be processed by the
corresponding . The deconstructs the message and uses the interface to
notify the application about the received data:

When the protocol stack within the network node sends a datagram to a
interface, the packet appears for the application which uses a as if the
packet were sent to the network.

TODO

IEEE 802.2 Socket
-----------------

Ethernet Socket
---------------

IEEE 802.11 Socket
------------------
