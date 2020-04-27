#include <linux/module.h>
#include <linux/init.h>
#include <linux/errno.h>
#include <linux/fs.h>
#include <linux/proc_fs.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>

MODULE_AUTHOR("Alexander Ding");
MODULE_DESCRIPTION("Custom Scheduler Module");
MODULE_LICENSE("GPL");

#define PROC_CONFIG_FILENAME "mysched_file"

static ssize_t mysched_proc_read(struct file*, char*, size_t, loff_t*);
static ssize_t mysched_proc_write(struct file*, char*, size_t, loff_t*);
static int mysched_proc_open(struct inode*, struct file*);
static int mysched_proc_release(struct inode*, struct file*);


//Custom Shared Structs
static struct mysched_task{
  int pid = 0;

}my_task;

enum task_state{
  init = 0,
  alloced = 1,

};
