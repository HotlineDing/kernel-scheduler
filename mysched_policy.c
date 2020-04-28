#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/proc_fs.h>
#include <linux/kernel.h>
#include <linux/sched/signal.h>
#include <linux/workqueue.h>
#include <linux/sched.h>

MODULE_AUTHOR("Alexander Ding");
MODULE_DESCRIPTION("Custom Scheduler Policy");
MODULE_LICENSE("GPL");

static workqueue_struct* sched_wq;

static DECLARE_DELAYED_WORK(scheduler_hdlr, context_switch);


static int __init  mysched_policy_init(void);
static void __exit mysched_policy_init(void);
module_init(mysched_policy_init);
module_exit(mysched_policy_exit);

static int __init mysched_policy_init(void){
	sched_wq = alloc_workqueue("mysched-workqueue", WQ_UNBOUND, 1);

	if(sched_wq == NULL){
		printk(KERN_ERR "mysched ERROR: Cannot allocate workqueue\n");

		return -ENOMEM;
	}

	return 0;
}

static void __exit mysched_policy_exit(void){
	cancel_delayed_work(&scheduler_hdlr);
	
	flush_workqueue(scheduler_wq);

	destroy_workqueue(scheduler_wq);

	printk(KERN_INFO "mysched is being unloaded\n");
}

