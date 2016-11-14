#include "usbd_core.h"

#define USB_REQ_TYPE_VENDOR 0x40

extern USBD_Class_cb_TypeDef USBD_custom_cb;

#define REQUEST_DRIVE_COIL 0x20
