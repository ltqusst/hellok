/*
 * io.h
 *
 *  Created on: Feb 2, 2015
 *      Author: tingqian
 */

#ifndef IO_H_
#define IO_H_

#include "common.h"

//==============================================================================
// from linux: arch/x86/boot/boot.h
/* Basic port I/O */
static inline void outb(u8 v, u16 port)
{
        asm volatile("outb %0,%1" : : "a" (v), "dN" (port));
}
static inline u8 inb(u16 port)
{
        u8 v;
        asm volatile("inb %1,%0" : "=a" (v) : "dN" (port));
        return v;
}
static inline void outw(u16 v, u16 port)
{
        asm volatile("outw %0,%1" : : "a" (v), "dN" (port));
}
static inline u16 inw(u16 port)
{
        u16 v;
        asm volatile("inw %1,%0" : "=a" (v) : "dN" (port));
        return v;
}
static inline void outl(u32 v, u16 port)
{
        asm volatile("outl %0,%1" : : "a" (v), "dN" (port));
}
static inline u32 inl(u16 port)
{
        u32 v;
        asm volatile("inl %1,%0" : "=a" (v) : "dN" (port));
        return v;
}

//==============================================================================

static __inline__ void __set_bit(int nr, volatile void * addr)
{
	__asm__(
	"btsl %1,%0"
	:"=m" (addr) /* %0      = means output; m means memory operand */
	:"Ir" (nr)); /* %1		Ir means immediate/register operand */
}
//==============================================================================

#define CR0_PG (1<<31)
#define CR0_PE (1<<0)

#define read_cr0(cr0) __asm__("mov %%cr0,%%eax;mov %%eax,%0;":"=m" (cr0)::)
static __inline__ unsigned int __get_cr0(void)
{
	unsigned int cr0;
	__asm__(
	"mov %%cr0,%%eax;"
	"mov %%eax,%0;"
	:"=m" (cr0)::); /* %0      = means output; m means memory operand */
	return cr0;
}

// from linux: /arch/x86/pci/early.c
// offset's lowerst 2-bit must be zero
u32 read_pci_config(u8 bus, u8 slot, u8 func, u8 offset)
{
        u32 v;
        outl(0x80000000 | (bus<<16) | (slot<<11) | (func<<8) | (offset & 0xfc), 0xcf8);
        v = inl(0xcfc);
        //if (v != 0xffffffff)
        //       pr_debug("%x reading 4 from %x: %x\n", slot, offset, v);
        return v;
}

u8 read_pci_config_byte(u8 bus, u8 slot, u8 func, u8 offset)
{
        u8 v;
        outl(0x80000000 | (bus<<16) | (slot<<11) | (func<<8) | (offset & 0xfc), 0xcf8);
        v = inb(0xcfc + (offset&3));
        //pr_debug("%x reading 1 from %x: %x\n", slot, offset, v);
        return v;
}

u16 read_pci_config_16(u8 bus, u8 slot, u8 func, u8 offset)
{
        u16 v;
        outl(0x80000000 | (bus<<16) | (slot<<11) | (func<<8) | (offset & 0xfc), 0xcf8);
        v = inw(0xcfc + (offset&2));
        //pr_debug("%x reading 2 from %x: %x\n", slot, offset, v);
        return v;
}
#endif /* IO_H_ */
