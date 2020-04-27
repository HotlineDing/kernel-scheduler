#include <linux/module.h>
#include <linux/init.h>
#include <linux/errno.h>
#include <linux/fs.h>
#include <linux/proc_fs.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>
#include <mysched.h>

MODULE_AUTHOR("Alexander Ding");
MODULE_DESCRIPTION("Custom Scheduler Module");
MODULE_LICENSE("GPL");

#define PROC_CONFIG_FILENAME "mysched_file"

static ssize_t mysched_proc_read(struct file*, char*, size_t, loff_t*);
static ssize_t mysched_proc_write(struct file*, char*, size_t, loff_t*);
static int mysched_proc_open(struct inode*, struct file*);
static int mysched_proc_release(struct inode*, struct file*);


//Kernel Object
static struct file_operations mysched_fops{
  .owner = THIS_MODULE;
  .read  = mysched_proc_read;
  .write = mysched_proc_write;
  .open  = mysched_proc_open;
  .release = mysched_proc_release;
};

//Kernel Object
static struct proc_dir_entry* mysched_proc_file_entry;

static int __init mysched_init(void){
  printk(KERN_INFO "INIT myscheduler\n");

  //Kernel Call
  mysched_proc_file_entry = proc_create(PROC_CONFIG_FILENAME, 0777, NULL, &mysched_fops);
  if(mysched_proc_file_entry == NULL) {
    printk(KERN_ALERT "ERROR: Could not create proc file at /proc/%s\n", PROC_CONFIG_FILENAME);
    return -ENOMEM;
  }

  return 0;
}

//Custom Callback Function
//Invoked when user tries to write to PROC_CONFIG_FILENAME
//buf is the new_proc_id that User wants to schedule
static ssize_t mysched_proc_write(struct file* file, char* buf, size_t count, loff_t* ppos){
  long int new_proc_id = 0;

  //Kernel call
  int retval = kstrtol(buf, BASE_10, &new_proc_id);
  if(retval < 0) {return -EINVAL;}

  ret = add_newprocess(new_proc_id);
  if(ret != 1){
    return -ENOMEM;
  }

  return count;
}

static ssize_t mysched_proc_read(struct file* file, char* buf, size_t count, loff_t* ppos){return 0;}
static int mysched_proc_open(struct inode* inode, struct file* file){return 0;}
static int mysched_proc_release(struct inode* inode, struct file* file){return 0;}


static int __exit mysched_exit(void){
  printk(KERN_INFO "Cleaning up and exiting mysched.\n");

  proc_remove(mysched_proc_file_entry);
}

module_init(mysched_init);
module_exit(mysched_exit);
