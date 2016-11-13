#include <stdlib.h>

#include "usbd_class.h"
#include "usbd_desc.h"
#include "usb_conf.h"
#include <string.h>

#define TX_BUF_SIZE 128

static uint8_t tx_buf[TX_BUF_SIZE];
static uint8_t bRequest;

static uint8_t init_cb(void* pdev, uint8_t cfgidx) {
    return USBD_OK;
}

static uint8_t deinit_cb(void* pdev, uint8_t cfgidx) {
    return USBD_OK;
}

static uint8_t setup_cb(void* pdev, USB_SETUP_REQ* req) {
    return USBD_FAIL;
}

static uint8_t ctl_rx_cb(void *pdev) {
    return USBD_FAIL;
}

const uint8_t config_descriptor[] = {
    0x09,   /* bLength: Configuration Descriptor size */
    USB_CONFIGURATION_DESCRIPTOR_TYPE ,   /* bDescriptorType: Configuration */
    0x12,   /* wTotalLength (LSB) */
    0x00,   /* wTotalLength (MSB) */
    0x01,   /* bNumberInterfaces: 1 interface */
    0x01,   /* bConfigurationValue */
    0x00,   /* iConfiguration: Index of string descriptor for this config */
    0x80,   /* bmAttributes: bus powered */
    0x32,   /* bMaxPower: 100 mA */

    0x09,   /* bLength: interface descriptor size */
    USB_INTERFACE_DESCRIPTOR_TYPE, /* bDescriptorType: Interface */
    0x00, /* bInterfaceNumber: Number of Interface */
    0x00, /* bAlternateSetting: Alternate setting */
    0x00, /* bNumEndpoints: one control endpoint */
    0xFF, /* bInterfaceClass: user's interface for vendor class */
    0x00, /* bInterfaceSubClass : */
    0x00, /* nInterfaceProtocol : None */
    0x05, /* iInterface: */
};

static uint8_t* config_cb(uint8_t speed, uint16_t* length) {
    *length = sizeof(config_descriptor);
    return (uint8_t*)config_descriptor;
}

USBD_Class_cb_TypeDef  USBD_custom_cb = {
  init_cb,
  deinit_cb,
  setup_cb,
  NULL, /*EP0_TxSent*/
  ctl_rx_cb, /*EP0_RxReady*/
  NULL, /*DataIn*/
  NULL, /*DataOut*/
  NULL, /*SOF */
  config_cb,
};
