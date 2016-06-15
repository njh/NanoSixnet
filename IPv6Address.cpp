#include <Arduino.h>
#include "MACAddress.h"
#include "IPv6Address.h"
#include "util.h"

IPv6Address::IPv6Address()
{
    memset(_address, 0, sizeof(_address));
}

void IPv6Address::setLinkLocalPrefix()
{
    _address[0] = 0xfe;
    _address[1] = 0x80;
}

bool IPv6Address::isMulticast() const
{
    return _address[0] == 0xFF;
}

void IPv6Address::setEui64(const MACAddress *macaddr)
{
    _address[8] = (*macaddr)[0] ^ 0x02;
    _address[9] = (*macaddr)[1];
    _address[10] = (*macaddr)[2];
    _address[11] = 0xff;
    _address[12] = 0xfe;
    _address[13] = (*macaddr)[3];
    _address[14] = (*macaddr)[4];
    _address[15] = (*macaddr)[5];
}

uint8_t* IPv6Address::getPtr()
{
    return _address;
}

bool IPv6Address::operator==(const IPv6Address& addr) const
{
    return memcmp(_address, addr._address, sizeof(_address)) == 0;
}

void IPv6Address::print(Print &p) const
{
    for (byte i = 0; i < 16; ++i) {
        printPaddedHex(_address[i], p);
        if (i % 2 == 1 && i < 15)
            p.print(':');
    }
}

void IPv6Address::println(Print &p) const
{
    this->print(p);
    p.println();
}
