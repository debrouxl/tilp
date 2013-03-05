/* Hey EMACS -*- linux-c -*- */
/* $Id$ */

/*  TiLP - Tilp Is a Linking Program
 *  Copyright (C) 1999-2006  Romain Lievin
 *  Copyright (C) 2005 Julien BLACHE <jb@jblache.org>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software Foundation,
 *  Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

/*
	Screen shot management
*/

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <zlib.h>
#define Z_OK 0

#include "tilp_core.h"

TilpScreen screen = { NULL, 0, 0 };	// change to screen (like local/remote)

/*
  Do a screen capture
*/
int screen_capture(void)
{
	CalcScreenCoord sc;
	int err;

	/* bug #1662383: V200 replies as busy but screenshot is working anyways */
	//if(options.calc_model != CALC_V200)

	/* Don't check whether calc is ready to avoid sending of HOME key */
	if(options.calc_model == CALC_NSPIRE)
		if(tilp_calc_isready())
			return -1;

	/* Place a progress bar */
	gif->create_pbar_(FNCT_RECV_SCREEN, _("Screendump"));

	/* 
	   Get a screen capture
	 */
	g_free(screen.bitmap);
	sc.format = options.screen_clipping;
	err = ticalcs_calc_recv_screen(calc_handle, &sc, &screen.bitmap);

	if (options.screen_clipping == SCREEN_FULL) 
	{
		screen.width = sc.width;
		screen.height = sc.height;
	} else 
	{
		screen.width = sc.clipped_width;
		screen.height = sc.clipped_height;
	}

	gif->destroy_pbar();

	if (tilp_err(err))
		return -1;

	return 0;
}


/*
  Convert the B&W bitmap into a B&W bytemap.
  The returned RRGGBB array must be freed when no longer used.
*/
uint8_t *screen_bw_convert(void)
{
	guchar *bitmap, *bytemap, data, mask;
	gint w;
	gint h;
	int row, col, bit, pixel, pos;

	bitmap = screen.bitmap;
	w = screen.width;
	h = screen.height;

	bytemap = g_malloc(3 * w * h);

	for (row = 0; row < h; row++) 
	{
		for (col = 0; col < (w >> 3); col++) 
		{
			data = bitmap[(w >> 3) * row + col];
			mask = 0x80;

			for (bit = 0; bit < 8; bit++) 
			{
				pixel = data & mask;
				pos = row * w + 8 * col + bit;
				if (pixel) 
				{
					bytemap[3 * pos + 0] = 0;
					bytemap[3 * pos + 1] = 0;
					bytemap[3 * pos + 2] = 0;
				} 
				else 
				{
					bytemap[3 * pos + 0] = 255;
					bytemap[3 * pos + 1] = 255;
					bytemap[3 * pos + 2] = 255;
				}
				mask >>= 1;
			}
		}
	}

	return bytemap;
}

/*
  Convert the B&W bitmap into a 2-colors bytemap.
  The returned RRGGBB array must be freed when no longer used.
*/
uint8_t *screen_bw_blurry(void)
{
	guchar *bitmap, *bytemap, data, mask;
	gint w;
	gint h;
	int row, col, bit, pixel, pos;

	bitmap = screen.bitmap;
	w = screen.width;
	h = screen.height;

	bytemap = g_malloc(3 * w * h);

	for (row = 0; row < h; row++) 
	{
		for (col = 0; col < (w >> 3); col++) 
		{
			data = bitmap[(w >> 3) * row + col];
			mask = 0x80;

			for (bit = 0; bit < 8; bit++) 
			{
				pixel = data & mask;
				pos = row * w + 8 * col + bit;
				if (pixel) 
				{
					bytemap[3 * pos + 0] = 0x00;
					bytemap[3 * pos + 1] = 0x00;
					bytemap[3 * pos + 2] = 0x34;
				} else 
				{
					bytemap[3 * pos + 0] = 0xa8;
					bytemap[3 * pos + 1] = 0xb4;
					bytemap[3 * pos + 2] = 0xa8;
				}
				mask >>= 1;
			}
		}
	}

	return bytemap;
}

/*
  Convert an NSpire grayscale bitmap into a bytemap.
  The returned RRGGBB array must be freed when no longer used.
*/
uint8_t* screen_gs_convert(void)
{
	guchar *bitmap  = screen.bitmap;
	gint w = screen.width;
	gint h = screen.height;
	guchar *bytemap = g_malloc(3 * w * h);
	int i, j;

	for (i = 0; i < h; i++) 
	{
		for (j = 0; j < w/2; j++)
		{
			uint8_t data = bitmap[(w/2) * i + j];
			uint8_t lo = data & 0x0f;
			uint8_t hi = data >> 4;

			int pos = w*i + 2*j;

			bytemap[3 * pos + 0] = hi << 4;
			bytemap[3 * pos + 1] = hi << 4;
			bytemap[3 * pos + 2] = hi << 4;

			bytemap[3 * pos + 3] = lo << 4;
			bytemap[3 * pos + 4] = lo << 4;
			bytemap[3 * pos + 5] = lo << 4;
		}
	}

	return bytemap;
}

/*
  Convert an NSpire CX 16-bit color bitmap into a bytemap.
  The returned RRGGBB array must be freed when no longer used.
*/
uint8_t* screen_16bitcolor_convert(void)
{
	guchar *bitmap  = screen.bitmap;
	gint w = screen.width;
	gint h = screen.height;
	guchar *bytemap = g_malloc(3 * w * h);
	int i, j;

	for (i = 0; i < h; i++)
	{
		for (j = 0; j < w; j++)
		{
			uint16_t data = ((uint16_t *)bitmap)[w * i + j];

			int pos = w * i + j;

			// R5 G6 B5.
			bytemap[3 * pos + 0] = ((data & 0xF800) >> 11) << 3;
			bytemap[3 * pos + 1] = ((data & 0x07E0) >>  5) << 2;
			bytemap[3 * pos + 2] = ((data & 0x001F) >>  0) << 3;
		}
	}

	return bytemap;
}

/*
 * Utility function for the EPS and PDF output
 */
static gboolean write_compressed_a85_screen(FILE *fp, guchar *data, unsigned long len, gboolean inv, GError **error)
{
	guchar *ubuf, *cbuf;
	unsigned long cbuflen;
	unsigned int i, j;
	int ret;
	unsigned int a85count;
	unsigned long a85tuple;
	guchar a85block[6];

	if (inv) {
		ubuf = g_malloc(len);
		if (ubuf == NULL) {
			g_set_error(error, 0, 0, _("Couldn't allocate memory!"));
			return FALSE;
		}

		for (i = 0; i < len; i++) {
			ubuf[i] = data[i] ^ 0xff;
		}
	}
	else {
		ubuf = data;
	}

	/* buffer length = length + 0.1 * length + 12 (mandatory) */
	cbuflen = len + len / 10 + 12;
	cbuf = g_malloc(cbuflen);

	if (cbuf == NULL) {
		g_set_error(error, 0, 0, _("Couldn't allocate memory!"));
		if (inv) {
			g_free(ubuf);
		}
		return FALSE;
	}

	ret = compress(cbuf, &cbuflen, ubuf, len);

	if (inv) {
		g_free(ubuf);
		ubuf = NULL;
	}

	if (ret != Z_OK) {
		g_set_error(error, 0, 0, _("zlib error"));
		g_free(cbuf);
		return FALSE;
	}

	/* ASCII85 (base 85) encoding */
	a85count = 0;
	a85tuple = 0;
	a85block[5] = '\0';

	for (i = 0; i < cbuflen; i++) {
		switch (a85count) {
		case 0:
			a85tuple |= (cbuf[i] << 24);
			a85count++;
			break;
		case 1:
			a85tuple |= (cbuf[i] << 16);
			a85count++;
			break;
		case 2:
			a85tuple |= (cbuf[i] << 8);
			a85count++;
			break;
		case 3:
			a85tuple |= (cbuf[i] << 0);

			if (a85tuple == 0) {
				a85block[0] = 'z';
				a85block[1] = '\0';
			}
			else {
				/* The ASCII chars must be written in reverse order,
				 * hence -> a85block[4-j]
				 */
				for (j = 0; j < 5; j++) {
					a85block[4-j] = (guchar)(a85tuple % 85 + '!');
					a85tuple /= 85;
				}
			}
			fprintf(fp, "%s", a85block);

			a85count = 0;
			a85tuple = 0;
			break;
		default:
			break;
		}

		if ((i > 0) && (i % 32 == 0)) {
			fprintf(fp, "\n");
		}
	}

	if (a85count > 0) {
		a85count++;
		for (j = 0; j <= a85count; j++) {
			a85block[j] = (guchar)(a85tuple % 85 + '!'); 
			a85tuple /= 85;
		}
                /* Reverse order */
		for (j--; j > 0; j--) {
			fprintf(fp, "%c", a85block[j]);
		}
	}

        /* ASCII85 EOD marker + newline*/
	fprintf(fp, "~>\n");

	g_free(cbuf);

	return TRUE;
}


/*
 * Write out an Encapsulated PostScript file.
 */
gboolean screen_write_eps(const gchar *filename, GError **error)
{
	int h, w;
	FILE *fp;
	guchar *buf;
	time_t t;
	gboolean ret;
	GError *err = NULL;

	fp = fopen(filename, "wb");
	if (fp == NULL) {
		g_set_error(error, 0, 0, _("Couldn't open destination file for writing!"));
		return FALSE;
	}

	h = screen.height;
	w = screen.width;

	time(&t);

	fprintf(fp, "%%!PS-Adobe-3.0 EPSF-3.0\n");
	fprintf(fp, "%%%%Creator: TiLP %s / PostScript output Copyright (C) 2005 Julien BLACHE\n", TILP_VERSION);
	fprintf(fp, "%%%%Title: TiLP %s screenshot\n",
		tifiles_model_to_string(options.calc_model));
	fprintf(fp, "%%%%CreationDate: %s", ctime(&t));
	fprintf(fp, "%%%%LanguageLevel: 3\n");
	fprintf(fp, "%%%%BoundingBox: 0 0 %d %d\n", w, h);
	fprintf(fp, "\n");
	fprintf(fp, "%d %d scale\n", w, h);

	if (options.screen_blurry) {
		fprintf(fp, "%d %d 8 [%d 0 0 -%d 0 %d] currentfile /ASCII85Decode filter /FlateDecode filter false 3 colorimage\n", w, h, w, h, h);

		buf = screen_bw_blurry();

		ret = write_compressed_a85_screen(fp, buf, (h * w * 3), FALSE, &err);

		g_free(buf);

		if (!ret) {
			g_propagate_error(error, err);
			fclose(fp);
			unlink(filename);
			return FALSE;
		}
	}
	else {
		fprintf(fp, "%d %d 1 [%d 0 0 -%d 0 %d] currentfile /ASCII85Decode filter /FlateDecode filter image\n", w, h, w, h, h);

		ret = write_compressed_a85_screen(fp, screen.bitmap, (h * w) / 8, TRUE, &err);

		if (!ret) {
			g_propagate_error(error, err);
			fclose(fp);
			unlink(filename);
			return FALSE;
		}
	}

	fprintf(fp, "%%%%EOF\n");
	fclose(fp);

	return TRUE;
}

/*
 * Write out a PDF file.
 */
gboolean screen_write_pdf(const gchar *filename, GError **error)
{
	int h, w;
	FILE *fp;
	long obj5, obj6, obj7, xref, slen, slenp;
	struct tm *t;
	time_t tt;
	guchar *buf;
	gboolean ret;
	GError *err = NULL;

	fp = fopen(filename, "wb");
	if (fp == NULL) {
		g_set_error(error, 0, 0, _("Couldn't open destination file for writing!"));
		return FALSE;
	}

	h = screen.height;
	w = screen.width;

	tt = time(NULL);
	t = gmtime(&tt);

	fprintf(fp, "%%PDF-1.5\n");
	fprintf(fp, "\n");
	fprintf(fp, "1 0 obj\n");
	fprintf(fp, "   << /Type /Catalog\n");
	fprintf(fp, "      /Outlines 2 0 R\n");
	fprintf(fp, "      /Pages 3 0 R\n");
	fprintf(fp, "   >>\n");
	fprintf(fp, "endobj\n");
	fprintf(fp, "\n");
	fprintf(fp, "2 0 obj\n");
	fprintf(fp, "   << /Type /Outlines\n");
	fprintf(fp, "      /Count 0\n");
	fprintf(fp, "   >>\n");
	fprintf(fp, "endobj\n");
	fprintf(fp, "\n");
	fprintf(fp, "3 0 obj\n");
	fprintf(fp, "   << /Type /Pages\n");
	fprintf(fp, "      /Kids [4 0 R]\n");
	fprintf(fp, "      /Count 1\n");
	fprintf(fp, "   >>\n");
	fprintf(fp, "endobj\n");
	fprintf(fp, "\n");
	fprintf(fp, "4 0 obj\n");
	fprintf(fp, "    << /Type /Page\n");
	fprintf(fp, "       /Parent 3 0 R\n");
	fprintf(fp, "       /MediaBox [0 0 %d %d]\n", w, h);
	fprintf(fp, "       /Contents 5 0 R\n");
	fprintf(fp, "       /Resources << /ProcSet 6 0 R >>\n");
	fprintf(fp, "    >>\n");
	fprintf(fp, "endobj\n");
	fprintf(fp, "\n");

	/* Offset of object 5, for xref */
	obj5 = ftell(fp);

	fprintf(fp, "5 0 obj\n");
	fprintf(fp, "    << /Length          >>\n");

	/* Position of the stream length, to be written later on */
	slenp = ftell(fp) - 12;

	fprintf(fp, "stream\n");

	/* Start of the stream data */
	slen = ftell(fp);

	fprintf(fp, "q\n");
	fprintf(fp, "%d 0 0 %d 0 0 cm\n", w, h);
	fprintf(fp, "BI\n");
	fprintf(fp, "  /W %d\n", w);
	fprintf(fp, "  /H %d\n", h);

	if (options.screen_blurry) {
		/* RGB, 8 bits per component, ASCIIHex encoding */
		fprintf(fp, "  /CS /RGB\n");
		fprintf(fp, "  /BPC 8\n");
		fprintf(fp, "  /F [/A85 /FlateDecode]\n");
		fprintf(fp, "ID\n");

		buf = screen_bw_blurry();

		ret = write_compressed_a85_screen(fp, buf, (h * w * 3), FALSE, &err);

		g_free(buf);

		if (!ret) {
			g_propagate_error(error, err);
			fclose(fp);
			unlink(filename);
			return FALSE;
		}
	}
	else {
		/* GrayLevel, 1 bit per component, ASCIIHex encoding */
		fprintf(fp, "  /CS /G\n");
		fprintf(fp, "  /BPC 1\n");
		fprintf(fp, "  /F [/A85 /FlateDecode]\n");
		fprintf(fp, "ID\n");

		ret = write_compressed_a85_screen(fp, screen.bitmap, (h * w) / 8, TRUE, &err);

		if (!ret) {
			g_propagate_error(error, err);
			fclose(fp);
			unlink(filename);
			return FALSE;
		}
	}

	fprintf(fp, "EI\n");
	fprintf(fp, "Q\n");

	/* Go back and write the length of the stream */
	slen = ftell(fp) - slen - 1;
	fseek(fp, slenp, SEEK_SET);
	fprintf(fp, "%lu", slen);
	fseek(fp, 0L, SEEK_END);

	fprintf(fp, "endstream\n");
	fprintf(fp, "endobj\n");
	fprintf(fp, "\n");

	/* Offset of object 6, for xref */
	obj6 = ftell(fp);

	fprintf(fp, "6 0 obj\n");
	fprintf(fp, "    [/PDF]\n");
	fprintf(fp, "endobj\n");
	fprintf(fp, "\n");

	/* Offset of object 7, for xref */
	obj7 = ftell(fp);

	fprintf(fp, "7 0 obj\n");
	fprintf(fp, "   << /Title (TiLP %s screenshot)\n",
		tifiles_model_to_string(options.calc_model));
	fprintf(fp, "      /Creator (TiLP / PDF output Copyright (C) 2005 Julien BLACHE)\n");
	fprintf(fp, "      /Producer (TiLP %s)\n", TILP_VERSION);
	fprintf(fp, "      /CreationDate (D:%04d%02d%02d%02d%02d%02d+00'00')\n",
		1900 + t->tm_year, t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec);
	fprintf(fp, "   >>\n");
	fprintf(fp, "endobj\n");
	fprintf(fp, "\n");

	/* Offset of xref, for startxref below */
	xref = ftell(fp);

	fprintf(fp, "xref\n");
	fprintf(fp, "0 8\n");
	fprintf(fp, "0000000000 65535 f \n");
	fprintf(fp, "0000000010 00000 n \n");
	fprintf(fp, "0000000094 00000 n \n");
	fprintf(fp, "0000000153 00000 n \n");
	fprintf(fp, "0000000229 00000 n \n");
	fprintf(fp, "%010lu 00000 n \n", obj5);
	fprintf(fp, "%010lu 00000 n \n", obj6);
	fprintf(fp, "%010lu 00000 n \n", obj7);
	fprintf(fp, "\n");
	fprintf(fp, "trailer\n");
	fprintf(fp, "    << /Size 8\n");
	fprintf(fp, "       /Root 1 0 R\n");
	fprintf(fp, "       /Info 7 0 R\n");
	fprintf(fp, "    >>\n");
	fprintf(fp, "startxref\n");
	fprintf(fp, "%lu\n", xref);
	fprintf(fp, "%%%%EOF\n");

	fclose(fp);

	return TRUE;
}
