#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/netlink.h>
#include <net/sock.h>

#define NETLINK_EXAMPLE 31

static struct sock *nl_sk = NULL;

static void nl_recv_msg(struct sk_buff *skb)
{
    struct nlmsghdr *nlh;
    nlh = (struct nlmsghdr *)skb->data;
    printk(KERN_INFO "Received message: %s\n", (char *)nlmsg_data(nlh));
}

static int __init netlink_module_init(void)
{
    struct netlink_kernel_cfg cfg =
    {
        .input = nl_recv_msg,
    };

    nl_sk = netlink_kernel_create(&init_net, NETLINK_EXAMPLE, &cfg);
    if (!nl_sk) {
        printk(KERN_ALERT "Error creating netlink socket.\n");
        return -ENOMEM;
    }
    printk(KERN_INFO "Netlink module loaded.\n");
    return 0;
}

static void __exit netlink_module_exit(void)
{
    netlink_kernel_release(nl_sk);
    printk(KERN_INFO "Netlink module unloaded.\n");
}

module_init(netlink_module_init);
module_exit(netlink_module_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("WARG");
MODULE_DESCRIPTION("Netlink");
