/*
 * Copyright (c) 2012-2013, Thingsquare, http://www.thingsquare.com/.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE
 * COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#include <MACAddress.h>

#ifndef ENC28J60_H
#define ENC28J60_H


/**
 * Send and receive Ethernet packets directly using a ENC28J60 controller.
 */
class ENC28J60 {

public:
    /**
     * Constructor that uses the default hardware SPI pins
     * @param cs the Arduino Chip Select / Slave Select pin
     */
    ENC28J60(int8_t cs);

    /**
     * Constructor for using software SPI, with custom set of pins
     * @param clk the SPI Clock pin
     * @param miso the SPI Master In / Slave Out pin
     * @param mosi the SPI Master Out / Slave In pin
     * @param cs the Arduino Chip Select / Slave Select pin
     */
    ENC28J60(int8_t clk, int8_t miso, int8_t mosi, int8_t cs);

    /**
     * Initialise the Ethernet controller
     * Must be called before sending or receiving Ethernet packets
     * @param enc_mac_addr the local MAC address
     */
    void init(const MACAddress *enc_mac_addr);

    /**
     * Send an Ethernet packet
     * @param data a pointer to the data to send
     * @param datalen the length of the data in the packet
     * @return 
     */
    int send(const uint8_t *data, uint16_t datalen);

    /**
     * Read an Ethernet packet
     * @param buffer a pointer to a buffer to write the packet to
     * @param bufsize the available space in the buffer
     * @return the length of the received packet
     *         or 0 if no packet was received
     */
    int read(uint8_t *buffer, uint16_t bufsize);

protected:

    /**
     * The MAC address of this Ethernet controller
     * @private
     */
    MACAddress enc_mac_addr;

private:

    uint8_t is_mac_mii_reg(uint8_t reg);
    uint8_t readreg(uint8_t reg);
    void writereg(uint8_t reg, uint8_t data);
    void setregbitfield(uint8_t reg, uint8_t mask);
    void clearregbitfield(uint8_t reg, uint8_t mask);
    void setregbank(uint8_t new_bank);
    void writedata(const uint8_t *data, int datalen);
    void writedatabyte(uint8_t byte);
    int readdata(uint8_t *buf, int len);
    uint8_t readdatabyte(void);
    void softreset(void);
    uint8_t readrev(void);
    void reset(void);

    void enc28j60_arch_spi_init(void);
    uint8_t enc28j60_arch_spi_write(uint8_t data);
    uint8_t enc28j60_arch_spi_read(void);
    void enc28j60_arch_spi_select(void);
    void enc28j60_arch_spi_deselect(void);

    // Previously defined in contiki/core/sys/clock.h
    void clock_delay_usec(uint16_t dt);


    uint8_t initialized;
    uint8_t bank;

    int8_t _cs, _clk, _mosi, _miso;

};

#endif /* ENC28J60_H */
