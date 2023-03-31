#include "buttonhandler.h"
#include <libusb-1.0/libusb.h>
#include<unistd.h>

#include <QDebug>

static const int VENDOR_ID = 0x0079;
static const int PRODUCT_ID = 0x0006;
static const int ENDPOINT_ADDRESS = 0x81;

ButtonHandler::ButtonHandler()
{

}

void* event_thread(void* arg)
{
    libusb_context* ctx = (libusb_context*)arg;
    while (1) {
        libusb_handle_events(ctx);
    }
    return NULL;
}

void ButtonHandler::handleButtonPress()
{
    libusb_device_handle* dev_handle;
    libusb_device** device_list;
    libusb_context* context = nullptr;
    ssize_t num_devices;
    int error = 0;

    // Initialize libusb
    error = libusb_init(&context);
    if (error != LIBUSB_SUCCESS) {
        qDebug() << "Failed to initialize libusb: " << libusb_strerror((enum libusb_error)error);
        return;
    }

    // Get the list of USB devices connected to the system
    num_devices = libusb_get_device_list(context, &device_list);
    if (num_devices < 0) {
        qDebug() << "Failed to get device list: " << libusb_strerror((enum libusb_error)num_devices);
        libusb_exit(context);
        return;
    }

    // Find the USB device with the specified vendor and product IDs
    for (ssize_t i = 0; i < num_devices; i++) {
        libusb_device* device = device_list[i];
        libusb_device_descriptor descriptor;
        error = libusb_get_device_descriptor(device, &descriptor);
        if (error != LIBUSB_SUCCESS) {
            qDebug() << "Failed to get device descriptor: " << libusb_strerror((enum libusb_error)error);
            continue;
        }

        if (descriptor.idVendor == VENDOR_ID && descriptor.idProduct == PRODUCT_ID) {

            // Open the USB device and claim the interface
            error = libusb_open(device, &dev_handle);
            if (error != LIBUSB_SUCCESS) {
                qDebug() << "Failed to open device: " << libusb_strerror((enum libusb_error)error);
                continue;
            }
            libusb_detach_kernel_driver(dev_handle, 0); //drop the drive of usb
            error = libusb_claim_interface(dev_handle, 0);
            if (error != LIBUSB_SUCCESS) {
                qDebug() << "Failed to claim interface: " << libusb_strerror((enum libusb_error)error);
                libusb_close(dev_handle);
                continue;
            }

            // Poll the USB device for button presses
            qDebug() << "Waiting for button press...";
            while (true) {
                unsigned char buffer[8];
                int transferred;
                error = libusb_interrupt_transfer(dev_handle, ENDPOINT_ADDRESS, buffer, sizeof(buffer), &transferred, 1000);
                if (error == LIBUSB_SUCCESS && transferred == sizeof(buffer)) {
                    switch(buffer[5]){
                        case 0x1f:
                            qDebug() << "Button 1 pressed!";
                            sleep(1);
                            break;
                        case 0x2f:
                            qDebug() << "Button 2 pressed!";
                            sleep(1);
                            break;
                        case 0x4f:
                            qDebug() << "Button 3 pressed!";
                            sleep(1);
                            break;
                        case 0x8f:
                            qDebug() << "Button 4 pressed!";
                            sleep(1);
                            break;
                        default:
                            switch(buffer[6]){
                            case 0x1:
                                qDebug() << "Button 5 pressed!";
                                sleep(1);
                                break;
                            case 0x2:
                                qDebug() << "Button 6 pressed!";
                                sleep(1);
                                break;
                            case 0x4:
                                qDebug() << "Button 7 pressed!";
                                sleep(1);
                                break;
                            case 0x8:
                                qDebug() << "Button 8 pressed!";
                                sleep(1);
                                break;
                            }
                    }
                }
                //debug
//                 for (int i = 0; i < sizeof(buffer); i++) {
//                     qDebug() << static_cast<int>(buffer[i]) << " ";
//                 }
            }

            // Release the claimed interface and close the USB device
            libusb_release_interface(dev_handle, 0);
            libusb_close(dev_handle);
            break;
        }
    }

    // Free the list of USB devices and exit libusb
    libusb_free_device_list(device_list, 1);
    libusb_exit(context);

    return;

}
