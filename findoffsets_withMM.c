/* The LibVMI Library is an introspection library that simplifies access to 
 * memory in a target virtual machine or in a file containing a dump of 
 * a system's physical memory.  LibVMI is based on the XenAccess Library.
 *
 * Copyright 2011 Sandia Corporation. Under the terms of Contract
 * DE-AC04-94AL85000 with Sandia Corporation, the U.S. Government
 * retains certain rights in this software.
 *
 * Author: Bryan D. Payne (bdpayne@acm.org)
 *
 * This file is part of LibVMI.
 *
 * LibVMI is free software: you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or (at your
 * option) any later version.
 *
 * LibVMI is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
 * License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with LibVMI.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/sched.h>

#define MYMODNAME "FindOffsets "

static int my_init_module(void);
static void my_cleanup_module(void);

static int
my_init_module(void)
{
    struct task_struct *p = NULL;
    unsigned long commOffset;
    unsigned long tasksOffset;
    unsigned long mmOffset;
    unsigned long pidOffset;
    unsigned long pgdOffset;
    unsigned long addrOffset;
    
    //Offsets for data within mm_struct
    unsigned long total_vm_Offset;  //Size of the process address space (number of pages)
    unsigned long map_count_Offset;  //# of VMAs
    unsigned long mmDataHead_Offset = 0, mmDataTail_Offset = 0;  
    unsigned long mmHeapHead_Offset = 0, mmHeapTail_Offset = 0;
    unsigned long mmStack_Offset = 0;
    unsigned long vmaHead_Offset = 0;  //offset for list of VMAs (struct vm_area_struct *mmap)

    //Offsets for data within mm_struct
    unsigned long vm_start_Offset = 0;
    unsigned long vm_end_Offset = 0;
    unsigned long vm_next_Offset = 0;
    unsigned long vm_prev_Offset = 0;
    unsigned long vm_mm_Offset = 0;  //the address space we belong to (should equal to mmOffset?)

    printk(KERN_ALERT "Module %s loaded.\n\n", MYMODNAME);
    p = current;

    if (p != NULL) {
        commOffset = (unsigned long) (&(p->comm)) - (unsigned long) (p);
        tasksOffset = (unsigned long) (&(p->tasks)) - (unsigned long) (p);
        mmOffset = (unsigned long) (&(p->mm)) - (unsigned long) (p);
        pidOffset = (unsigned long) (&(p->pid)) - (unsigned long) (p);
        pgdOffset = (unsigned long) (&(p->mm->pgd)) - (unsigned long) (p->mm);
        addrOffset = (unsigned long) (&(p->mm->start_code)) - (unsigned long) (p->mm);
	
		//Calculating Offsets within mm_struct
		total_vm_Offset = (unsigned long) (&(p->mm->total_vm)) - (unsigned long) (p->mm);
		map_count_Offset = (unsigned long) (&(p->mm->map_count)) - (unsigned long) (p->mm);
		mmDataHead_Offset = (unsigned long) (&(p->mm->start_data)) - (unsigned long) (p->mm);
		mmDataTail_Offset = (unsigned long) (&(p->mm->end_data)) - (unsigned long) (p->mm);
		mmHeapHead_Offset = (unsigned long) (&(p->mm->start_brk)) - (unsigned long) (p->mm);
		mmHeapTail_Offset = (unsigned long) (&(p->mm->brk)) - (unsigned long) (p->mm);
		mmStack_Offset = (unsigned long) (&(p->mm->start_stack)) - (unsigned long) (p->mm);
		vmaHead_Offset = (unsigned long) (&(p->mm->mmap)) - (unsigned long) (p->mm);
		
		//Calculating Offsets within vm_area_struct (VMA)
		vm_start_Offset = (unsigned long) (&(p->mm->mmap->vm_start)) - (unsigned long) (p->mm->mmap);
		vm_end_Offset = (unsigned long) (&(p->mm->mmap->vm_end)) - (unsigned long) (p->mm->mmap);
		vm_next_Offset = (unsigned long) (&(p->mm->mmap->vm_next)) - (unsigned long) (p->mm->mmap);
		vm_prev_Offset = (unsigned long) (&(p->mm->mmap->vm_prev)) - (unsigned long) (p->mm->mmap);
		vm_mm_Offset = (unsigned long) (&(p->mm->mmap->vm_mm)) - (unsigned long) (p->mm->mmap);
		
		
		
        printk(KERN_ALERT "[domain name] {\n");
        printk(KERN_ALERT "    ostype = \"Linux\";\n");
        printk(KERN_ALERT "    sysmap = \"[insert path here]\";\n");
        printk(KERN_ALERT "    linux_name = 0x%x;\n", (unsigned int) commOffset);
        printk(KERN_ALERT "    linux_tasks = 0x%x;\n", (unsigned int) tasksOffset);
        printk(KERN_ALERT "    linux_mm = 0x%x;\n", (unsigned int) mmOffset);
        printk(KERN_ALERT "    linux_pid = 0x%x;\n", (unsigned int) pidOffset);
        printk(KERN_ALERT "    linux_pgd = 0x%x;\n", (unsigned int) pgdOffset);
        
        //Printing offsets locateed within mm_struct
        printk(KERN_ALERT "    linux_total_vm = 0x%x;\n", (unsigned int) total_vm_Offset);
        printk(KERN_ALERT "    linux_map_count = 0x%x;\n", (unsigned int) map_count_Offset);
        printk(KERN_ALERT "    linux_mmDataHead = 0x%x;\n", (unsigned int) mmDataHead_Offset);
        printk(KERN_ALERT "    linux_mmDataTail = 0x%x;\n", (unsigned int) mmDataTail_Offset);
        printk(KERN_ALERT "    linux_mmHeapHead = 0x%x;\n", (unsigned int) mmHeapHead_Offset);
        printk(KERN_ALERT "    linux_mmHeapTail = 0x%x;\n", (unsigned int) mmHeapTail_Offset);
        printk(KERN_ALERT "    linux_mmStack = 0x%x;\n", (unsigned int) mmStack_Offset);
        printk(KERN_ALERT "    linux_vmaHead = 0x%x;\n", (unsigned int) vmaHead_Offset);
        
        //Printing offsets locateed within vma_area_struct
        printk(KERN_ALERT "    linux_vm_start_Offset = 0x%x;\n", (unsigned int) vm_start_Offset);
        printk(KERN_ALERT "    linux_vm_end_Offset = 0x%x;\n", (unsigned int) vm_end_Offset);
        printk(KERN_ALERT "    linux_vm_next_Offset = 0x%x;\n", (unsigned int) vm_next_Offset);
        printk(KERN_ALERT "    linux_vm_prev_Offset = 0x%x;\n", (unsigned int) vm_prev_Offset);
        printk(KERN_ALERT "    linux_vm_mm_Offset = 0x%x;\n", (unsigned int) vm_mm_Offset);
        
        
        printk(KERN_ALERT "}\n");   
    }
    else {
        printk(KERN_ALERT
               "%s: found no process to populate task_struct.\n",
               MYMODNAME);
    }

    return 0;
}

static void my_cleanup_module(void)
{
    printk(KERN_ALERT "Module %s unloaded.\n", MYMODNAME);
}

module_init(my_init_module);
module_exit(my_cleanup_module);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Nilushan Silva");
MODULE_DESCRIPTION("task_struct offset Finder");
