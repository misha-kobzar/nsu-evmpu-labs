#include <libusb-1.0/libusb.h>
#include <iostream>
#include <cstdio>

void print_device_info(libusb_device *device)
{
    std::libusb_device_descriptor descriptor;
    std::libusb_device_handle *handle = nullptr;

    unsigned char message[200];
    int descriptor_id = libusb_get_device_descriptor(device, &descriptor);

    if (descriptor_id < 0)
    {
        fprintf(stderr, "Ошибка: дескриптор устройства не получен, код: %d.\n", descriptor_id);
        return;
    }

    printf("Класс устройства: %x\n", (int) descriptor.bDeviceClass);
    printf("Идентификатор производителя: %d\n", descriptor.idVendor);
    printf("Идентификатор устройства: %d\n", descriptor.idProduct);

    std::libusb_open(device, &handle);

    if (handle)
    {
        printf("Cерийный номер: ");

        if (descriptor.iSerialNumber)
        {
            descriptor_id = std::libusb_get_string_descriptor_ascii(handle,
                                                                    descriptor.iSerialNumber,
                                                                    message,
                                                                    sizeof(message));

            (descriptor_id > 0) ? printf("%s\n", message) : printf("Нет данных\n");
        }
        else
        {
            printf("Нет данных\n");
        }

        printf("Производитель: ");

        if (descriptor.iManufacturer)
        {
            descriptor_id = std::libusb_get_string_descriptor_ascii(handle,
                                                                    descriptor.iSerialNumber,
                                                                    message,
                                                                    sizeof(message));

            (descriptor_id > 0) ? printf("%s\n", message) : printf("Нет данных\n");
        }
        else
        {
            printf("Нет данных\n");
        }

        printf("Имя устройства: ");

        if (descriptor.iProduct)
        {
            descriptor_id = std::libusb_get_string_descriptor_ascii(handle,
                                                                    descriptor.iSerialNumber,
                                                                    message,
                                                                    sizeof(message));

            (descriptor_id > 0) ? printf("%s\n", message) : printf("Нет данных\n");
        }
        else
        {
            printf("Нет данных\n");
        }
    }
    else
    {
        printf("Доступ к данным закрыт\n");
    }

    std::libusb_close(handle);
}

int main()
{
    std::libusb_device **devices;
    std::libusb_context *context = nullptr;

    ssize_t device_list_size;

    if (std::libusb_init(&context) < 0)
    {
        fprintf(stderr, "Ошибка: инициализация не выполнена.\n");
        return 1;
    }

    device_list_size = std::libusb_get_device_list(context, &devices);

    if (device_list_size < 0)
    {
        fprintf(stderr, "Ошибка: список USB устройств не получен.\n");
        return 1;
    }

    printf("Найдено устройств: %ld\n", device_list_size);

    for (ssize_t i = 0; i < device_list_size; i++)
    {
        printf("\n");

        print_device_info(devices[i]);

        printf("\n");
    }

    std::libusb_free_device_list(devices, 1);
    std::libusb_exit(context);

    return 0;
}