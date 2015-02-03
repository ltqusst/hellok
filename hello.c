#include "common.h"
#include "string.h"
#include "monitor.h"
#include "io.h"
#include "gdt.h"


extern unsigned int bss;
extern unsigned int bss_end;
void kernel_main()
{
	int i,cr0,k;
	int cnt;
	uint8_t bus,  slot,  func;
	uint32_t dev_vendor_id;
	int PCItype, tmp;
	gdt_entry_t * p_gdt_entry;
	for(i=0;i<bss_end-bss;i++) ((char*)bss)[i] = 0;

	clr_scr();
	for(i=0;;i++)
	{
		print_scr(0,0, "Hello World");
		print_scr(0,1,"  iter: %d.", i);

		//cr0 = __get_cr0();
		read_cr0(cr0);
		print_scr(0,2,"  CR0=0x%x", cr0);
		print_scr(0,3,"  Paging :%s; %s mode;",
					cr0 & CR0_PG?"on":"off",
				    cr0 & CR0_PE?"Protected":"Real");

		p_gdt_entry = gdt_base();
		cnt = gdt_cnt();
		print_scr(0,4,"gdt at 0x%x, entry count: %d", p_gdt_entry, cnt);
		/*
		PCItype =0;
		outl(0, 0xCF8);
		outl(0, 0xCFA);

		if ((inl(0xCF8)==0) && (inl(0xCFA)==0))
			PCItype=2;
		else
		{
			tmp=inl(0xCF8);
			outl(0x80000000, 0xCF8);
			if (inl(0xCF8)==0x80000000) PCItype=1;
			outl(tmp, 0xCF8);
		}
		print_scr(0,5,"PCItype=%d", PCItype);
		*/
		cnt = 0;
		bus = 0;
		for(slot=0;slot<32;slot++)
		for(func=0;func<8;func++)
		{
			dev_vendor_id = read_pci_config(bus, slot, func, 0);
			if(dev_vendor_id != 0xffffffff)
			{
				print_scr(0, cnt+6, "BDF=%d/%d/%d  dev_vendr:0x%x",
							bus,slot,func, dev_vendor_id);
				cnt++;

				print_scr(0,cnt+6, " %x,%x,%x,%x,%x,%x",
							read_pci_config(bus, slot, func, 0x10),
							read_pci_config(bus, slot, func, 0x14),
							read_pci_config(bus, slot, func, 0x18),
							read_pci_config(bus, slot, func, 0x1C),
							read_pci_config(bus, slot, func, 0x20),
							read_pci_config(bus, slot, func, 0x24)
							);

				cnt++;
			}
		}
		//while(1);
	}
}

