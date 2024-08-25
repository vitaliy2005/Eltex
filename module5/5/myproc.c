#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/netlink.h>
#include <net/sock.h>
#include <string.h>

#define NETLINK_EXAMPLE 31 // Выберите уникальный номер
#define MAX_PAYLOAD 1024 // Максимальный размер полезной нагрузки

static struct sock *nl_sk = NULL;

static void nl_recv_msg(struct sk_buff *skb)
{
    struct nlmsghdr *nlh;
       int pid;
       struct sk_buff *skb_out;
       int msg_size;
       char *msg = "Hello from kernel";
       int res;

       printk(KERN_INFO "Entering: %s\n", __FUNCTION__);

       msg_size = strlen(msg);

       nlh = (struct nlmsghdr *)skb->data;
       printk(KERN_INFO "Netlink received msg payload: %s\n", (char *)nlmsg_data(nlh));
       pid = nlh->nlmsg_pid; /*pid of sending process */

       skb_out = nlmsg_new(msg_size, 0);

       if (!skb_out)
       {

           printk(KERN_ERR "Failed to allocate new skb\n");
           return;

       }
       nlh = nlmsg_put(skb_out, 0, 0, NLMSG_DONE, msg_size, 0);
       NETLINK_CB(skb_out).dst_group = 0; /* not in mcast group */
           strncpy(nlmsg_data(nlh), msg, msg_size);

       res = nlmsg_unicast(nl_sk, skb_out, pid);

       if (res < 0)
           printk(KERN_INFO "Error while sending bak to user\n");
}

static int __init netlink_module_init(void) {
    struct netlink_kernel_cfg cfg = {
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

static void __exit netlink_module_exit(void) {
    netlink_kernel_release(nl_sk);
    printk(KERN_INFO "Netlink module unloaded.\n");
}

module_init(netlink_module_init);
module_exit(netlink_module_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("Netlink Example Module");
