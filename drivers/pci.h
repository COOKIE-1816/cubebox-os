#ifndef _CB_PCI_H_
#define _CB_PCI_H_

#include <stdint.h>

struct pci_driver;

typedef struct {
	uint32_t            vendor;
	uint32_t            device;
	uint32_t            func;
	struct pci_driver   *driver;
} pci_device;

typedef struct {
	uint32_t vendor;
	uint32_t device;
	uint32_t func;
} pci_device_id;

typedef struct __pci_driver {
	pci_device_id*          table;
	char*                   name;
	uint8_t (*init_one)     (pci_device *);
	uint8_t (*init_driver)  (void);
	uint8_t (*exit_driver)  (void);
} pci_driver;

uint16_t pci_readWord(      uint16_t __bus, 
                            uint16_t __slot, 
                            uint16_t __func, 
                            uint16_t __offset);

//uint16_t pci_checkVendor(uint8_t __bus, uint8_t __slot);

void pci_addDevice(pci_device __device);

uint16_t pci_getVendor(     uint16_t __bus, 
                            uint16_t __device, 
                            uint16_t __function);

uint16_t pci_getDeviceId(   uint16_t __bus, 
                            uint16_t __device, 
                            uint16_t __function);

uint16_t pci_getClassId(    uint16_t __bus,
                            uint16_t __device,
                            uint16_t __function);

uint16_t pci_getSubClassId( uint16_t __bus,
                            uint16_t __device,
                            uint16_t __function);

void pci_init();

#endif