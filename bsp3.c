#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/version.h>
#include <linux/fs.h>
#include <linux/fcntl.h>
#include <linux/ctype.h>
#include <linux/cdev.h>
#include <linux/slab.h>
#include <linux/vmalloc.h>
#include <linux/pagemap.h>
#include <linux/errno.h>
#include <linux/types.h>
#include <linux/kthread.h>
#include <linux/timer.h>
#include <linux/sched.h>
#include <linux/ktime.h>
#include <linux/jiffies.h>
#include <linux/semaphore.h>

#define DEVN 111
#define DEV_NAME "BSP"
#define DES "BSP_TEST305"
#define START 1
#define END 100
#define INTERVAL1 jiffies + HZ
#define INTERVAL2 jiffies + 2 * HZ

struct timer_list timer1, timer2;

struct task_struct *kth1, *kth2;

struct semaphore sem1, sem2;

int v1, v2;

//when timer1 arrive time 1s run this function
static void _timer1(void) {
	printk("%s_THREAD1: %d\n", DES, v1);
	up(&sem1);
}

//when timer2 arrive time 2s run this fucntion
static void _timer2(void) {
	printk("%s_THREAD2: %d\n", DES, v2);
	up(&sem2);
}

//init and start timer1
static void start_timer1(void) {
	timer_setup(&timer1, (void *)_timer1, 0);
	timer1.expires = INTERVAL1;
	add_timer(&timer1);
}

//init and start timer2
static void start_timer2(void) {
	timer_setup(&timer2, (void *)_timer2, 0);
	timer2.expires = INTERVAL2;
	add_timer(&timer2);
}

//thread1 run this function 1-100 1s
static void _kth1(void) {
	down(&sem1);
	for(v1 = START + 1; v1 <= END; v1 += 1) {
		mod_timer(&timer1, INTERVAL1);
		down(&sem1);
	}
}

//thread2 run this function 1-100 2s
static void _kth2(void) {
	down(&sem2);
	for(v2 = START + 1; v2 <= END; v2 += 1) {
		mod_timer(&timer2, INTERVAL2);
		down(&sem2);
	}
}

//open
static int bsp_open(struct inode *inodp, struct file *filp) {
	v1 = START;
	v2 = START;

	sema_init(&sem1, 0);
	sema_init(&sem2, 0);

	kth1 = kthread_create((void *)_kth1, NULL, "kthread1");
	wake_up_process(kth1);
	
	kth2 = kthread_create((void *)_kth2, NULL, "kthread2");
	wake_up_process(kth2);
	
	return 0;
}

static int bsp_release(struct inode *inodp, struct file *filp) {
	del_timer(&timer1);
	del_timer(&timer2);
	
	kthread_stop(kth1);
	kthread_stop(kth2);
	
	return 0;
}

//use ioctl to control
static long bsp_ioctl(struct file *filp, unsigned int cmd, unsigned long arg) {
	switch(cmd) {
		case 10:                        //stop thread1
			del_timer(&timer1);
			return 0;
			break;
		case 11:                        //start thread1
			if(timer_pending(&timer1)) return -1;
			else { start_timer1(); return 0; }
			break;
		case 12:                        //reset thread1
			del_timer(&timer1);
			v1 = START;
			return 0;
			break;
		case 20:                        //stop thread2
			del_timer(&timer2);
			return 0;
			break;
		case 21:                        //start thread2
			if(timer_pending(&timer2)) return -1;
			else { start_timer2(); return 0; }
			break;
		case 22:                        //reset thread2
			del_timer(&timer2);
			v2 = START;
			return 0;
			break;
		case 30:                        //stop thread1 and thread2
			del_timer(&timer1);
			del_timer(&timer2);
			return 0;
			break;
		case 31:                        //start thread1 and thread2
			if(timer_pending(&timer1) && timer_pending(&timer2)) return -1;
			if(timer_pending(&timer1) && !timer_pending(&timer2)) { start_timer2(); return 2; }
			if(!timer_pending(&timer1) && timer_pending(&timer2)) { start_timer1(); return 1; }
			if(!timer_pending(&timer1) && !timer_pending(&timer2)) { start_timer1(); start_timer2(); return 0; }
			break;
		case 32:                        //reset thread1 and thread2
			del_timer(&timer1);
			del_timer(&timer2);
			v1 = START;
			v2 = START;
			return 0;
			break;
	}
	return 0;
}

static struct file_operations bsp_fops = {
	.owner = THIS_MODULE,
	.unlocked_ioctl = bsp_ioctl,
	.open = bsp_open,
	.release = bsp_release
};

static int __init bsp_init(void) {
	int _init = register_chrdev(DEVN, DEV_NAME, &bsp_fops);
	if(_init < 0) {
		printk("%s: Fail to register!\n", DES);
	}
	else {
		printk("%s: OK to register!\n", DES);
	}
	
	return 0;
}

static void __exit bsp_exit(void) {
	unregister_chrdev(DEVN, DEV_NAME);
	printk("%s: OK to unregister!\n", DES);
}

module_init(bsp_init);
module_exit(bsp_exit);

MODULE_AUTHOR("MRZC");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("TWO THREADS");
