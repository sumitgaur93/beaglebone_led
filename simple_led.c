/*
===============================================================================
Driver Name		:		simple_led
Author			:		SUMIT
License			:		GPL
Description		:		LINUX DEVICE DRIVER PROJECT
===============================================================================
*/

#include <linux/init.h>
#include <linux/module.h>
#include <linux/ioport.h>
#include <asm/io.h>
#include <asm/irq.h>

#define PIN_28 28            //(1*28+32)=60
#define GPIO_1 0X4804C000
#define GPIO_OE 0X134
#define GPIO_SETDATAOUT 0X194 
#define GPIO_CLEARDATA 0X190
MODULE_LICENSE("GPL");
MODULE_AUTHOR("CDAC");

static void *vaddr;

static int __init simple_led_init(void)
{
	vaddr = ioremap(GPIO_1,4096);
	printk("\nmem_virt_addr = %p",vaddr);

   	iowrite32(0XEFFDFFFF,vaddr+GPIO_OE);
	iowrite32(0X10020000,vaddr+GPIO_SETDATAOUT);
	return 0;
}

static void __exit simple_led_exit(void)
{
	iounmap(vaddr);
	iowrite32(0X10020000,vaddr+GPIO_CLEARDATA);
	printk("exit\n");
	return;
}

module_init(simple_led_init);
module_exit(simple_led_exit);

