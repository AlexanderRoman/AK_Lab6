
#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/types.h>
#include <linux/slab.h>
#include <linux/ktime.h>

struct my_list_head {
struct my_list_head *next;
ktime_t time;
};

MODULE_AUTHOR("Roman Alexander <ice.wall.law.come@gmail.com>");
MODULE_DESCRIPTION("Hello, world");
MODULE_LICENSE("Dual BSD/GPL");

static struct my_list_head *head;

static uint times = 1;
module_param(times,uint,S_IRUGO);
MODULE_PARM_DESC(times, "The amount of times to print hello world");

static int __init initializer(void)
{
  uint i = 0;
  struct my_list_head *var1, *var2;

  printk(KERN_INFO "times: %d\n", times);

  if(times == 0) {
    printk(KERN_WARNING "times is 0");
  }else if(times >=5 && times <= 10) {
    printk(KERN_WARNING "The times are between 5 and 10");
  } else if(times > 10) {
    printk(KERN_ERR "The times are greater than 10");
    return -EINVAL;
  }

  head = kmalloc(sizeof(struct my_list_head *), GFP_KERNEL);
  var1 = head;
  
  for(i = 0; i < times; i++){
  var1->next = kmalloc(sizeof(struct my_list_head), GFP_KERNEL);
    var1->time = ktime_get();
    pr_info("Hello World!");
    var2 = var1;
    var1 = var1->next;
    }
    if (times != 0) {
      kfree(var2->next);
      var2->next = NULL;

  }
  printk(KERN_INFO "times: %d\n", times);
  return 0;
}

static void __exit exitter(void)
{
  struct my_list_head *variable;
  while (head != NULL && times != 0) {
    variable = head;
    pr_info("Time : %lld", variable->time);
    head = variable->next;
    kfree(variable);
  }
  if (times == 0) {
    pr_info("Times is 0 because print wasn't used");
  }
  pr_info("");
}

module_init(initializer);
module_exit(exitter);
