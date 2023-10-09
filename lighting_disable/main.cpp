#include <vector>
#include <iostream>
#include <hidapi.h>

int main() {
    if (hid_init() != 0) {
        std::cerr << "Failed to initialize HIDAPI" << std::endl;
        return -1;
    }

    auto message = std::vector<unsigned char> {
        0x5d,
        0xb3,
        0x00,
        0x00, // mode

        0x00, // r
        0x00, // g
        0x00, // b

        0x00, // speed
        0x00, // direction

        0x00, // r
        0x00, // g
        0x00, // b
    };

    auto message_set = std::vector<unsigned char> {
        0x5d, 0xb5, 0, 0, 0,
    };

    auto message_apply = std::vector<unsigned char> {
        0x5d, 0xb4,
    };

    hid_device_info* devs = hid_enumerate(0x0b05, 0x0);
    hid_device_info* cur_dev = devs;

    while (cur_dev) {
        hid_device* device = hid_open_path(cur_dev->path);

        if (device) {
            hid_send_feature_report(device, message.data(), message.size());
            hid_send_feature_report(device, message_set.data(), message_set.size());
            hid_send_feature_report(device, message_apply.data(), message_apply.size());
            hid_close(device);
        }

        cur_dev = cur_dev->next;
    }

    hid_free_enumeration(devs);

    hid_exit();

    return 0;
}