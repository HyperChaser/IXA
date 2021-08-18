#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/version.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/err.h>
#include <linux/uaccess.h>
#include <linux/device-mapper.h>

#define MINOR_FIRST 0
#define MINOR_COUNT 1
#define DEV_NAME "oni_chrdev"
#define BUFFER_SIZE 256

static struct cdev oni_cdev;
static struct class *oni_class;
static struct device *oni_device;
static size_t size_of_msg=0;
char msg[BUFFER_SIZE]={0};

static dev_t oni_device_number;

static int oni_open(struct inode *, struct file *);
static int oni_release(struct inode *, struct file *);
static ssize_t oni_write(struct file *, const char __user *, size_t count, loff_t *pos);
static ssize_t oni_read(struct file *, char __user *, size_t count, loff_t *pos);

struct file_operations oni_fops=
{
	.owner = THIS_MODULE,
	.open = oni_open,
	.release = oni_release,
	.write = oni_write,
	.read = oni_read
};

static ssize_t oni_read(struct file *filp, char __user *buffer, size_t count, loff_t *offset)
{
	if ((*offset + count) > BUFFER_SIZE)	
		count = BUFFER_SIZE - *offset;

	if (copy_to_user(buffer, msg, count))
	{
		pr_info("Oni Chrdev: Failed to send %d chars to the user\n", count);
		return -EFAULT;
	}

	*offset += count;
	pr_info("Oni Chrdev: Number of bytes successfully read = %zu\n", count);
	return count;
}

static ssize_t oni_write(struct file *filp, const char __user *buffer, size_t count, loff_t *offset)
{
	if ((*offset + count) > BUFFER_SIZE)
		count = BUFFER_SIZE - *offset;

	if (!count)
		return -ENOMEM;
	if(copy_from_user(msg, buffer, count))
	{
		return -EFAULT;
	}

	*offset + count;
	pr_info( "Oni Chrdev: receive %zu charaters for the user %s\n",count,msg);
	return count;
}

static int oni_open(struct inode *node, struct file *filp)
{
	
	return 0;
}

static int oni_release(struct inode *node, struct file *filp)
{	
	return 0;
}

void __exit oni_exit(void)
{
	device_destroy(oni_class, oni_device_number);
	class_destroy(oni_class);
	cdev_del(&oni_cdev);
	unregister_chrdev_region(oni_device_number, MINOR_COUNT);
	printk(KERN_INFO "UNLOAD ONI DRIVER");
}

int __init oni_init(void)
{	
	int ret; 
	ret = alloc_chrdev_region(&oni_device_number, MINOR_FIRST, MINOR_COUNT,DEV_NAME);
	if( ret != 0 )
	{
		printk(KERN_WARNING "Cannot allocate a device number");
		return ret;
	}
	cdev_init(&oni_cdev, &oni_fops);	
	ret = cdev_add(&oni_cdev, oni_device_number, MINOR_COUNT);
	if( ret != 0 )
	{
		unregister_chrdev_region(oni_device_number, MINOR_COUNT);
		printk(KERN_WARNING "Cannot add device to kernel");
		return ret;
	}
	
	oni_class = class_create(THIS_MODULE, DEV_NAME);
	if (IS_ERR(oni_class))
	{
		cdev_del(&oni_cdev);
		unregister_chrdev_region(oni_device_number, MINOR_COUNT);
		printk(KERN_WARNING "Cannot create class");
		return PTR_ERR(oni_class);
	}
	
	oni_device = device_create(oni_class, NULL, oni_device_number, NULL, DEV_NAME);
	if (IS_ERR(oni_device))
	{
		class_destroy(oni_class);
		cdev_del(&oni_cdev);
		unregister_chrdev_region(oni_device_number, MINOR_COUNT);
		printk(KERN_WARNING "Cannot create device file");
		return PTR_ERR(oni_device);
	}
	printk(KERN_INFO "INSTALL ONI DRIVER SUCCESS");
	return 0;
}

MODULE_LICENSE("GPL");            ///< The license type -- this affects available functionality
MODULE_AUTHOR("Oni Ranger");    ///< The author -- visible when you use modinfo
MODULE_DESCRIPTION("A simple Linux char driver for explain sleeping");  ///< The description -- see modinfo
MODULE_VERSION("0.1");            ///< A version number to inform users
module_init(oni_init);
module_exit(oni_exit);
