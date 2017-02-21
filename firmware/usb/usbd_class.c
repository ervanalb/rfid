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
static uint8_t initialized = 0;

static uint8_t init_cb(void* pdev, uint8_t cfgidx) {
    DCD_PMA_Config(pdev, IN_EP, USB_SNG_BUF, BULK_IN_TX_ADDRESS);

    // Open EP IN
    DCD_EP_Open(pdev, IN_EP, MAX_PACKET_SIZE, USB_EP_BULK);

    initialized = 1;

    return USBD_OK;
}

static uint8_t deinit_cb(void* pdev, uint8_t cfgidx) {
    /* Close EP IN */
    DCD_EP_Close(pdev, IN_EP);

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
        case REQUEST_LED_READ:
            if(req->wValue) {
                led_read_on();
            } else {
                led_read_off();
            }
            return USBD_OK;
        case REQUEST_LED_WRITE:
            if(req->wValue) {
                led_write_on();
            } else {
                led_write_off();
            }
            return USBD_OK;
        case REQUEST_LED_SPOOF:
            if(req->wValue) {
                led_spoof_on();
            } else {
                led_spoof_off();
            }
            return USBD_OK;
        case REQUEST_COIL_DRIVE:
            if(req->wValue) {
                coil_tune();
                coil_drive();
            } else {
                coil_float();
            }
            return USBD_OK;
        case REQUEST_COIL_TUNE:
            if(req->wValue) {
                coil_tune();
            } else {
                coil_float();
                coil_detune();
            }
            return USBD_OK;
        case REQUEST_STREAM_READ:
            if(req->wValue) {
                stream_read_enable();
            } else {
                stream_read_disable();
            }
            return USBD_OK;
        case REQUEST_STREAM_WRITE:
            if(req->wValue) {
                stream_write_enable();
            } else {
                stream_write_disable();
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
    0x19,   /* wTotalLength (LSB) */
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
    0x01, /* bNumEndpoints: one endpoint */
    0xFF, /* bInterfaceClass: user's interface for vendor class */
    0x00, /* bInterfaceSubClass : */
    0x00, /* nInterfaceProtocol : None */
    0x05, /* iInterface: */

    /*Endpoint IN Descriptor*/
    0x07,   /* bLength: Endpoint Descriptor size */
    USB_ENDPOINT_DESCRIPTOR_TYPE,      /* bDescriptorType: Endpoint */
    IN_EP,                             /* bEndpointAddress */
    0x02,                              /* bmAttributes: Bulk */
    LOBYTE(MAX_PACKET_SIZE),      /* wMaxPacketSize: */
    HIBYTE(MAX_PACKET_SIZE),
    0x00                               /* bInterval: ignore for Bulk transfer */
};

static uint8_t* config_cb(uint8_t speed, uint16_t* length) {
    *length = sizeof(config_descriptor);
    return (uint8_t*)config_descriptor;
}

static void try_tx(void* pdev) {
      uint16_t samples_available;

      if(packet_sent) return;

      samples_available = stream_read_available();

      if(samples_available >= MAX_PACKET_SIZE / sizeof(uint16_t)) {
            stream_read(tx_buf, MAX_PACKET_SIZE / sizeof(uint16_t));
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
    if(!initialized) return USBD_OK;

    try_tx(pdev);
    return USBD_OK;
}

USBD_Class_cb_TypeDef  USBD_custom_cb = {
    init_cb,
    deinit_cb,
    setup_cb,
    NULL, /*EP0_TxSent*/
    ctl_rx_cb, /*EP0_RxReady*/
    tx_cb, /*DataIn*/
    NULL, /*DataOut*/
    sof_cb, /*SOF */
    config_cb,
};
