#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/uaccess.h>

#define DEVICE_NAME "mychardev"
#define BUFFER_SIZE 256

static char buffer[BUFFER_SIZE];
static int major_number;

static ssize_t device_read(struct file *file, char __user *user_buffer, size_t length, loff_t *offset)
{
    int bytes_read = 0;

    if (buffer[0] == 0) {
        return 0; // No data to read
    }

    while (length && buffer[bytes_read])
    {
        put_user(buffer[bytes_read], user_buffer++);
        length--;
        bytes_read++;
    }

    buffer[0] = 0;
    return bytes_read;
}

static ssize_t device_write(struct file *file, const char __user *user_buffer, size_t length, loff_t *offset)
{
    int i;

    if (length > BUFFER_SIZE)
    {
        return -EINVAL;
    }

    for (i = 0; i < length && i < BUFFER_SIZE; i++)
    {
        get_user(buffer[i], user_buffer++);
    }
    buffer[i] = 0;

    return i;
}

static struct file_operations fops =
{
    .read = device_read,
    .write = device_write,
};

static int __init mychardev_init(void)
{
    major_number = register_chrdev(0, DEVICE_NAME, &fops);
    if (major_number < 0)
    {
        printk(KERN_ALERT "Failed to register char device\n");
        return major_number;
    }
    printk(KERN_INFO "My char device registered with major number %d\n", major_number);
    return 0;
}

static void __exit mychardev_exit(void)
{
    unregister_chrdev(major_number, DEVICE_NAME);
    printk(KERN_INFO "My char device unregistered\n");
}

module_init(mychardev_init);
module_exit(mychardev_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("A simple character device");
