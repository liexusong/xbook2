#include <string.h>
#include <stdio.h>
#include <stdio.h>
#include <sys/res.h>
#include <sys/ioctl.h>
#include <sys/vmm.h>

#include <drivers/screen.h>
#include <drivers/mouse.h>
#include <drivers/keyboard.h>

#include <layer/draw.h>
#include <layer/layer.h>

#include <window/window.h>
#include <environment/mouse.h>


#include <guisrv.h>

int init_guisrv()
{
    /* drivers */
    if (init_screen_driver()) {
        printf("[failed ] %s: init screen driver failed!\n", SRV_NAME);
        return -1;
    }
    if (init_mouse_driver()) {
        printf("[failed ] %s: init mouse driver failed!\n", SRV_NAME);
        return -1;
    }
    if (init_keyboard_driver()) {
        printf("[failed ] %s: init keyboard driver failed!\n", SRV_NAME);
        return -1;
    }

    return 0;
}

int open_guisrv()
{
    /* drivers */
    if (drv_screen.open()) {
        printf("[failed ] %s: open screen driver failed!\n", SRV_NAME);
        return -1;
    }
    if (drv_mouse.open()) {
        printf("[failed ] %s: open mouse driver failed!\n", SRV_NAME);
        return -1;
    }
    if (keyboard.open()) {
        printf("[failed ] %s: open keyboard driver failed!\n", SRV_NAME);
        return -1;
    }
    return 0;
}

int close_guisrv()
{
    /* drivers */
    if (drv_screen.close()) {
        printf("[failed ] %s: close screen driver failed!\n", SRV_NAME);
        return -1;
    }
    if (drv_mouse.close()) {
        printf("[failed ] %s: close mouse driver failed!\n", SRV_NAME);
        return -1;
    }
    if (keyboard.close()) {
        printf("[failed ] %s: close keyboard driver failed!\n", SRV_NAME);
        return -1;
    }
    return 0;
}

int start_guisrv()
{
    
    /* init layer */
    if (guisrv_init_layer()) {
        printf("[failed ] %s: init window layer failed!\n", SRV_NAME);
        return -1;
    }
    
    if (init_gui_window()) {
        printf("[failed ] %s: init window management failed!\n", SRV_NAME);
        return -1;
    }
    
}

int loop_guisrv()
{
    while (1)
    {
        drv_mouse.read();
        keyboard.read(); 
        
    }
}


/*
GUI struct:
+-----------------------+
| graph environment     |
| (system, user)        |
\                       /
+-----------------------+
| window manager        |
\                       /
+-----------------------+
| layer | input | event |
\                       /
+-----------------------+
| drivers               |
+-----------------------+
*/

int main(int argc, char *argv[])
{
    printf("[ok ] graph service start.\n");

    if (init_guisrv()) {
        return -1;
    }
    if (open_guisrv()) {
        return -1;
    }

    start_guisrv();

    loop_guisrv();

    if (close_guisrv()) {
        return -1;
    }
    return 0;
}
