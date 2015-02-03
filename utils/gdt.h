/*
 * gdt.h
 *
 *  Created on: Feb 2, 2015
 *      Author: tingqian
 */

#ifndef GDT_H_
#define GDT_H_


//==============================================================================
// This structure contains the value of one GDT entry.
// We use the attribute 'packed' to tell GCC not to change
// any of the alignment in the structure.
struct gdt_entry_struct
{
   u16int limit_low;           // The lower 16 bits of the limit.
   u16int base_low;            // The lower 16 bits of the base.
   u8int  base_middle;         // The next 8 bits of the base.
   union{
	   u8int  data;              // Access flags, determine what ring this segment can be used in.
	   struct
	   {
		   u8int Type:4;
		   u8int DT:1;
		   u8int DPL:2;
		   u8int P:1;
	   }bits;
   }access;
   union{
	   u8int  data;
	   struct
	   {
		   u8int limit_high:4;
		   u8int A:1;
		   u8int Zero:1;
		   u8int D:1;
		   u8int G:1;
	   }bits;
   }granularity;
   u8int  base_high;           // The last 8 bits of the base.
} __attribute__((packed));

struct gdt_ptr_struct
{
   u16int limit;               // The upper 16 bits of all selector limits.
   u32int base;                // The address of the first gdt_entry_t struct.
}__attribute__((packed));

typedef struct gdt_entry_struct gdt_entry_t;
typedef struct gdt_ptr_struct gdt_ptr_t;

static inline gdt_entry_t * gdt_base(void)
{
	gdt_ptr_t gdt;
	asm volatile("sgdt %0;":"=m" (gdt)::);
	return (gdt_entry_t*)gdt.base;
}
static inline int gdt_cnt(void)
{
	gdt_ptr_t gdt;
	asm volatile("sgdt %0;":"=m" (gdt)::);
	return (gdt.limit/sizeof(gdt_entry_t)) + 1;
}

#endif /* GDT_H_ */
