#include <libusb-1.0/libusb.h>
#include <iostream>
#include <cstdio>

using namespace std;

void print_device_info(libusb_device *device) 
{
	libusb_device_descriptor descriptor;
	libusb_device_handle *handle = nullptr;

	unsigned char message[200];
	int descriptor_id = libusb_get_device_descriptor(device, &descriptor);
	
	if (descriptor_id < 0) 
	{
		fprintf(stderr, "Ошибка: дескриптор устройства не получен, код: %d.\n", descriptor_id);
		return;
	}

	printf("Класс устройства: %x\n", (int)descriptor.bDeviceClass);
	printf("Идентификатор производителя: %d\n", descriptor.idVendor);
	printf("Идентификатор устройства: %d\n", descriptor.idProduct);

	libusb_open(device, &handle);

	if (handle) 
	{	
		printf("Cерийный номер: ");

		if (descriptor.iSerialNumber) 
		{
			descriptor_id = libusb_get_string_descriptor_ascii(handle,
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
			descriptor_id = libusb_get_string_descriptor_ascii(handle,
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
			descriptor_id = libusb_get_string_descriptor_ascii(handle,
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

	libusb_close(handle);
}

int main() 
{
	libusb_device **devices;
	libusb_context *context = nullptr;

	ssize_t device_list_size;

	if (libusb_init(&context) < 0) 
	{
		fprintf(stderr, "Ошибка: инициализация не выполнена.\n");
		return 1;
	}

	device_list_size = libusb_get_device_list(context, &devices);

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

	libusb_free_device_list(devices, 1);
	libusb_exit(context);

	return 0;
}
