#include "linux/module.h"
#include "linux/fs.h"
#include "linux/uaccess.h"

#define MAX_SIZE 1024
//每一个设备文件都代表着内核中的一个file结构体。该结构体在头文件linux/fs.h定义。注意，file结构体是内核空间的结构体，这意味着它不会在用户程序的代码中出现。
int my_open(struct inode *inode, struct file *file);
int my_release(struct inode *inode, struct file *file);
ssize_t my_read(struct file *file, char __user *user, size_t t, loff_t *f);
ssize_t my_write(struct file *file, const char __user *user, size_t t, loff_t *f);

char message[MAX_SIZE] = "this is an original message.";
int devNum; 
char devName[] = "myDevice";

struct file_operations myOperation = {
    open : my_open,
    release : my_release,
    read : my_read,
    write : my_write,
};

int init_module() { 
    int ret = register_chrdev(0, devName, &myOperation);
    if(ret < 0) {
        printk("Register chrdev failed\n");
        return -1;
    }
    else {
        printk("MyDevice has been successfully registered\n");
        printk("id: %d\n", ret);
        devNum = ret;
        return 0;
    }
}

void cleanup_module() { 
    unregister_chrdev(devNum, devName);
    printk("MyDevice unregistered\n");
}

int my_open(struct inode *inode, struct file *file) { 
    printk("MyDevice opened\n");
    try_module_get(THIS_MODULE);
    return 0;
}

int my_release(struct inode *inode, struct file *file) { 
    printk("MyDevice released\n");
    module_put(THIS_MODULE);
    return 0;
}

ssize_t my_read(struct file*file, char __user *user, size_t t, loff_t*f) { 
    if(copy_to_user(user, message, sizeof(message))) {  
        return -2;
    }
    return sizeof(message);
}

ssize_t my_write(struct file*file, const char __user *user, size_t t, loff_t*f) { 
    if(copy_from_user(message, user, sizeof(message))) {
        return -3;
    }
    return sizeof(message);
}