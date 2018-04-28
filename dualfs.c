/** Dual Fast Picture **/

#include <module.h>
#include <dryos.h>
#include <bmp.h>
#include <menu.h>
#include <config.h>
#include <property.h>
#include <raw.h>
#include <shoot.h>
#include <zebra.h>
#include <beep.h>
#include <lens.h>
#include <focus.h>
#include <string.h>
#include <battery.h>
#include <powersave.h>


static uint64_t ret_0_long() { return 0; }

static CONFIG_INT( "dualfs.invert", silent_pic_invert, 0);
static CONFIG_INT( "dualfs.fiso", silent_pic_first_iso, 0);
static CONFIG_INT( "dualfs.fshutter", silent_pic_first_shutter, 0);
static CONFIG_INT( "dualfs.iso", silent_pic_recovery_iso, 0);
static CONFIG_INT( "dualfs.shutter", silent_pic_recovery_shutter, 0);

//static int long_exposure_fix_enabled = 0;

/* forward reference */
static struct menu_entry silent_menu[];
static struct menu_entry silent_smenu[];

static int iso_original = 0;
static int shutter_original = 0;

static int new_iso = 0;
static int new_shutter = 0;

static int new_fiso = 0;
static int new_fshutter = 0;

static MENU_UPDATE_FUNC(silent_pic_mode_update)
{
    /* reveal options for the current shooting mode, if any */
   // silent_menu[0].children[1].shidden =(silent_pic_mode != SILENT_PIC_MODE_SLITSCAN);
}


static MENU_UPDATE_FUNC(isocheck)
{

 switch (silent_pic_recovery_iso)
    {
        case -12:
            new_iso = ISO_100;
            break;
        case -11:
            new_iso = ISO_125;
            break;
        case -10:
            new_iso = ISO_160;
            break;
        case -9:
            new_iso = ISO_200;
            break;
        case -8:
            new_iso = ISO_250;
            break;
        case -7:
            new_iso = ISO_320;
            break;
        case -6:
            new_iso = ISO_400;
            break;
        case -5:
            new_iso = ISO_500;
            break;
        case -4:
            new_iso = ISO_640;
            break;
        case -3:
            new_iso = ISO_800;
            break;
        case -2:
            new_iso = ISO_1000;
            break;
        case -1:
            new_iso = ISO_1250;
            break;
        case 0:
            new_iso = ISO_1600;
            break;
        case 1:
            new_iso = ISO_2000;
            break;
        case 2:
            new_iso = ISO_2500;
            break;
        case 3:
            new_iso = ISO_3200;
            break;
        case 4:
            new_iso = ISO_4000;
            break;
        

    }
	//bmp_printf(FONT_MED, 0, 0, "Iso debug : %d", silent_pic_recovery_iso);
    bmp_printf(FONT_MED, 0, 0, "Iso chosen : %d", new_iso);

}

static MENU_UPDATE_FUNC(fisocheck)
{

 switch (silent_pic_first_iso)
    {
        case -12:
            new_fiso = ISO_100;
            break;
        case -11:
            new_fiso = ISO_125;
            break;
        case -10:
            new_fiso = ISO_160;
            break;
        case -9:
            new_fiso = ISO_200;
            break;
        case -8:
            new_fiso = ISO_250;
            break;
        case -7:
            new_fiso = ISO_320;
            break;
        case -6:
            new_fiso = ISO_400;
            break;
        case -5:
            new_fiso = ISO_500;
            break;
        case -4:
            new_fiso = ISO_640;
            break;
        case -3:
            new_fiso = ISO_800;
            break;
        case -2:
            new_fiso = ISO_1000;
            break;
        case -1:
            new_fiso = ISO_1250;
            break;
        case 0:
            new_fiso = ISO_1600;
            break;
        case 1:
            new_fiso = ISO_2000;
            break;
        case 2:
            new_fiso = ISO_2500;
            break;
        case 3:
            new_fiso = ISO_3200;
            break;
        case 4:
            new_fiso = ISO_4000;
            break;
        

    }
    //bmp_printf(FONT_MED, 0, 0, "Iso debug : %d", silent_pic_recovery_iso);
    bmp_printf(FONT_MED, 0, 0, "Fiso chosen : %d", new_fiso);

}


static MENU_UPDATE_FUNC(shuttercheck)
{

 switch (silent_pic_recovery_shutter)
    {
        case -12:
            new_shutter = SHUTTER_1_60;
            break;
        case -11:
            new_shutter = SHUTTER_1_80;
            break;
        case -10:
            new_shutter = SHUTTER_1_90;
            break;
        case -9:
            new_shutter = SHUTTER_1_100;
            break;
        case -8:
            new_shutter = SHUTTER_1_125;
            break;
        case -7:
            new_shutter = SHUTTER_1_160;
            break;
        case -6:
            new_shutter = SHUTTER_1_180;
            break;
        case -5:
            new_shutter = SHUTTER_1_200;
            break;
        case -4:
            new_shutter = SHUTTER_1_250;
            break;
        case -3:
            new_shutter = SHUTTER_1_320;
            break;
        case -2:
            new_shutter = SHUTTER_1_350;
            break;
        case -1:
            new_shutter = SHUTTER_1_400;
            break;
        case 0:
            new_shutter = SHUTTER_1_500;
            break;
        case 1:
            new_shutter = SHUTTER_1_640;
            break;
        case 2:
            new_shutter = SHUTTER_1_750;
            break;
        case 3:
            new_shutter = SHUTTER_1_800;
            break;
        case 4:
            new_shutter = SHUTTER_1_1000;
            break;
        case 5:
            new_shutter = SHUTTER_1_1250;
            break;
        case 6:
            new_shutter = SHUTTER_1_1500;
            break;
        case 7:
            new_shutter = SHUTTER_1_1600;
            break;
        case 8:
            new_shutter = SHUTTER_1_2000;
            break;
        case 9:
            new_shutter = SHUTTER_1_2500;
            break;
        case 10:
            new_shutter = SHUTTER_1_3000;
            break;
        case 11:
            new_shutter = SHUTTER_1_3200;
            break;
        case 12:
            new_shutter = SHUTTER_1_4000;
            break;
        

    }
	//bmp_printf(FONT_MED, 0, 0, "Shutter debug : %d", silent_pic_recovery_shutter);
    bmp_printf(FONT_MED, 0, 0, "Shutter chosen : %d", new_shutter);

}

static MENU_UPDATE_FUNC(fshuttercheck)
{

 switch (silent_pic_first_shutter)
    {
        case -12:
            new_fshutter = SHUTTER_0s3;
            break;
        case -11:
            new_fshutter = SHUTTER_0s4;
            break;
        case -10:
            new_fshutter = SHUTTER_0s5;
            break;
        case -9:
            new_fshutter = SHUTTER_0s6;
            break;
        case -8:
            new_fshutter = SHUTTER_0s7;
            break;
        case -7:
            new_fshutter = SHUTTER_0s8;
            break;
        case -6:
            new_fshutter = SHUTTER_1s;
            break;
        case -5:
            new_fshutter = SHUTTER_1s3;
            break;
        case -4:
            new_fshutter = SHUTTER_1s5;
            break;
        case -3:
            new_fshutter = SHUTTER_1s6;
            break;
        case -2:
            new_fshutter = SHUTTER_2s;
            break;
        case -1:
            new_fshutter = SHUTTER_2s5;
            break;
        case 0:
            new_fshutter = SHUTTER_3s;
            break;
        case 1:
            new_fshutter = SHUTTER_3s2;
            break;
        case 2:
            new_fshutter = SHUTTER_4s;
            break;
        case 3:
            new_fshutter = SHUTTER_5s;
            break;
        case 4:
            new_fshutter = SHUTTER_6s;
            break;
        case 5:
            new_fshutter = SHUTTER_8s;
            break;
        case 6:
            new_fshutter = SHUTTER_10s;
            break;
        case 7:
            new_fshutter = SHUTTER_13s;
            break;
        case 8:
            new_fshutter = SHUTTER_15s;
            break;
        case 9:
            new_fshutter = SHUTTER_20s;
            break;
        case 10:
            new_fshutter = SHUTTER_25s;
            break;
        case 11:
            new_fshutter = SHUTTER_30s;
            break;
        case 12:
            new_fshutter = SHUTTER_MIN;
            break;
        

    }
    //bmp_printf(FONT_MED, 0, 0, "Shutter debug : %d", silent_pic_recovery_shutter);
    bmp_printf(FONT_MED, 0, 0, "Fshutter chosen : %d", new_fshutter);

}



static void fshoot()
{
    shutter_original = lens_info.raw_shutter;

    iso_original = lens_info.raw_iso;

    if(silent_pic_invert == 0){

	    lens_set_rawiso(new_fiso); 
	    lens_set_rawshutter(new_fshutter); 

	    //is_bulb_mode();

	    take_fast_pictures(1);

	 
	    lens_set_rawiso(new_iso); 
	    lens_set_rawshutter(new_shutter); 

	    take_fast_pictures(1);

    }
    else{

	    lens_set_rawiso(new_iso); 
	    lens_set_rawshutter(new_shutter); 

	    //is_bulb_mode();

	    take_fast_pictures(1);

	    lens_set_rawiso(new_fiso); 
	    lens_set_rawshutter(new_fshutter); 


	    take_fast_pictures(1);

    }

    lens_set_rawiso(iso_original); 
    lens_set_rawshutter(shutter_original);

    return;
}

   

    
    

static struct menu_entry silent_menu[] = {
    {
        .name = "ISO Flash Menu",
        //.priv = &silent_pic_enabled,
        //.update = silent_pic_display,
        .max  = 1,
        .depends_on = DEP_LIVEVIEW | DEP_CFN_AF_BACK_BUTTON,
        .help  = "Take two pictures with custom parameters \n"
		"with minimum delay between them",
        .submenu_width = 650,
        .children =  (struct menu_entry[]) {
            {
                .name = "First ISO",
                .priv = &silent_pic_first_iso,
                .update = fisocheck,
                .min = -12,
                .max = 4,
                //.unit = UNIT_ISO,
                .choices = CHOICES("100", "125","160","200","250","320","400","500","640","800","1000","1250","1600","2000","2500","3200","4000"),
                .help  = "ISO for first shot (should be low)",
                //.help2 = "Test",
            },
            {
                .name = "First Shutter",
                .priv = &silent_pic_first_shutter,
                .update = fshuttercheck,
                .min = -12,
                .max = 12,
                //.unit = UNIT_ISO,
                .choices = CHOICES("0.3", "0.4", "0.5", "0.6", "0.7", "0.8", "1", "1.3", "1.5", "1.6", "2", "2.5", "3", "3.2", "4", "5", "6", "8", "10", "13", "15", "20", "25", "30", "MIN"),
                .help  = "shutter for first shot (in seconds, should be long)",
                //.help2 = "(Indicated in 1 / value)",
            },
            {
                .name = "Second ISO",
                .priv = &silent_pic_recovery_iso,
                .update = isocheck,
                .min = -12,
                .max = 4,
                //.unit = UNIT_ISO,
                .choices = CHOICES("100", "125","160","200","250","320","400","500","640","800","1000","1250","1600","2000","2500","3200","4000"),
                .help  = "ISO for second shot (should be high)",
                //.help2 = "Test",
            },
	    {
                .name = "Second Shutter",
                .priv = &silent_pic_recovery_shutter,
                .update = shuttercheck,
                .min = -12,
                .max = 12,
                //.unit = UNIT_ISO,
                .choices = CHOICES("60", "80", "90", "100", "125", "160", "180", "200", "250", "320", "350", "400", "500", "640", "750", "800", "1000", "1250", "1500", "1600", "2000", "2500", "3000", "3200", "4000"),
                .help  = "shutter for second shot (in 1/value, should be short)",
                //.help2 = "(Indicated in 1 / value)",
            },

{
                .name = "Invert",
                .priv = &silent_pic_invert,
                //.update = shuttercheck,
                .min = 0,
                .max = 1,
                //.unit = UNIT_ISO,
                .choices = CHOICES("Yes", "No"),
                .help  = "Invert order of picture (takes second before first)",
                //.help2 = "(Indicated in 1 / value)",
            },
            MENU_EOL,
        }
       
    }
};


static struct menu_entry silent_smenu[] = {
    {
        .name = "ISO Flash Shoot",
        //.priv = &silent_pic_enabled,
        //.update = silent_pic_display,
        .max  = 1,
        .depends_on = DEP_LIVEVIEW | DEP_CFN_AF_BACK_BUTTON,
        .help  = "Take two pictures with custom parameters \n"
		"with minimum delay between them",
        .submenu_width = 650,
        .children =  (struct menu_entry[]) {
            {
                .name = "SHOOT",
                //.priv = &silent_pic_first_shutter,
                .update = fshoot,
                //.min = -12,
                //.max = 12,
                .help  = "start the shoot sequence",
                //.help2 = "(Indicated in 1 / value)",
            },
            MENU_EOL,
        }
       
    }
};


static unsigned int silent_init()
{
    
    /* fixme in core: prop handlers should trigger when initializing, but they do not */
    shutter_original = lens_info.raw_iso;
    iso_original = lens_info.raw_shutter;
    menu_add("Shoot", silent_menu, COUNT(silent_menu));
    menu_add("Shoot", silent_smenu, COUNT(silent_smenu));
    return 0;
}

static unsigned int silent_deinit()
{
    return 0;
}

MODULE_INFO_START()
    MODULE_INIT(silent_init)
    MODULE_DEINIT(silent_deinit)
MODULE_INFO_END()

MODULE_CONFIGS_START()
    MODULE_CONFIG(silent_pic_invert)
    MODULE_CONFIG(silent_pic_first_iso)
    MODULE_CONFIG(silent_pic_first_shutter)
    MODULE_CONFIG(silent_pic_recovery_iso)
    MODULE_CONFIG(silent_pic_recovery_shutter)
MODULE_CONFIGS_END()
