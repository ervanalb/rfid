#include "usbd_core.h"

#define USB_REQ_TYPE_VENDOR 0x40

extern USBD_Class_cb_TypeDef USBD_custom_cb;

#define REQUEST_LED_READ     0x20
#define REQUEST_LED_WRITE    0x21
#define REQUEST_LED_SPOOF    0x22
#define REQUEST_COIL_DRIVE   0x23
#define REQUEST_COIL_TUNE    0x24
#define REQUEST_STREAM_READ  0x25
#define REQUEST_STREAM_WRITE 0x26
