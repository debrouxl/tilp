/* Hey EMACS -*- linux-c -*- */
/*  tilp - a linking program for TI graphing calculators
 *  Copyright (C) 1999-2003  Romain Lievin
 *
 *  This program is free software you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software Foundation,
 *  Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>
#include <glade/glade.h>
#include <stdlib.h>
#include <string.h>

#include "support.h"

#include "gstruct.h"
#include "tilp_core.h"
#include "dboxes.h"
#include "pbars.h"
#include "about.h"
#include "manpage.h"
#include "labels.h"
#include "clock.h"
#include "release.h"
#include "options.h"
#include "device.h"
#include "clist.h"
#include "ctree.h"
#include "dnd.h"
#include "filesel.h"
#include "action.h"
#include "gtk_update.h"
#include "screenshot.h"

#ifdef __WIN32__
#define strcasecmp _stricmp
#endif /* __WIN32__ */

GladeXML *xml = NULL;
GtkWidget *main_wnd  = NULL;
GtkWidget *clist_wnd = NULL;
GtkWidget *ctree_wnd = NULL;
GtkWidget *help_menu = NULL;


/* Main window */

void show_right_view(int view)
{
	gpointer data;

	if(view)
	{
		data = glade_xml_get_widget(xml, "vbox2");
		gtk_widget_show_all(data);
	}
	else
	{
		data = glade_xml_get_widget(xml, "vbox2");
		gtk_widget_hide(data);

		//gtk_window_resize(dbox, options.xsize, options.ysize);
	}
}

GtkWidget *display_tilp_dbox()
{
	GtkWidget *dbox;
	GtkWidget *paned;

	xml = glade_xml_new(tilp_paths_build_glade("tilp-2.glade"), "tilp_dbox", PACKAGE);
	if (!xml)
		g_error("GUI loading failed !\n");
	glade_xml_signal_autoconnect(xml);

	dbox = glade_xml_get_widget(xml, "tilp_dbox");
	if(options.full_gui)
		gtk_window_resize(GTK_WINDOW(dbox), options.wnd_x_size1, options.wnd_y_size1);
	else
		gtk_window_resize(GTK_WINDOW(dbox), options.wnd_x_size2, options.wnd_y_size2);

	ctree_wnd = glade_xml_get_widget(xml, "treeview1");
	clist_wnd = glade_xml_get_widget(xml, "treeview2");

	label_wnd.label11 = glade_xml_get_widget(xml, "label11");
	label_wnd.label12 = glade_xml_get_widget(xml, "label12");
	label_wnd.label13 = glade_xml_get_widget(xml, "label13");
	label_wnd.label14 = glade_xml_get_widget(xml, "label14");
	label_wnd.label21 = glade_xml_get_widget(xml, "label21");

	toolbar_wnd.toolbar = glade_xml_get_widget(xml, "toolbar2");
	toolbar_wnd.button10 = glade_xml_get_widget(xml, "button1");
	toolbar_wnd.button11 = glade_xml_get_widget(xml, "button2");
	toolbar_wnd.button12 = glade_xml_get_widget(xml, "button3");
	toolbar_wnd.button13 = glade_xml_get_widget(xml, "button4");
	toolbar_wnd.button14 = glade_xml_get_widget(xml, "button5");
	toolbar_wnd.button15 = glade_xml_get_widget(xml, "button6");
	toolbar_wnd.button20 = glade_xml_get_widget(xml, "button10");
	toolbar_wnd.button21 = glade_xml_get_widget(xml, "button11");
	toolbar_wnd.button22 = glade_xml_get_widget(xml, "button12");

	menubar_wnd.menubar = glade_xml_get_widget(xml, "menubar1");
	menubar_wnd.viewlocal = glade_xml_get_widget(xml, "menuitem13");
	menubar_wnd.showall = glade_xml_get_widget(xml, "show_all_files1");
	menubar_wnd.restore = glade_xml_get_widget(xml, "imagemenuitem4");
	menubar_wnd.backup = glade_xml_get_widget(xml, "imagemenuitem3");
	menubar_wnd.idlist = glade_xml_get_widget(xml, "menuitem10");
	menubar_wnd.setclock = glade_xml_get_widget(xml, "menuitem9");
	menubar_wnd.dumprom = glade_xml_get_widget(xml, "menuitem8");

	paned = glade_xml_get_widget(xml, "hpaned1");
	gtk_paned_set_position(GTK_PANED(paned), options.pane_x_size);

	show_right_view(options.full_gui);
	help_menu = glade_xml_get_widget(xml, "help_menu1");

	clist_init();
	ctree_init();
	dnd_init();

	return dbox;
}

GtkWidget *display_help_menu(void)
{
	GladeXML *xml2;
	GtkWidget *menu;

	xml2 = glade_xml_new(tilp_paths_build_glade("tilp-2.glade"), "help_menu1", PACKAGE);
	if (!xml2)
		g_error("GUI loading failed !\n");
	glade_xml_signal_autoconnect(xml2);

	menu = glade_xml_get_widget(xml2, "help_menu1");
	return menu;
}

GLADE_CB void on_hpaned1_size_request(GtkPaned* paned, gpointer user_data)
{
	options.pane_x_size = gtk_paned_get_position(paned);
}

GLADE_CB void on_tilp_dbox_destroy(GtkObject* object, gpointer user_data)
{
	tilp_config_write();
	gtk_main_quit();
}

GLADE_CB gboolean on_tilp_dbox_delete_event(GtkWidget* widget, GdkEvent* event, gpointer user_data)
{
	if(options.full_gui)
		gtk_window_get_size(GTK_WINDOW(widget), &options.wnd_x_size1, &options.wnd_y_size1);
	else
		gtk_window_get_size(GTK_WINDOW(widget), &options.wnd_x_size2, &options.wnd_y_size2);

	return FALSE;
}

/* Help menu */

extern int go_to_bookmark(const char *link);

GLADE_CB void on_manual1_activate(GtkMenuItem* menuitem, gpointer user_data)
{
	gchar *path = g_strconcat(inst_paths.help_dir, _("Manual_en.html"), NULL);

	if(go_to_bookmark(path) < 0)
		msg_box1(_("Error"), _("Failed to run browser."));
	g_free(path);
}

GLADE_CB void on_manpage1_activate(GtkMenuItem* menuitem, gpointer user_data)
{
	display_manpage_dbox();
}

GLADE_CB void on_ti_s_web_site1_activate(GtkMenuItem* menuitem, gpointer user_data)
{
	go_to_bookmark("http://education.ti.com");
}

GLADE_CB void on_calculator_software1_activate(GtkMenuItem* menuitem, gpointer user_data)
{
	go_to_bookmark("http://epsstore.ti.com");
}

GLADE_CB void on_ticalcorg1_activate(GtkMenuItem* menuitem, gpointer user_data)
{
	go_to_bookmark("http://www.ticalc.org");
}

GLADE_CB void on_tinewsnet1_activate(GtkMenuItem* menuitem, gpointer user_data)
{
	go_to_bookmark("http://www.tigen.org");
}

GLADE_CB void on_ti_frorg1_activate(GtkMenuItem* menuitem, gpointer user_data)
{
	go_to_bookmark("http://www.ti-fr.com");
} 

GLADE_CB void on_the_lpg1_activate(GtkMenuItem* menuitem, gpointer user_data)
{
	go_to_bookmark("http://lpg.ticalc.org");
} 

GLADE_CB void on_tilp_s_web_site1_activate(GtkMenuItem* menuitem, gpointer user_data)
{
	go_to_bookmark("http://tilp.info");
} 

GLADE_CB void on_bug_report1_activate(GtkMenuItem* menuitem, gpointer user_data)
{
	GtkWidget *dialog;
	const gchar *message = _("There are several ways to get in touch if you encounter a problem with TiLP or if you have questions, suggestions, bug reports, etc:\n- if you have general questions or problems, please consider the users' mailing list first (mailto:tilp-users@list.sf.net).\n- if you want to discuss about TiLP, you can use the TiLP forum (http://sourceforge.net/forum/?group_id=18378).\n- for bug reports, use the 'Bug Tracking System' (http://sourceforge.net/tracker/?group_id=18378).\n\nBefore e-mailing the TiLP team, make sure you have read the FAQ....");
  
	dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL,
				  GTK_MESSAGE_INFO, GTK_BUTTONS_CLOSE,
				  "%s", message);
	gtk_dialog_run(GTK_DIALOG(dialog));
	gtk_widget_destroy(dialog);
}

GLADE_CB void on_changelog1_activate(GtkMenuItem* menuitem, gpointer user_data)
{
	display_release_dbox();
}

GLADE_CB void on_about1_activate(GtkMenuItem* menuitem, gpointer user_data)
{
	display_about_dbox();
}

/* Toolbar buttons callbacks */

GLADE_CB void on_rom_dump1_activate(GtkMenuItem* menuitem, gpointer user_data)
{
	char* src_filename;
	const char *dst_filename;
	const char *dst_filename2;
	char filename[128];

	if (tilp_calc_rom_dump())
		return;

	src_filename = g_strconcat(g_get_tmp_dir(), G_DIR_SEPARATOR_S, TMPFILE_ROMDUMP, NULL);

	sprintf(filename, "dump%s", tifiles_model_to_string(options.calc_model));
	dst_filename = create_fsel(local.cwdir, filename, "*.rom", TRUE);
	if (!dst_filename)
	{
		g_free(src_filename);
		return;
	}

	if (!strcmp(tifiles_fext_get(dst_filename), ""))
		dst_filename2 = g_strconcat(dst_filename, ".", "rom", NULL);
	else
		dst_filename2 = g_strdup(dst_filename);
	g_free(dst_filename);

	if (dst_filename2)
	{
		tilp_file_move_with_check(src_filename, dst_filename2);
	}
	g_free(src_filename);
	g_free(dst_filename2);

	tilp_dirlist_local();
	clist_refresh();
	labels_refresh();
}

// Ready
GLADE_CB void on_tilp_button1_clicked(GtkButton* button, gpointer user_data)
{
	tilp_calc_isready();
}

// Dirlist
GLADE_CB void on_tilp_button2_clicked(GtkButton* button, gpointer user_data)
{
	if (tilp_calc_dirlist() != 0)
		return;

	ctree_refresh();
	labels_refresh();
}

// Backup
GLADE_CB void on_tilp_button3b_clicked(GtkButton* button, gpointer user_data)
{
	char* src_filename;
	const char *dst_filename;
	const char *dst_filename2;
	char *ext;

	if (tilp_calc_recv_backup() != 0)
		return;

	src_filename = g_strconcat(g_get_tmp_dir(), G_DIR_SEPARATOR_S, TMPFILE_BACKUP, NULL);

	ext = g_strconcat("*.", tifiles_fext_of_backup(options.calc_model), NULL);
	dst_filename = create_fsel(local.cwdir, "backup", ext, TRUE);
	g_free(ext);

	if (!dst_filename)
	{
		g_free(src_filename);
		return;
	}

	if (!strcmp(tifiles_fext_get(dst_filename), ""))
		dst_filename2 = g_strconcat(dst_filename, ".", tifiles_fext_of_backup(options.calc_model), NULL);
	else
		dst_filename2 = g_strdup(dst_filename);
	g_free(dst_filename);
	
	if (dst_filename2)
	{
		tilp_file_move_with_check(src_filename, dst_filename2);
	}
	g_free(src_filename);
	g_free(dst_filename2);

	tilp_dirlist_local();
	clist_refresh();
	labels_refresh();
}

GLADE_CB void on_tilp_button7_clicked(GtkButton* button, gpointer user_data);

GLADE_CB void on_tilp_button3_clicked(GtkButton* button, gpointer user_data)
{
	if(options.backup_as_tigroup && tifiles_is_flash(options.calc_model))
		on_tilp_button7_clicked(button, user_data);
	else
		on_tilp_button3b_clicked(button, user_data);
}

// Restore
GLADE_CB void on_tilp_button4_clicked(GtkButton* button, gpointer user_data)
{
	const char *filename;
	char *ext;
	int mode = TIG_ALL | TIG_BACKUP;

	ext = g_strconcat("*.", tifiles_fext_of_backup(options.calc_model), ";*.tig", NULL);
	filename = create_fsel(local.cwdir, NULL, ext, FALSE);
	g_free(ext);

	if(filename)
	{
		if(tifiles_file_is_tigroup(filename))
		{
			int ret = backup_box(_("Restore"), _("Data to restore:"), &mode);
			if(ret != BUTTON1)
				return;
			tilp_calc_send_tigroup(filename, mode | TIG_BACKUP);
		}
		else if(tifiles_file_is_backup(filename))
			tilp_calc_send_backup(filename);
	}

	return;
}

static int save_group(void)
{
	char* src_filename;
	const char *dst_filename;
	const char *dst_filename2;
	char *ext;

	src_filename = g_strconcat(g_get_tmp_dir(), G_DIR_SEPARATOR_S, TMPFILE_GROUP, 
		".", tifiles_fext_of_group(options.calc_model), NULL);

	ext = g_strconcat("*.", tifiles_fext_of_group(options.calc_model), NULL);
	dst_filename = create_fsel(local.cwdir, "group", ext, TRUE);
	g_free(ext);

	if (!dst_filename)
	{
		g_free(src_filename);
		return -1;
	}

	if (!strcmp(tifiles_fext_get(dst_filename), ""))
		dst_filename2 = g_strconcat(dst_filename, ".", tifiles_fext_of_group(options.calc_model), NULL);
	else
		dst_filename2 = g_strdup(dst_filename);
	g_free(dst_filename);

	if (dst_filename2)
	{
		tilp_file_move_with_check(src_filename, dst_filename2);
	}
	g_free(src_filename);
	g_free(dst_filename2);

	tilp_dirlist_local();
	clist_refresh();
	labels_refresh();

	return 0;
}

void on_tilp_recv(void)
{
	int ret;

	if ((remote.selection1 != NULL) || (remote.selection2 != NULL)) 
	{
		if (remote.selection1 != NULL) 
		{
			ret = tilp_calc_recv_var();
			if (ret < 0)
				return;
			else if (ret > 0)
				save_group();
		}

		if (remote.selection2 != NULL) 
		{
			ret = tilp_calc_recv_app();
			if (ret != 0)
				return;
		}
	} 
	else if ((options.calc_model == CALC_TI82) || (options.calc_model == CALC_TI85)) 
	{
		ret = tilp_calc_recv_var();
		if (ret < 0)
			return;
		else if (ret > 0)
			save_group();
	}

	clist_refresh();
	labels_refresh();
}

// Used for sending vars
// Note: user_data is a string:
// - such as "<FLASH>" for sending var into FLASH (ti83+/84+/89/92+/v200)
// - such as "" for sending var in the default folder
// - such as "foo" for sending var in the 'foo' folder
// - unused for sending FLASH files
void on_tilp_send(const gchar *user_data)
{
	gchar *target;
	FileEntry *f;
	int ret1 = -1;
	int ret2 = -1;

	if (local.selection0 == NULL && local.selection2 == NULL && local.selection5 == NULL)
		return;

	tilp_local_contents_load();
	
	// send apps
	if(local.selection3 || (local.selection5 && local.selection3))
	{
		f = (FileEntry *) local.selection3->data;

		// send os upgrades
		if(tifiles_file_is_flash(f->name) || tifiles_file_is_tigroup(f->name)) 
		{
			if(tifiles_file_test(f->name, TIFILE_OS, options.calc_model))
			{
				if (tilp_calc_send_os(f->name) != 0)
					return;
			} 
			else if(tifiles_file_is_app(f->name))
			{
				ret1 = tilp_calc_send_app();
				if(!ret1)
				{
					// update dirlist (caching, avoid to request dirlist again)
					tilp_local_update_applist();
					ctree_refresh();
					labels_refresh();
				}
			}
		} 
	}

	// send vars
	if(local.selection1 || (local.selection5 && local.selection1))
	{
		// note: dst_folder must be a copy b/c the user_data
		// pointer is no longer valid after dirlist_remote
		target = g_strdup(user_data);

		// change target folder
		if(strcmp(target, "") && strcmp(target, "<FLASH>"))
			tilp_local_change_folder(target);

		// and wait for action
		if (display_action_dbox(target) == BUTTON2) 
		{
			g_free(target);
			tilp_local_contents_unload();
			return;
		}

		// needed: avoid box locking/flickering !
		GTK_REFRESH();

		ret2 = tilp_calc_send_var();
		if(!ret2)
		{
			// update dirlist (caching, avoid to request dirlist again)
			tilp_local_update_varlist();
			ctree_refresh();
			labels_refresh();
		}

		g_free(target);
	}

	tilp_local_contents_unload();
}

// Receive
GLADE_CB void on_tilp_button5_clicked(GtkButton* button, gpointer user_data)
{
	on_tilp_recv();
}

// Send
GLADE_CB void on_tilp_button6_clicked(GtkButton* button, gpointer user_data)
{
	gchar** filenames;
	gchar** ptr;
	char *ext;

	ext = g_strconcat("*.", "*", NULL);
	filenames = create_fsels(local.cwdir, NULL, ext);
	g_free(ext);

	if(filenames == NULL)
		return;

	for(ptr = filenames; *ptr != NULL; ptr++)
		tilp_local_selection_add(*ptr);

	g_strfreev(filenames);

	on_tilp_send("");
	tilp_local_selection_destroy();
}

// Recv TiGroup
GLADE_CB void on_tilp_button7_clicked(GtkButton* button, gpointer user_data)
{
	char* src_filename;
	const char *dst_filename;
	const char *dst_filename2;
	int ret;
	int mode = TIG_ALL;

	ret = backup_box(_("Backup"), _("Data to backup:"), &mode);
	if(ret != BUTTON1)
		return;

	if (tilp_calc_recv_tigroup(mode) != 0)
		return;

	src_filename = g_strconcat(g_get_tmp_dir(), G_DIR_SEPARATOR_S, TMPFILE_TIGROUP, NULL);
	dst_filename = create_fsel(local.cwdir, "backup", "*.tig", TRUE);

	if(!dst_filename)
	{
		g_free(src_filename);
		return;
	}

	if (!strcmp(tifiles_fext_get(dst_filename), ""))
		dst_filename2 = g_strconcat(dst_filename, ".tig", NULL);
	else
		dst_filename2 = g_strdup(dst_filename);
	g_free(dst_filename);

	if (dst_filename2)
	{
		tilp_file_move_with_check(src_filename, dst_filename2);
	}
	g_free(src_filename);
	g_free(dst_filename2);

	tilp_dirlist_local();
	clist_refresh();
	labels_refresh();
}

// Send TiGroup
GLADE_CB void on_tilp_button8_clicked(GtkButton* button, gpointer user_data)
{
	const char *filename;
	int ret;
	int mode = TIG_ALL;

	ret = backup_box(_("Restore"), _("Data to restore:"), &mode);
	if(ret != BUTTON1)
		return;

#if 1
	filename = create_fsel(local.cwdir, NULL, "*.tig", FALSE);
	if(filename)
		tilp_calc_send_tigroup(filename, mode);
#else
	if(local.selection2 == NULL)
		return;
	if(g_list_length(local.selection) > 1)
		return;
	
	{
		FileEntry *f = (FileEntry *) local.selection->data;

		if(!tifiles_file_is_tigroup(f->name))
			return;
	
		tilp_calc_send_tigroup(f->name, mode);
	}
#endif

	return;
}

// ---

// make new dir
GLADE_CB void on_tilp_button10_clicked(GtkButton* button, gpointer user_data)
{
	gchar *utf8 = NULL;
	gsize br, bw;
	gchar *dirname;

	utf8 = gif->msg_entry(_("Make a new directory"), _("Name: "), _("new_directory"));
	if (utf8 == NULL)
		return;

	dirname = g_filename_from_utf8(utf8, -1, &br, &bw, NULL);
	g_free(utf8);

	tilp_file_mkdir(dirname);
	g_free(dirname);

	clist_refresh();
	labels_refresh();
}


// trash
GLADE_CB void on_tilp_button11_clicked(GtkButton* button, gpointer user_data)
{
	tilp_file_selection_delete();

	clist_refresh();
	labels_refresh();
}

// refresh
GLADE_CB void on_tilp_button12_clicked(GtkButton* button, gpointer user_data)
{
	if (!local.copy_cut)
		tilp_file_selection_destroy();

	clist_refresh();
	labels_refresh();
}

GLADE_CB void on_tilp_button13_clicked(GtkButton* button, gpointer user_data)
{
	GtkWidget *menu = display_help_menu();

	gtk_menu_popup(GTK_MENU(menu), NULL, NULL, NULL, NULL, 0, gtk_get_current_event_time ());
}

// take screenshot
GLADE_CB void on_tilp_menuitem7_clicked(GtkButton* button, gpointer user_data)
{
	display_screenshot_dbox();
}

// change folder
GLADE_CB void on_button14_clicked(GtkButton* button, gpointer user_data)
{
	gchar *folder;

	folder = msg_entry(_("Path"), _("Enter new path"), local.cwdir);
	if(folder != NULL)
	{
		if(g_file_test(folder, G_FILE_TEST_IS_DIR))
		{
			tilp_file_chdir(folder);
			g_free(local.cwdir);
			local.cwdir = g_get_current_dir();

			clist_refresh();
			labels_refresh();
		}
		g_free(folder);
	}
}

// set clock
GLADE_CB void on_tilp_menuitem9_clicked(GtkButton* button, gpointer user_data)
{
	display_clock_dbox();
}

//get id-list
GLADE_CB void on_tilp_menuitem10_clicked(GtkButton* button, gpointer user_data)
{
	tilp_calc_idlist(0);
}

//get calc info
GLADE_CB void on_tilp_menuitem12_clicked(GtkButton* button, gpointer user_data)
{
	CalcInfos infos;
	tilp_calc_get_infos(&infos);
}


//update View menu
GLADE_CB void on_tilp_viewmenu_active(GtkButton* button, gpointer user_data)
{

}
