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
*  along with this program if not, write to the Free Software
*  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
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

#ifdef __WIN32__
#define strcasecmp _stricmp
#endif				/* __WIN32__ */

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
		gtk_widget_hide_all(data);

		//gtk_window_resize(dbox, options.xsize, options.ysize);
	}
}

GtkWidget *display_tilp_dbox()
{
	//GladeXML *xml;
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

	label_wnd.label21 = glade_xml_get_widget(xml, "label26");
	label_wnd.label22 = glade_xml_get_widget(xml, "label24");
	label_wnd.label23 = glade_xml_get_widget(xml, "label29");

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
	GladeXML *xml;
	GtkWidget *menu;

	xml = glade_xml_new(tilp_paths_build_glade("tilp-2.glade"), "help_menu1", PACKAGE);
	if (!xml)
		g_error("GUI loading failed !\n");
	glade_xml_signal_autoconnect(xml);

	menu = glade_xml_get_widget(xml, "help_menu1");
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

GLADE_CB gboolean
on_tilp_dbox_delete_event              (GtkWidget       *widget,
                                        GdkEvent         *event,
                                        gpointer          user_data)
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
		msg_box1("Error", "Failed to run browser.");
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

GLADE_CB void
on_bug_report1_activate                (GtkMenuItem     *menuitem, gpointer         user_data)
{
	GtkWidget *dialog;
	const gchar *message =
    "There are several ways to get in touch if you encounter a problem with TiLP or if you have questions, suggestions, bug reports, etc:\n- if you have general questions or problems, please consider the users' mailing list first (mailto:tilp-users@list.sf.net).\n- if you want to discuss about TiLP, you can use the TiLP forum (http://sourceforge.net/forum/?group_id=18378).\n- for bug reports, use the 'Bug Tracking System' (http://sourceforge.net/tracker/?group_id=18378).\n\nBefore e-mailing the TiLP team, make sure you have read the FAQ....";
  
	dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL,
				  GTK_MESSAGE_INFO, GTK_BUTTONS_CLOSE,
				  message);
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
	char filename[128];

	if (tilp_calc_rom_dump())
		return;
#if 1
	src_filename = g_strconcat(g_get_tmp_dir(), G_DIR_SEPARATOR_S, TMPFILE_ROMDUMP, NULL);

	sprintf(filename, "dump%s", tifiles_model_to_string(options.calc_model));
	dst_filename = create_fsel(local.cwdir, filename, "*.rom", TRUE);
	if(!dst_filename)
	{
		g_free(src_filename);
		return;
	}

	if (!strcmp(tifiles_fext_get(dst_filename), ""))
		dst_filename = g_strconcat(dst_filename, ".", "rom", NULL);
	else
		dst_filename = g_strdup(dst_filename);
	
	tilp_file_move_with_check(src_filename, dst_filename);
	g_free(src_filename);
	
	tilp_dirlist_local();
	clist_refresh();
	labels_refresh();
#endif
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

// Send Backup
GLADE_CB void on_tilp_button3_clicked(GtkButton* button, gpointer user_data)
{
	char* src_filename;
	const char *dst_filename;
	char *ext;

	if (tilp_calc_recv_backup() != 0)
		return;

	src_filename = g_strconcat(g_get_tmp_dir(), G_DIR_SEPARATOR_S, TMPFILE_BACKUP, NULL);

	ext = g_strconcat("*.", tifiles_fext_of_backup(options.calc_model), NULL);
	dst_filename = create_fsel(local.cwdir, "backup", ext, TRUE);
	g_free(ext);

	if(!dst_filename)
	{
		g_free(src_filename);
		return;
	}

	if (!strcmp(tifiles_fext_get(dst_filename), ""))
		dst_filename = g_strconcat(dst_filename, ".", tifiles_fext_of_backup(options.calc_model), NULL);
	else
		dst_filename = g_strdup(dst_filename);
	
	tilp_file_move_with_check(src_filename, dst_filename);
	g_free(src_filename);
	
	tilp_dirlist_local();
	clist_refresh();
	labels_refresh();
}

// Recv Backup
GLADE_CB void on_tilp_button4_clicked(GtkButton* button, gpointer user_data)
{
	const char *filename;
	char *ext;

	ext = g_strconcat("*.", tifiles_fext_of_backup(options.calc_model), NULL);
	filename = create_fsel(local.cwdir, NULL, ext, FALSE);
	g_free(ext);

	if(filename)
		tilp_calc_send_backup(filename);

	return;
}

static int save_group(void)
{
	char* src_filename;
	const char *dst_filename;
	char *ext;

	src_filename = g_strconcat(g_get_tmp_dir(), G_DIR_SEPARATOR_S, TMPFILE_GROUP, 
		".", tifiles_fext_of_group(options.calc_model), NULL);

	ext = g_strconcat("*.", tifiles_fext_of_group(options.calc_model), NULL);
	dst_filename = create_fsel(local.cwdir, "group", ext, TRUE);
	g_free(ext);

	if(!dst_filename)
	{
		g_free(src_filename);
		return -1;
	}

	if (!strcmp(tifiles_fext_get(dst_filename), ""))
		dst_filename = g_strconcat(dst_filename, ".", tifiles_fext_of_group(options.calc_model), NULL);
	else
		dst_filename = g_strdup(dst_filename);
	
	tilp_file_move_with_check(src_filename, dst_filename);
	g_free(src_filename);
	
	tilp_dirlist_local();
	clist_refresh();
	labels_refresh();

	return 0;
}

void on_tilp_recv(void)
{
	int ret;

	if ((remote.selection != NULL) || (remote.selection2 != NULL)) 
	{
		if (remote.selection != NULL) 
		{
			ret = tilp_calc_recv_var();
			if (ret < 0)
				return;

			else if (ret > 0)
			{
				save_group();
			}
		}

		if (remote.selection2 != NULL) 
		{
			ret = tilp_calc_recv_flash_app();
			if (ret != 0)
				return;
		}
	} 
	else if ((options.calc_model == CALC_TI82) || (options.calc_model == CALC_TI85)) 
	{
		ret = tilp_calc_recv_var();
		if (ret < 0)
			return;

		if (ret > 0)
		{
			save_group();
		}
		else 
		{
			clist_refresh();
			labels_refresh();
		}
	}
}

// Used for sending vars
// Note: user_data is a string:
// - such as "FLASH" for sending var into FLASH (ti83+/84+/89/92+/v200)
// - such as "" for sending var in the default folder
// - such as "foo" for sending var in the 'foo' folder
// - unused for sending FLASH files
void on_tilp_send(gchar *user_data)
{
	gchar *target;
	FileEntry *f;
	int ret;

	// note: dst_folder must be a copy b/c the user_data
	// pointer is no longer valid after dirlist_remote
	target = g_strdup(user_data);

	if (local.selection == NULL)
		return;

	f = (FileEntry *) local.selection->data;
	if (tifiles_file_is_flash(f->name) || tifiles_file_is_tib(f->name)) 
	{
		if (!strcasecmp(tifiles_fext_get(f->name), tifiles_fext_of_certif(options.calc_model))) 
		{
			if (tilp_calc_send_cert(f->name) != 0)
				return;
		} 
		if (!strcasecmp(tifiles_fext_get(f->name), tifiles_fext_of_flash_app(options.calc_model))) 
		{
			if (tilp_calc_send_flash_app(f->name) != 0)
				return;
		} 
		else if (!strcasecmp(tifiles_fext_get(f->name), tifiles_fext_of_flash_os(options.calc_model))) 
		{
			if (tilp_calc_send_flash_os(f->name) != 0)
				return;
		} 
		else if (tifiles_file_is_tib(f->name)) 
		{
			if (tilp_calc_send_flash_os(f->name) != 0)
				return;
		}
	} 
	else 
	{
		tilp_slct_load_contents();

		// change target folder
		if(strcmp(target, ""))
			tilp_slct_change_folder(target);

		// and wait for action
		if (display_action_dbox(target) == BUTTON2) 
		{
			g_free(target);
			return;
		}

		// needed: avoid box locking/flickering !
		GTK_REFRESH();
		ret = tilp_calc_send_var();

		// update dirlist (caching, avoid to request dirlist again)
		if(!ret)
		{
			tilp_slct_update_dirlist();
			ctree_refresh();

			remote.memory.ram_used = ticalcs_dirlist_ram_used(remote.var_tree);
			labels_refresh();
		}

		tilp_slct_unload_contents();
	}

	g_free(target);
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
		tilp_clist_add_file_to_selection(*ptr);

	g_strfreev(filenames);
	
	on_tilp_send("");
	tilp_clist_selection_destroy();
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
	tilp_delete_selected_files();

	clist_refresh();
	labels_refresh();
}

// refresh
GLADE_CB void on_tilp_button12_clicked(GtkButton* button, gpointer user_data)
{
	if (!local.copy_cut)
		tilp_clist_file_selection_destroy();

	clist_refresh();
	labels_refresh();
}

GLADE_CB void on_tilp_button13_clicked(GtkButton* button, gpointer user_data)
{
	GtkWidget *menu = display_help_menu();

	gtk_menu_popup(GTK_MENU(menu), NULL, NULL, NULL, NULL,
				       0, gtk_get_current_event_time ());
}
