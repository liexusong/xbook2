#include <xbook/resource.h>
#include <xbook/task.h>
#include <xbook/debug.h>
#include <xbook/sharemem.h>
#include <xbook/sem.h>
#include <xbook/msgqueue.h>
#include <xbook/pipe.h>
#include <xbook/driver.h>
#include <sys/res.h>
#include <sys/ipc.h>

/* debug: 1 enable, 0 disable */
#define DEBUG_LOCAL 0

res_item_t *res_to_item(int res)
{
    task_t *cur = current_task;
    if (cur->res == NULL)
        return NULL;
    if (IS_BAD_RES(res))
        return NULL;
    
    return &cur->res->table[res];
}

/**
 * install_res - 安装资源到进程空间
 * 
 * @devno: 设备号
 * 
 */
int install_res(unsigned long flags, unsigned long handle)
{
    resource_t *res = current_task->res;
    int i;
    for (i = 0; i < RES_NR; i++) {
        if (!res->table[i].flags)
            break;
    }
    if (i >= RES_NR) {
        printk(KERN_ERR "install_res: out of range!\n");
        return -1;
    }
    res->table[i].flags = flags;
    res->table[i].handle = handle;
    return i;
}

/**
 * uninstall_res - 从进程空间卸载资源
 * 
 * @idx: res index
 * 
 */
int uninstall_res(int idx)
{
    if (IS_BAD_RES(idx)) {
        printk(KERN_ERR "install_res: bad index in table!\n");
        return -1;
    }
    resource_t *res = current_task->res;
    res_item_t *item = &res->table[idx];
    
    item->flags = 0;
    item->handle = 0;
    return 0;
}

int __getres_device(char *name, unsigned long resflg)
{
#if DEBUG_LOCAL == 1
    printk(KERN_DEBUG "__getres_device: get name %s\n", name);
#endif    
    handle_t handle = device_open(name, resflg & RES_LOCAL_MASK);
    if (handle < 0) {
        printk(KERN_ERR "__getres_device: device open %d failed!\n", handle);
        return -1;
    }
    #if DEBUG_LOCAL == 1
        printk(KERN_DEBUG "__getres_device: open done, ready install res.\n");
    #endif
    
    /* 打开资源成功，安装到进程中 */
    int res = install_res(resflg & RES_GLOBAL_MASK, handle);
    if (res == -1) { /* 失败后要关闭设备 */  
        printk(KERN_ERR "__getres_device: install res failed!\n");
        device_close(handle);
        return -1;
    }
    return res;
}

int __getres_ipc(char *name, unsigned long resflg, unsigned long arg)
{
    int res = -1;
    unsigned long handle;
    if (resflg & IPC_SHM) { /* 共享内存 */
        handle = share_mem_get(name, arg, resflg & RES_LOCAL_MASK);
        if (handle == -1)
            return -1;
        /* 消除从类型中的其它类型 */
        resflg = (resflg & (RES_LOCAL_MASK | RES_MASTER_MASK)) | IPC_SHM;
        /* 打开资源成功，安装到进程中 */
        res = install_res(resflg, handle);
        if (res == -1) { /* 失败后要释放资源 */  
            #if DEBUG_LOCAL == 1
                printk(KERN_DEBUG "__getres_ipc: install res failed!\n");
            #endif
            share_mem_put(handle);
            return -1;
        }
    } else if (resflg & IPC_SEM) { /* 信号量 */
        handle = sem_get(name, arg, resflg & RES_LOCAL_MASK);
        if (handle == -1)
            return -1;
        /* 消除从类型中的其它类型 */
        resflg = (resflg & (RES_LOCAL_MASK | RES_MASTER_MASK)) | IPC_SEM;
        /* 打开资源成功，安装到进程中 */
        res = install_res(resflg, handle);
        if (res == -1) { /* 失败后要释放资源 */  
            #if DEBUG_LOCAL == 1
                printk(KERN_DEBUG "__getres_ipc: install res failed!\n");
            #endif
            sem_put(handle);
            return -1;
        }
    } else if (resflg & IPC_MSG) { /* 信号量 */
        handle = msg_queue_get(name, resflg & RES_LOCAL_MASK);
        if (handle == -1)
            return -1;
        /* 消除从类型中的其它类型 */
        resflg = (resflg & (RES_LOCAL_MASK | RES_MASTER_MASK)) | IPC_MSG;
        /* 打开资源成功，安装到进程中 */
        res = install_res(resflg, handle);
        if (res == -1) { /* 失败后要释放资源 */  
            #if DEBUG_LOCAL == 1
                printk(KERN_DEBUG "__getres_ipc: install res failed!\n");
            #endif
            msg_queue_put(handle);
            return -1;
        }
    } else if (resflg & IPC_PIPE) { /* 管道 */
#if DEBUG_LOCAL == 1
        printk(KERN_DEBUG "__getres_ipc: pipe resuource.\n");
#endif        
        handle = pipe_get(name, resflg & RES_LOCAL_MASK);
        if (handle == -1)
            return -1;
        /* 消除从类型中的其它类型 */
        resflg = (resflg & (RES_LOCAL_MASK | RES_MASTER_MASK)) | IPC_PIPE;
        /* 打开资源成功，安装到进程中 */
        res = install_res(resflg, handle);
        if (res == -1) { /* 失败后要释放资源 */  
            #if DEBUG_LOCAL == 1
            printk(KERN_DEBUG "__getres_ipc: install res failed!\n");
            #endif
            pipe_put(handle);
            return -1;
        }
    }
    return res;
}

int __writeres_ipc(res_item_t *item, off_t off, void *buffer, size_t count)
{
    void *shmaddr;
    /* 根据从类型进行不同的操作 */
    switch (item->flags & RES_SLAVER_MASK)
    {
    case IPC_SHM:
        shmaddr = share_mem_map(item->handle, buffer);
        if (shmaddr == NULL) {
            return -1;
        }
        /* 如果buf为空，就需要保存映射后的地址到count里面 */
        if (buffer == NULL)
            *(size_t *)count = (size_t )shmaddr;
        break;
    case IPC_SEM:
        if (sem_down(item->handle, off))
            return -1;
        break;
    case IPC_MSG:
        if (msg_queue_send(item->handle, buffer, count, off))
            return -1;
        break;
    case IPC_PIPE:
        if (pipe_write(item->handle, buffer, count, off))
            return -1;
        break;
    default:
        return -1;
    }
    return 0;
}

int __readres_ipc(res_item_t *item, off_t off, void *buffer, size_t count)
{
    long *msgtype = (long *) buffer;
    int read_bytes;
    /* 根据从类型进行不同的操作 */
    switch (item->flags & RES_SLAVER_MASK)
    {
    case IPC_SHM:
        if (share_mem_unmap(buffer))
            return -1;
        break;
    case IPC_SEM:
        if (sem_up(item->handle))
            return -1;
        break;
    case IPC_MSG:
        read_bytes = msg_queue_recv(item->handle, buffer, count, *msgtype, off);
        return read_bytes;
    case IPC_PIPE:
        read_bytes = pipe_read(item->handle, buffer, count, off);
        return read_bytes;
    default:
        return -1;
    }
    return 0;
}
/**
 * sys_getres - 获取资源
 * @resname: 资源名
 * @resflg: 资源标志，由本地标志和全局标志组成。
 *          本地标志：0-15位，全局标志16-31位。
 * @arg: 参数
 * 
 * @return: 成功返回资源，失败返回-1
 */
int sys_getres(char *resname, unsigned long resflg, unsigned long arg)
{
    CHECK_THREAD_CANCELATION_POTINT(current_task);
    #if DEBUG_LOCAL == 1
        printk(KERN_DEBUG "sys_getres: resname=%s resflg=%x\n", resname, resflg);
    #endif
    int res = -1;
    if (resflg & RES_DEV) {     /* 设备类型资源 */
        /* 消除主类型中的其它类型 */
        resflg = (resflg & (RES_LOCAL_MASK | RES_SLAVER_MASK)) | RES_DEV;
        res = __getres_device(resname, resflg);
    } else if (resflg & RES_IPC) {
        /* 消除主类型中的其它类型 */
        resflg = (resflg & (RES_LOCAL_MASK | RES_SLAVER_MASK)) | RES_IPC;
        res = __getres_ipc(resname, resflg, arg);
    }
    if (res == -1) {
        printk(KERN_ERR "sys_getres: get %s fialed!.\n", resname);        
    } else {
#if DEBUG_LOCAL == 1
        printk(KERN_DEBUG "sys_getres: install res success.\n");
#endif
    }
    return res;
}
/**
 * sys_putres - 释放资源
 * @res: 资源
 * 
 * @return: 成功返回0，失败返回-1
 */
int sys_putres(int res)
{
    CHECK_THREAD_CANCELATION_POTINT(current_task);
#if DEBUG_LOCAL == 1
    printk(KERN_DEBUG "sys_putres: res index %d\n", res);
#endif    
    res_item_t *item = res_to_item(res);
    if (item == NULL)
        return -1;
    
    switch (item->flags & RES_MASTER_MASK)
    {
    case RES_DEV:
        if (device_close(item->handle) < 0) {
            return -1;
        }
        break;
    case RES_IPC:
        switch (item->flags & RES_SLAVER_MASK)
        {
        case IPC_PIPE: /* 管道在释放时需要释放管道 */
            pipe_put(item->handle);
            break;
        default:
            break;
        }
        break;
    default:
        return -1;  /* error type */
    }
#if DEBUG_LOCAL == 1
    printk(KERN_DEBUG "sys_putres: uninstall res, the handle %x.\n", item->handle);
#endif    
    uninstall_res(res);

    return 0;
}

/**
 * sys_readres - 读取资源
 * @res: 资源
 * @off: 数据便宜（对于磁盘而言才有意义）
 * @buffer: 缓冲区
 * @count: 数据量
 * 
 * @return: 成功返回读取的数据量，失败返回-1
 */
int sys_readres(int res, off_t off, void *buffer, size_t count)
{
    CHECK_THREAD_CANCELATION_POTINT(current_task);
    #if DEBUG_LOCAL == 2
    printk(KERN_DEBUG "sys_readres: res index %d buffer=%x count=%d.\n",
        res, buffer, count);
    #endif   
    res_item_t *item = res_to_item(res);
    if (item == NULL)
        return -1;
    int retval = 0;
    switch (item->flags & RES_MASTER_MASK)
    {
    case RES_DEV:
        #if DEBUG_LOCAL == 2
            printk(KERN_DEBUG "sys_readres: devno=%x.\n", item->handle);
        #endif   
        retval = device_read(item->handle, buffer, count, off);
        break;
    case RES_IPC:
        /* 返回读取资源的信息 */
        retval = __readres_ipc(item, off, buffer, count);
        break;
    default:
        return -1;  /* error type */
    }
    #if DEBUG_LOCAL == 2
    printk(KERN_DEBUG "sys_readres: read done!\n");
    #endif    
    return retval;
}

/**
 * sys_writeres - 写入资源
 * @res: 资源
 * @off: 数据便宜（对于磁盘而言才有意义）
 * @buffer: 缓冲区
 * @count: 数据量，磁盘是扇区数
 * 
 * @return: 成功返回读取的数据量，失败返回-1
 */
int sys_writeres(int res, off_t off, void *buffer, size_t count)
{
    CHECK_THREAD_CANCELATION_POTINT(current_task);
    #if DEBUG_LOCAL == 2
    printk(KERN_DEBUG "sys_writeres: res index %d buffer=%x count=%d.\n",
        res, buffer, count);
    #endif    
    res_item_t *item = res_to_item(res);
    if (item == NULL)
        return -1;
    #if DEBUG_LOCAL == 2
    printk(KERN_DEBUG "sys_writeres: devno=%x.\n", item->handle);
    #endif    
    int retval = 0;
    switch (item->flags & RES_MASTER_MASK)
    {
    case RES_DEV:
        #if DEBUG_LOCAL == 2
            printk(KERN_DEBUG "sys_writeres: devno=%x.\n", item->handle);
        #endif   
        retval = device_write(item->handle, buffer, count, off);
        break;
    case RES_IPC:
        retval = __writeres_ipc(item, off, buffer, count);
        break;
    default:
        return -1;  /* error type */
    }
    #if DEBUG_LOCAL == 2
    printk(KERN_DEBUG "sys_writeres: write done!\n");
    #endif    
    return retval;
}

/**
 * sys_ctlres - 控制资源
 * @res: 资源
 * @buffer: 缓冲区
 * @count: 数据量，磁盘是扇区数
 * 
 * @return: 成功返回信息，失败返回-1
 */
int sys_ctlres(int res, unsigned int cmd, unsigned long arg)
{
#if DEBUG_LOCAL == 1
    printk(KERN_DEBUG "sys_ctlres: res index %d cmd=%d arg=%x.\n",
        res, cmd, arg);
#endif  
    res_item_t *item = res_to_item(res);
    if (item == NULL)
        return -1;
#if DEBUG_LOCAL == 1
    printk(KERN_DEBUG "sys_ctlres: devno=%x.\n", item->handle);
#endif  
    int retval = 0;
    switch (item->flags & RES_MASTER_MASK)
    {
    case RES_DEV:
        #if DEBUG_LOCAL == 2
            printk(KERN_DEBUG "sys_ctlres: devno=%x.\n", item->handle);
        #endif   
        retval = device_devctl(item->handle, cmd, arg);
        break;
    case RES_IPC:
        if (cmd == IPC_DEL) { /* 命令是删除IPC */
            /* 根据从类型进行不同的操作 */
            switch (item->flags & RES_SLAVER_MASK)
            {
            case IPC_SHM:
                share_mem_put(item->handle);
                break;
            case IPC_SEM:
                sem_put(item->handle);
                break;
            case IPC_MSG:
                msg_queue_put(item->handle);
                break;
            default:
                retval = -1;
                break;
            }
            if (!retval) /* 如果删除成功，就需要卸载资源 */
                uninstall_res(res);
        } else {
            retval = -1;
        }
        break;
    default:
        retval = -1;
        break;
    }
#if DEBUG_LOCAL == 1
    printk(KERN_DEBUG "sys_ctlres: control done!\n");
#endif  
    return retval;
}

/**
 * sys_mmap - 映射资源
 * @res: 资源
 * @length: 长度
 * @flags: 映射标志
 * 
 * @return: 成功返回映射后的地址，失败返回NULL
 */
void *sys_mmap(int res, size_t length, int flags)
{
#if DEBUG_LOCAL == 1
    printk(KERN_DEBUG "%s: res index %d cmd=%d arg=%x.\n",
        __func__, res, cmd, arg);
#endif  
    res_item_t *item = res_to_item(res);
    if (item == NULL)
        return NULL;
#if DEBUG_LOCAL == 1
    printk(KERN_DEBUG "%s: devno=%x.\n", __func__, item->handle);
#endif  
    void *retval = NULL;
    switch (item->flags & RES_MASTER_MASK)
    {
    case RES_DEV:
        #if DEBUG_LOCAL == 2
            printk(KERN_DEBUG "%s: devno=%x.\n", __func__, item->handle);
        #endif   
        retval = device_mmap(item->handle, length, flags);
        break;
    default:
        retval = NULL;
        break;
    }
#if DEBUG_LOCAL == 1
    printk(KERN_DEBUG "%s: control done!\n", __func__);
#endif  
    return retval;
}

/**
 * resource_copy - 复制资源
 * 
 * @res: 资源
 */
void resource_copy(resource_t *dst, resource_t *src)
{
    if (src == NULL || dst == NULL)
        return;
    int i;
    res_item_t *item;
    for (i = 0; i < RES_NR; i++) {
        item = &src->table[i];
        if (item->flags > 0) { /* 项在使用中 */
            switch (item->flags & RES_MASTER_MASK)
            {
            case RES_DEV:
                dst->table[i].flags = item->flags;  /* 复制项 */
                dst->table[i].handle = item->handle;  /* 复制项 */
                
                /* 设备增长 */
                device_grow(dst->table[i].handle);
                break;
            case RES_IPC:
                /* 不复制ipc资源和表项 */
                break;
            default:
                break;
            }
        }
    }
}
/**
 * resource_release - 释放资源
 * 
 * @res: 资源
 */
void resource_release(resource_t *res)
{
    if (res == NULL)
        return;
    int i;
    res_item_t *item;
    for (i = 0; i < RES_NR; i++) {
        item = &res->table[i];
        if (item->flags) {      
#if DEBUG_LOCAL == 1
    printk(KERN_DEBUG "resource_release: index=%d handle=%x flags=%x.\n", i, item->handle, item->flags);
#endif
            switch (item->flags & RES_MASTER_MASK)
            {
            case RES_DEV:
                /* 设备关闭 */
                device_close(res->table[i].handle);
                break;
            case RES_IPC:
                /* 管道在释放时需要释放 */
                switch (item->flags & RES_SLAVER_MASK)
                {
                case IPC_PIPE:
                    pipe_put(item->handle);
                    break;
                default:
                    break;
                } 
                break;
            default:
                continue;
            }
            uninstall_res(i); /* 卸载资源 */
        }
    }
}

/**
 * dump_resource - 调试
 * 
 * @res: 资源
 */
void dump_resource(resource_t *res)
{
    if (res == NULL)
        return;
    int i;
    res_item_t *item;
    for (i = 0; i < RES_NR; i++) {
        item = &res->table[i];
        switch (item->flags & RES_MASTER_MASK)
        {
        case RES_DEV:
            /* 设备增长 */
            printk(KERN_DEBUG "dump_resource: index=%d devno=%x\n",
                i, item->handle);
            break;
        case RES_IPC:
            printk(KERN_DEBUG "dump_resource: index=%d ipcno=%x\n",
                i, item->handle);
            /* code */
            break;
        default:
            break;
        }
    }
}

void resource_init(resource_t *res)
{
    if (res == NULL)
        return;
    int i;
    for (i = 0; i < RES_NR; i++) {
        res->table[i].flags = 0;
        res->table[i].handle = 0;
    }
}