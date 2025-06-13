#include <linux/module.h>   /* Define module_init(), module_exit() */
#include <linux/fs.h>       /* Define alloc_chrdev_region(), register_chrdev_region() */
#include <linux/device.h>   /* Define device_create(), class_create() */
#include <linux/cdev.h>     /* Define cdev_init(), cdev_add() */
#include <linux/uaccess.h>  /* Define copy_to_user(), copy_from_user() */
#include <linux/slab.h>     /* Define kfee */

#define DRIVER_AUTHOR "HOHOANG"
#define DRIVER_DESC "Basic kernel module"
#define DRIVER_VERS "1.0"

#define NPAGES 1

static int m_open(struct inode *inode, struct file *file);
static int m_release(struct inode *inode, struct file *file);
static ssize_t m_read(struct file *filp, char __user *user_buf, size_t size, loff_t * offset);
static ssize_t m_write(struct file *filp, const char __user *user_buf, size_t size, loff_t * offset);

struct m_chdev
{
    int32_t size;
    char *kmalloc_ptr;
    dev_t dev_num;
    struct class *m_class;
    struct cdev m_cdev;
} m_dev; 

static struct file_operations fops = 
{
    .owner      = THIS_MODULE,
    .read       = m_read,
    .write      = m_write,
    .open       = m_open,
    .release    = m_release,
};

static int m_open(struct inode *inode, struct file *file){
    pr_info("System call open() called...!!!\n");
    return 0;
}

static int m_release(struct inode *inode, struct file *file){
    pr_info("System call close() called...!!!\n");
    return 0;
}

static ssize_t m_read(struct file *filp, char __user *user_buf, size_t size, loff_t * offset){
    size_t to_read;

    pr_info("System call read() called...!!!\n");

    to_read = (size > m_dev.size - *offset) ? (m_dev.size - *offset) : size;

    if (copy_to_user(user_buf, m_dev.kmalloc_ptr + *offset, to_read)){
        return -EFAULT;
    }

    *offset += to_read;

    return to_read;
}

static ssize_t m_write(struct file *filp, const char __user *user_buf, size_t size, loff_t * offset){
    size_t to_write;

    pr_info("System call write() called...!!!\n");

    to_write = (size + *offset > NPAGES * PAGE_SIZE) ? (NPAGES * PAGE_SIZE - *offset) : size;

    memset(m_dev.kmalloc_ptr, 0, NPAGES * PAGE_SIZE);
    if (copy_from_user(m_dev.kmalloc_ptr + *offset, user_buf, to_write) != 0)
        return -EFAULT;

    pr_info("Data from usr: %s", m_dev.kmalloc_ptr);

    if (strcmp(m_dev.kmalloc_ptr, "on\n") == 0 || strcmp(m_dev.kmalloc_ptr, "on") == 0){
        pr_info("turn led on");

    }else if (strcmp(m_dev.kmalloc_ptr, "off\n") == 0 || strcmp(m_dev.kmalloc_ptr, "off") == 0){
        pr_info("turn led off");
    }

    *offset += to_write;
    m_dev.size = *offset;

    return to_write;
}

static int __init chdev_init(void)
{
    /* 1.0 Dynamic allocating device number (cat /proc/devices) */
    if (alloc_chrdev_region(&m_dev.dev_num, 0, 1, "dev_num")){
        pr_err("failed to alloc chrdev region\n");
        return -1;
    }

    /* 2.0 Creating struct class */
    if ((m_dev.m_class = class_create(THIS_MODULE, "m_class")) == NULL){
        pr_err("Cannot create the struct class for my device\n");
        goto rm_class;
    }

    /* 3.0 Creating device */
    if ((device_create(m_dev.m_class, NULL, m_dev.dev_num, NULL, "m_device")) == NULL){
        pr_err("Cannot create my device\n");
        goto rm_device_numb;
    }

    /* 4.0 Creating cdev structure */
    cdev_init(&m_dev.m_cdev, &fops);

    /* 4.1 Adding character device to the system */
    if ((cdev_add(&m_dev.m_cdev, m_dev.dev_num, 1)) < 0){
        pr_err("Cannot add device to the system\n");
        goto rm_device;
    }

    /* 5.0 Allocate kernel buffer */
    m_dev.kmalloc_ptr = kmalloc(NPAGES * PAGE_SIZE, GFP_KERNEL);
    if (!m_dev.kmalloc_ptr){
        pr_err("Cannot allocate memory\n");
        goto rm_cdev;
    }

    pr_info("Hello world kernel module\n");
    pr_info("Major = %d, Minor = %d\n", MAJOR(m_dev.dev_num), MINOR(m_dev.dev_num));

    return 0;

rm_cdev:
    cdev_del(&m_dev.m_cdev);

rm_device:
    device_destroy(m_dev.m_class, m_dev.dev_num);

rm_class:
    class_destroy(m_dev.m_class);

rm_device_numb:
    unregister_chrdev_region(m_dev.dev_num, 1);

    return -1;
}


static void __exit chdev_exit(void)
{
    kfree(m_dev.kmalloc_ptr);
    cdev_del(&m_dev.m_cdev);
    device_destroy(m_dev.m_class, m_dev.dev_num);
    class_destroy(m_dev.m_class);
    unregister_chrdev_region(m_dev.dev_num, 1);
    pr_info("Goodbye kernel module unloaded\n");
}

module_init(chdev_init);
module_exit(chdev_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_VERSION(DRIVER_VERS);

