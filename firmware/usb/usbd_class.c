#include <stdlib.h>

#include "usbd_class.h"
#include "usbd_desc.h"
#include "usb_conf.h"
#include <string.h>
#include "hal.h"

#define MAX_PACKET_SIZE 64 

static uint8_t need_zlp = 0;
static uint8_t packet_sent = 0;
static uint16_t tx_buf[MAX_PACKET_SIZE / sizeof(uint16_t)];
static uint8_t bRequest;

static uint8_t init_cb(void* pdev, uint8_t cfgidx) {
    return USBD_OK;
}

static uint8_t deinit_cb(void* pdev, uint8_t cfgidx) {
    return USBD_OK;
}

static uint8_t setup_cb(void* pdev, USB_SETUP_REQ* req) {
    // Only accept vendor requests
    if((req->bmRequest & USB_REQ_TYPE_MASK) != USB_REQ_TYPE_VENDOR) {
        USBD_CtlError(pdev, req);
        return USBD_FAIL;
    }

    bRequest = req->bRequest;

    switch(req->bRequest) {
        case REQUEST_DRIVE_COIL:
            if(req->wValue) {
                read_on();
                drive_coil();
            } else {
                read_off();
                float_coil();
            }
            return USBD_OK;

        default:
            return USBD_FAIL;
    }
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

static void try_tx(void* pdev) {
      uint16_t items_available;

      if(packet_sent) return;

      items_available = items_to_read();

      if(items_available >= MAX_PACKET_SIZE / sizeof(uint16_t)) {
            read_items(tx_buf, MAX_PACKET_SIZE / sizeof(uint16_t));
            need_zlp = 1;
            DCD_EP_Tx (pdev,
                   IN_EP,
                   (uint8_t*)tx_buf,
                   MAX_PACKET_SIZE);
            packet_sent = 1;
      }
      //else if(rx_idle() && (bytes_available || need_zlp)) {
      //    read_bytes(USB_Tx_Buffer, bytes_available);
      //    need_zlp = 0;
      //    DCD_EP_Tx (pdev,
      //               CDC_IN_EP,
      //               USB_Tx_Buffer,
      //               bytes_available);
      //    packet_sent = 1;
      //}
}

static uint8_t tx_cb(void *pdev, uint8_t epnum) {
    // If 64 bytes available for read, send them out
    packet_sent = 0;
    try_tx(pdev);

    return USBD_OK;
}

static uint8_t sof_cb(void *pdev) {
    try_tx(pdev);
    return USBD_OK;
}

USBD_Class_cb_TypeDef  USBD_custom_cb = {
    init_cb,
    deinit_cb,
    setup_cb,
    NULL, /*EP0_TxSent*/
    ctl_rx_cb, /*EP0_RxReady*/
    NULL, //tx_cb, /*DataIn*/
    NULL, /*DataOut*/
    NULL, //sof_cb, /*SOF */
    config_cb,
};
