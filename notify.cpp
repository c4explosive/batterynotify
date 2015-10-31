#include <stdlib.h>
#include <libnotify/notify.h>
#include <gdk-pixbuf/gdk-pixbuf.h>
#include <string.h>
/*
*Idea Original: http://blog.desdelinux.net/script-controlar-ciclos-carga-bateria-laptop/
*
*/
void notifyB(GdkPixbuf * nimage)
{
    notify_init ("Battery Notify");
    NotifyNotification * Hll = notify_notification_new("Battery Health","Por la salud de tu batería, ¡Desconecta el cargador!","/root/005/Dev/notify/mac-battery-recalibrate-full-battery.png"); //Cambiar el icono
    notify_notification_set_image_from_pixbuf(Hll,nimage);
    notify_notification_set_timeout(Hll,0);
    notify_notification_show(Hll,NULL);
    g_object_unref(G_OBJECT(Hll));
    notify_uninit();
}

int percents()
{
    FILE * bff;
    int i,n=0;
    char * output=(char *)malloc(5*sizeof(char)), ch;
    sprintf(output,"");
    bff=popen("acpi | awk \'{print $4}\'","r");
    //bff=popen("calc 50+50","r");
    while(!feof(bff))
    {
	ch=fgetc(bff);
	if(ch>=48 && ch<=57)
	{
    	    output[n]=ch;
	    n++;
	}
    }
    pclose(bff);
    return atoi(output);
}

int main()
{
    printf("Porcentaje: %d%\n",percents());
    if(percents() > 98)
    {
    	GdkPixbuf * img=gdk_pixbuf_new_from_file("/root/005/Dev/notify/mac-battery-recalibrate-full-battery.png",NULL); //Cambiar ruta del icono
    	notifyB(img);
    }
    return 0;
}
