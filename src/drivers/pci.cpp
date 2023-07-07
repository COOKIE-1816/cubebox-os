#include "drivers/pci.h"
#include "kernel/common.h"
#include "kernel/kdrivers.h"

using namespace PCI;
using namespace Kernel::Kdrivers;

pci_device *pci_devices = 0;
uint32_t devs = 0;

pci_driver *pci_drivers = 0;
uint32_t drivs = 0;

uint16_t PCI::readWord(      uint16_t __bus, 
                            uint16_t __slot, 
                            uint16_t __func, 
                            uint16_t __offset) {

    uint64_t address;
    uint64_t lbus =  (uint64_t) __bus;
    uint64_t lslot = (uint64_t) __slot;
    uint64_t lfunc = (uint64_t) __func;
    uint16_t tmp = 0;

    address = (uint64_t)    ((lbus << 16)       | 
                            (lslot << 11)       |
                            (lfunc << 8)        | 
                            (__offset & 0xfc)   | 
                            ((uint32_t)0x80000000));
    outb(0xCF8, address);
    
    tmp = (uint16_t)((inb(0xCFC) >> ((__offset & 2) * 8)) & 0xffff);
    return (tmp);
}

void PCI::addDevice(pci_device __device) {
    pci_devices[devs] = __device;
    devs++;

    //return;
}

uint16_t PCI::getVendor( uint16_t __bus, 
                        uint16_t __device, 
                        uint16_t __function) {

    uint32_t r0 = readWord(__bus, __device, __function, 0);
    return r0;
}

uint16_t PCI::getDeviceId(   uint16_t __bus, 
                            uint16_t __device, 
                            uint16_t __function) {
    
    uint32_t r0 = readWord(__bus, __device, __function, 2);
    return r0;
}

uint16_t PCI::getClassId(    uint16_t __bus,
                            uint16_t __device,
                            uint16_t __function) {

    uint32_t r0 = readWord(__bus, __device, __function, 0xA);
    return (r0 & ~0x00FF) >> 8;
}

uint16_t PCI::getSubClassId( uint16_t __bus,
                            uint16_t __device,
                            uint16_t __function) {
    
    uint32_t r0 = readWord(__bus, __device, __function, 0xA);
    return (r0 & ~0x00FF);
}

/*void pci_probe() {
    for(uint32_t bus = 0; bus < 256; bus++) {
        for(uint32_t slot = 0; slot < 32; slot++) {
            for(uint32_t function = 0; function < 8; function++) {
                    uint16_t vendor = pci_getVendor(bus, slot, function);
                    
                    if(vendor == 0xffff) 
                        continue;
                    
                    uint16_t device = pci_getDeviceID(bus, slot, function);
                    //mprint("vendor: 0x%x device: 0x%x\n", vendor, device);

                    struct pci_device pdev = (pci_device)malloc(sizeof(pci_device));

                    pdev->vendor    = vendor;
                    pdev->device    = device;
                    pdev->func      = function;
                    pdev->driver    = 0;

                    pci_addDevice(pdev);
            }
        }
    }
}*/

/*uint16_t pci_checkVendor(uint8_t __bus, uint8_t __slot) {
    uint16_t vendor, device;
    
    if ((vendor = pci_configReadWord(__bus, __slot, 0, 0)) != 0xFFFF) {
       device = pci_configReadWord(__bus, __slot, 0, 2);
       //. . .
    } return (vendor);
}*/

void pci_init() {

    kdriver pci;
    pci.name = "PCI BUS";

    statusMsg_create(pci);

    devs = drivs = 0;

	//pci_devices = (pci_device **)malloc(32 * sizeof(pci_device));
	//pci_drivers = (pci_driver **)malloc(32 * sizeof(pci_driver));
	
    //pci_probe();

    statusMsg_status(KDRIVERS_OK);
}