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

#include "Packet.h"

namespace inet {

Packet::Packet(const Packet& other) :
    cPacket(other),
    data(other.data),
    headerIterator(other.headerIterator),
    trailerIterator(other.trailerIterator)
{
}

Packet::Packet(const char *name, short kind) :
    cPacket(name, kind),
    data(std::make_shared<SequenceChunk>()),
    headerIterator(data->createForwardIterator()),
    trailerIterator(data->createBackwardIterator())
{
}

} // namespace