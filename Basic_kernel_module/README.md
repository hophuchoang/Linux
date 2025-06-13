# Character device file
## Overview
A character device file is a special file in Linux (usually under /dev) that allows user-space programs to communicate with hardware or drivers by reading and writing one byte at a time

## How it Works
1. Dynamic allocating device number (cat /proc/devices)
```bash
SYNOPSIS
    int alloc_chrdev_region(dev_t * dev, unsigned baseminor, unsigned count, const char * name);

ARGUMENTS
dev
    output parameter for first assigned number
baseminor
    first of the requested range of minor numbers
count
    the number of minor numbers required
name
    the name of the associated device or driver
```

2. Creating struct class
```bash
SYNOPSIS
    struct class * __class_create(struct module * owner, const char * name, struct lock_class_key * key);

ARGUMENTS
owner
    pointer to the module that is to “own” this struct class
name
    pointer to a string for the name of this class.
key
    the lock_class_key for this class; used by mutex lock debugging

```

3. Creating device
```bash
SYNOPSIS
    struct device * device_create(struct class * class, struct device * parent, dev_t devt, void * drvdata, const char * fmt, ...);

ARGUMENTS
class
    pointer to the struct class that this device should be registered to
parent
    pointer to the parent struct device of this new device, if any
devt
    the dev_t for the char device to be added
drvdata
    the data to be added to the device for callbacks
fmt
    string for the device's name
...
    variable arguments

```

4. Creating cdev structure
```bash
SYNOPSIS
    void cdev_init(struct cdev * cdev, const struct file_operations * fops);

ARGUMENTS
cdev
    the structure to initialize
fops
    the file_operations for this device
```

5. Adding character device to the system 
```bash
SYNOPSIS
    int cdev_add(struct cdev * p, dev_t dev, unsigned count);

ARGUMENTS
p
    the cdev structure for the device
dev
    the first device number for which this device is responsible
count
    the number of consecutive minor numbers corresponding to this device
``` 

## Demo
```bash
# On terminal
sudo insmod cdfile.ko # insert module to kernel
sudo rmmod  cdfile    # remove module from kernel

# Another terminal
dmesg -w               # Monitor kernel messages in real time

# Another terminal
sudo ./app /dev/m_device [on/off]

```


