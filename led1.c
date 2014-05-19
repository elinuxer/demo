#include <linux/module.h>
#include <linux/init.h>
#include <linux/tty.h>          /* For fg_console, MAX_NR_CONSOLES */
#include <linux/kd.h>           /* For KDSETLED */
#include <linux/console_struct.h>       /* For vc_cons */
#include<linux/string.h>
#include<linux/fs.h>
#include<linux/uaccess.h>
#include<linux/gpio.h>
#include<linux/interrupt.h>
#include<linux/io.h>
#include<linux/of.h>
#include<linux/of_address.h>

MODULE_LICENSE("GPL");


static int dev_open(struct inode * ,struct file * );
static ssize_t dev_read(struct file * ,char * ,size_t ,loff_t *);
static int dev_rls(struct inode * , struct file *);
static ssize_t dev_write(struct file * ,const char  * ,size_t ,loff_t *);


static struct file_operations fops =
{

.read=dev_read,
.open=dev_open,
.write=dev_write,
.release=dev_rls,                               //close device file*

};



int init_module(void)
{

int t;

t=register_chrdev(15,"sathya",&fops);  //registers driver with major number

if(t<0)
{
//gpio_request(1,"led");
//gpio_export(1,"true");
//gpio_direction_output(1,0);
//gpio_set_value(1,1);

printk(KERN_ALERT "DEVICE REGISTRATION FAILED....\n");
}
else
{
printk(KERN_ALERT "DEVICE REGISTERED SUCCESSFULLY....\n");
return t;
}


}

void cleanup_module(void)
{

unregister_chrdev(15,"sathya");
printk(KERN_ALERT "DEVICE UNREGISTERED.....BYE.....:)\n");

}


static int dev_open(struct inode *inod,struct file *fil)
{
gpio_request(1,"led");
gpio_export(1,"true");
gpio_direction_output(1,0);
gpio_set_value(1,1);
return 0;

} 

/*static ssize_t dev_write(struct file *filp,const char *buff,size_t len ,loff_t *off)
{

switch( buff[0] )
{
case '0':
gpio_set_value(1, 0);
break;
 
case '1':
gpio_set_value(1, 1);
break;
 
default:
printk("Wrong option.\n");
break;
}
 
return count;

}*/

static  ssize_t dev_read(struct file *filp,char *buff,size_t len,loff_t *off)
{
int i=0,j;

short  count=0;

while(i<50)
{

for(j=0;j<1000000;j++)
gpio_direction_output(1,1);

for(j=0;j<1000000;j++)
gpio_direction_output(1,0);

i++;

}

}

static int dev_rls(struct inode *inod,struct file *fil)
{

printk(KERN_ALERT " DEVICE CLOSED SUCCESSFULLY...\n");
return 0;

}

