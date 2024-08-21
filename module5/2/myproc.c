#include <linux/init.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/uaccess.h>

#define PROC_NAME "myprocfile"
#define BUFFER_SIZE 128

static char buffer[BUFFER_SIZE];
static int buffer_len = 0;

static ssize_t myprocfile_read(struct file *file, char __user *user_buffer, size_t count, loff_t *offset)
{
    if (*offset >= buffer_len)
    {
        return 0;
    }
    // Копируем данные в user space
    if (copy_to_user(user_buffer, buffer, buffer_len))
    {
        return -EFAULT;
    }

    *offset += buffer_len;
    return buffer_len;
}

static ssize_t myprocfile_write(struct file *file, const char __user *user_buffer, size_t count, loff_t *offset)
{
    if (count > BUFFER_SIZE - 1)
    {
        return -EINVAL;
    }
    if (copy_from_user(buffer, user_buffer, count))
    {
        return -EFAULT;
    }

    buffer[count] = '\0';
    buffer_len = count;

    return count;
}

static struct proc_ops myproc_ops =
{
    .proc_read = myprocfile_read,
    .proc_write = myprocfile_write,
};

static int __init myproc_init(void)
{
    if (proc_create(PROC_NAME, 0666, NULL, &myproc_ops) == NULL)
    {
        return -ENOMEM;
    }
    return 0;
}

static void __exit myproc_exit(void)
{
    remove_proc_entry(PROC_NAME, NULL);
}

module_init(myproc_init);
module_exit(myproc_exit);

MODULE_LICENSE("VAG");
MODULE_AUTHOR("WARG");
MODULE_DESCRIPTION("Модуль обмена данными с userspace через /proc");
