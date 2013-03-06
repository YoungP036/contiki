/**
 * \addtogroup dev
 * @{
 */

/**
 * \defgroup radio Radio API
 *
 * The radio API module defines a set of functions that a radio device
 * driver must implement.
 *
 * @{
 */

/*
 * Copyright (c) 2005, Swedish Institute of Computer Science.
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
 * 3. Neither the name of the Institute nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE INSTITUTE AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE INSTITUTE OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * This file is part of the Contiki operating system.
 *
 */

/**
 * \file
 *         Header file for the radio API
 * \author
 *         Adam Dunkels <adam@sics.se>
 * Additional modifications by Kévin Roussel <Kevin.Roussel@inria.fr>
 */

#ifndef __RADIO_H__
#define __RADIO_H__


/** additional functions ("capabilities") provided by radio transceivers */
enum radio_capabilities_e {

  /** radio transceiver can change channel on-the-fly */
  RADIO_CAN_CHANGE_CHANNEL       = 0x01,
  /** radio transceiver can change short address on-the-fly */
  RADIO_CAN_CHANGE_SHORT_ADDRESS = 0x02,
  /** radio transceiver can change PAN identifier on-the-fly */
  RADIO_CAN_CHANGE_PAN_ID        = 0x04,
  /** radio transceiver can change IEEE address on-the-fly */
  RADIO_CAN_CHANGE_IEEE_ADDRESS  = 0x08,
  /** radio transceiver emitting power can be changed */
  RADIO_CAN_SET_TX_POWER         = 0x10,
  /** last known RSSI can be consulted */
  RADIO_CAN_GET_RSSI             = 0x20,
  /** CCA threshold can be modified */
  RADIO_CAN_SET_CCA_THRESHOLD    = 0x40,
  /** radio transceiver can be set in "promiscuous" mode */
  RADIO_CAN_USE_PROMISCUOUS_MODE = 0x80,
  // any other addition here...

};

/** configuration constants (for capabilities) of radio transceivers */
typedef enum radio_const_e {

  /** minimal value for working channel -- usually 11 for 802.15.4 */
  RADIO_MIN_CHANNEL,
  /** maximal value for working channel -- usually 26 for 802.15.4 */
  RADIO_MAX_CHANNEL,
  /** minimal value for emitting power */
  RADIO_MIN_TX_POWER,
  /** maximal value for emitting power */
  RADIO_MAX_TX_POWER,

} radio_const_t;

/** configuration parameters (for capabilities) of radio transceivers */
typedef enum radio_param_e {

  /** working channel (= frequency) used by the radio transceiver */
  RADIO_CHANNEL,
  /** current short (16-bit) address used by the radio transceiver */
  RADIO_SHORT_ADDRESS,
  /** current PAN ID (16-bit) used by the radio transceiver */
  RADIO_PAN_ID,
  /** current IEEE (64-bit) address used by the radio transceiver */
  RADIO_IEEE_ADDRESS,
  /** transmission power */
  RADIO_TX_POWER,
  /** latest radio signal strength capted */
  RADIO_RSSI,
  /** Clear-Channel Assessment threshold */
  RADIO_CCA_THRESHOLD,
  /** set/unset promiscuous mode */
  RADIO_PROMISCUOUS_MODE,

} radio_param_t;


/**
 * The structure of a device driver for a radio in Contiki.
 */
struct radio_driver {

  int (* init)(void);
  
  /** Prepare the radio with a packet to be sent. */
  int (* prepare)(const void *payload, unsigned short payload_len);

  /** Send the packet that has previously been prepared. */
  int (* transmit)(unsigned short transmit_len);

  /** Prepare & transmit a packet. */
  int (* send)(const void *payload, unsigned short payload_len);

  /** Read a received packet into a buffer. */
  int (* read)(void *buf, unsigned short buf_len);

  /** Perform a Clear-Channel Assessment (CCA) to find out if there is
      a packet in the air or not. */
  int (* channel_clear)(void);

  /** Check if the radio driver is currently receiving a packet */
  int (* receiving_packet)(void);

  /** Check if the radio driver has just received a packet */
  int (* pending_packet)(void);

  /** Turn the radio on. */
  int (* on)(void);

  /** Turn the radio off. */
  int (* off)(void);

  /** Get the list of additional properties of the radio transceiver */
  int (* get_capabilities)(void);

  /** Get configuration constant(s) of the radio transceiver */
  int (* get_config_const)(radio_const_t cst_id);

  /** Set a config parameter of the radio transceiver */
  int (* set_param)(radio_param_t param_id, unsigned short value);

  /** Get a config parameter of the radio transceiver */
  int (* get_param)(radio_param_t param_id);
};

/* Generic radio return values... */
enum {

  /* ... of transmission functions */
  RADIO_TX_OK,
  RADIO_TX_ERR,
  RADIO_TX_COLLISION,
  RADIO_TX_NOACK,

  /* ... of configuration functions */
  RADIO_CONF_OK                = 0,
  RADIO_CONF_UNKNOWN_CONST     = -100,
  RADIO_CONF_UNKNOWN_PARAM     = -101,
  RADIO_CONF_UNAVAILABLE_CONST = -102,
  RADIO_CONF_UNAVAILABLE_PARAM = -103,
  RADIO_CONF_READ_ONLY_PARAM   = -104,
  RADIO_CONF_WRITE_ONLY_PARAM  = -105,

};

#endif /* __RADIO_H__ */


/** @} */
/** @} */

