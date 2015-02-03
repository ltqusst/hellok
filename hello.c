#include "common.h"
#include "string.h"
#include "monitor.h"
#include "io.h"
#include "gdt.h"

int probe_func(u8 bus, u8 slot, u8 func, int y)
{
	u32 dev_vendor_id;
	u32 class_sub_prog_rev;
	u8 header_type;
	int x = 0;
	dev_vendor_id = read_pci_config_u32(bus, slot, func, 0);
	if((dev_vendor_id & 0xFFFF) == 0xffff) return 0;

	header_type = read_pci_config_u8(bus, slot, 0, 0xe);
	class_sub_prog_rev = read_pci_config_u32(bus, slot, func, 0x08);
	x += print_scr(x, y, "BDF=%d/%d/%d(%s) dev_vendor:0x%08X   class:0x%08X",
						  bus,slot,func, header_type&0x80?"MF":"  ", dev_vendor_id, class_sub_prog_rev);
	return 1;
}
int probe_dev(u8 bus, u8 slot, int y)
{
	int x = 0, func = 0, cnt = 0;
	u16 dev_id;
	u32 class_sub_prog_rev;
	u8 header_type;

	if(probe_func(bus, slot, 0, y + 0) == 0) return 0;

	header_type = read_pci_config_u8(bus, slot, 0, 0xe);
	cnt = 1;
	if(header_type & 0x80){
		for(func=1;func<8;func++)
		{
			if(probe_func(bus, slot, func, y + cnt)) cnt++;
		}
	}
	return cnt;
}

extern unsigned int bss;
extern unsigned int bss_end;
void kernel_main()
{
	int i,cr0,k,y;
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
		y = 6;
		bus = 0;
		for(slot=0;slot<32;slot++)
		{
			y += probe_dev(bus, slot, y);
		}
		//while(1);
	}
}

