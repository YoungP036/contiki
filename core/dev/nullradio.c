#include "dev/nullradio.h"


/*---------------------------------------------------------------------------*/
static int
init(void)
{
  return 0;
}
/*---------------------------------------------------------------------------*/
static int
prepare(const void *payload, unsigned short payload_len)
{
  return 1;
}
/*---------------------------------------------------------------------------*/
static int
transmit(unsigned short transmit_len)
{
  return RADIO_TX_OK;
}
/*---------------------------------------------------------------------------*/
static int
send(const void *payload, unsigned short payload_len)
{
  prepare(payload, payload_len);
  return transmit(payload_len);
}
/*---------------------------------------------------------------------------*/
static int
read(void *buf, unsigned short buf_len)
{
  return 0;
}
/*---------------------------------------------------------------------------*/
static int
channel_clear(void)
{
  return 1;
}
/*---------------------------------------------------------------------------*/
static int
receiving_packet(void)
{
  return 0;
}
/*---------------------------------------------------------------------------*/
static int
pending_packet(void)
{
  return 0;
}
/*---------------------------------------------------------------------------*/
static int
on(void)
{
  return 0;
}
/*---------------------------------------------------------------------------*/
static int
off(void)
{
  return 0;
}
/*---------------------------------------------------------------------------*/
static int
no_capabilities(void)
{
  return 0;   /* no element of the radio_capabilities_e enum is returned */
}
/*---------------------------------------------------------------------------*/
static int
dummy_get_config_const(radio_const_t cst_id)
{
  return RADIO_CONF_UNAVAILABLE_CONST;
}
/*---------------------------------------------------------------------------*/
static int
dummy_set_param(radio_param_t param_id, unsigned short value)
{
  return RADIO_CONF_UNAVAILABLE_PARAM;
}
/*---------------------------------------------------------------------------*/
static int
dummy_get_param(radio_param_t param_id)
{
  return RADIO_CONF_UNAVAILABLE_PARAM;
}
/*---------------------------------------------------------------------------*/
const struct radio_driver nullradio_driver =
  {
    init,
    prepare,
    transmit,
    send,
    read,
    channel_clear,
    receiving_packet,
    pending_packet,
    on,
    off,
    no_capabilities,
    dummy_get_config_const,
    dummy_set_param,
    dummy_get_param,
  };
/*---------------------------------------------------------------------------*/
