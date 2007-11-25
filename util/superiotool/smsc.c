/*
 * This file is part of the superiotool project.
 *
 * Copyright (C) 2007 Uwe Hermann <uwe@hermann-uwe.de>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA
 */

#include "superiotool.h"

#define DEVICE_ID_REG_OLD	0x0d
#define DEVICE_REV_REG_OLD	0x0e

#define DEVICE_ID_REG   	0x20
#define DEVICE_REV_REG  	0x21

static const struct superio_registers reg_table[] = {
	/* The following Super I/Os use the 0x20/0x21 ID registers. */
	{0x03, "FDC37C93xFR", {
		/* FIXME: There's another 0x03 but found on port 0x0d/0x0e! */
		{EOT}}},
	{0x0a, "FDC37N971", {
		{EOT}}},
	{0x0b, "FDC37N972", {
		{EOT}}},
	{0x0e, "LPC47N252", {	/* From sensors-detect */
		{EOT}}},
	{0x14, "LPC47M172", {
		{EOT}}},
	{0x30, "FDC37C93xAPM", {
		{EOT}}},
	{0x40, "FDC37C67x", {	/* E.g. FDC37C672. Chiprev: 0x01 */
		{NOLDN, NULL,
			{0x03,0x20,0x21,0x22,0x23,0x24,0x26,0x27,0x2b,0x2c,
			 0x2d,0x2e,0x2f,EOT},
			{0x03,0x40,NANA,0x00,0x00,0x04,MISC,MISC,NANA,NANA,
			 NANA,NANA,NANA,EOT}},
		{0x0, "Floppy",
			{0x30,0x60,0x61,0x70,0x74,0xf0,0xf1,0xf2,0xf4,0xf5,
			 EOT},
			{0x00,0x03,0xf0,0x06,0x02,0x0e,0x00,0xff,0x00,0x00,
			 EOT}},
		{0x3, "Parallel port",
			{0x30,0x60,0x61,0x70,0x74,0xf0,0xf1,EOT},
			{0x00,0x00,0x00,0x00,0x04,0x3c,0x00,EOT}},
		{0x4, "COM1",
			{0x30,0x60,0x61,0x70,0xf0,EOT},
			{0x00,0x00,0x00,0x00,0x00,EOT}},
		{0x5, "COM2",
			{0x30,0x60,0x61,0x62,0x63,0x70,0x74,0xf0,0xf1,0xf2,
			 EOT},
			{0x00,0x00,0x00,0x00,0x00,0x00,0x04,0x00,0x02,0x03,
			 EOT}},
		{0x7, "Keyboard",
			{0x30,0x70,0x72,0xf0,EOT},
			{0x00,0x00,0x00,0x00,EOT}},
		{0x8, "Aux I/O",
			{0x30,0xb4,0xb5,0xb6,0xb7,0xc0,0xc1,0xc2,0xc3,0xc4,
			 0xf1,0xf2,0xf3,0xf4,0xf6,0xf7,0xf8,0xf9,0xfa,0xfb,
			 EOT},
			{0x00,NANA,NANA,NANA,NANA,0x06,0x03,NANA,NANA,NANA,
			 0x00,0x00,0x00,MISC,RSVD,RSVD,RSVD,RSVD,RSVD,RSVD,
			 EOT}},
		{EOT}}},
	{0x42, "FDC37B80x/FDC37M707", {
		{EOT}}},
	{0x09, "FDC37N958FR", {	/* Found in e.g. Dell Latitude CPi A366XT. */
		{NOLDN, NULL,
			{0x03,0x07,0x20,0x21,0x22,0x23,0x24,0x26,0x27,0x28,
			 0x2b,0x2c,0x2d,0x2e,0x2f,EOT},
			{0x03,NANA,0x44,0x00,0x00,0x00,0x04,MISC,MISC,0x00,
			 NANA,NANA,NANA,NANA,NANA,EOT}},
		{0x0, "Floppy",
			{0x30,0x60,0x61,0x70,0x74,0xf0,0xf1,0xf2,0xf4,0xf5,
			 EOT},
			{0x00,0x03,0xf0,0x06,0x02,0x0e,0x00,0xff,0x00,0x00,
			 EOT}},
		{0x3, "Parallel port",
			{0x30,0x60,0x61,0x70,0x74,0xf0,0xf1,EOT},
			{0x00,0x00,0x00,0x00,0x04,0x3c,0x00,EOT}},
		{0x4, "COM1",
			{0x30,0x60,0x61,0x70,0xf0,EOT},
			{0x00,0x00,0x00,0x00,0x00,EOT}},
		{0x5, "COM2",
			{0x30,0x60,0x61,0x62,0x63,0x70,0x74,0xf0,0xf1,0xf2,
			 EOT},
			{NANA,0x00,0x00,0x00,0x00,0x00,0x04,0x00,0x02,0x03,
			 EOT}},
		{0x6, "Real-time clock (RTC)",
			{0x30,0x62,0x63,0x70,0xf0,EOT},
			{0x00,0x00,0x70,0x00,0x00,EOT}},
		{0x7, "Keyboard",
			{0x30,0x70,0x72,0xf0,EOT},
			{0x00,0x00,0x00,0x00,EOT}},
		{0x8, "Aux I/O",
			{0x30,0xb0,0xb1,0xb2,0xb3,0xb8,0xc0,0xc1,0xc2,0xc3,
			 0xc4,0xc5,0xc6,0xc8,0xca,0xcb,0xcc,0xd0,0xd1,0xd2,
			 0xd3,0xd4,0xd5,0xd6,0xd7,0xe0,0xe1,0xe2,0xe3,0xe4,
			 0xe5,0xe6,0xe7,0xef,0xf0,0xf1,0xf2,0xf3,0xf4,0xf6,
			 0xf9,0xfa,EOT},
			{0x00,NANA,NANA,NANA,NANA,NANA,NANA,0x01,NANA,NANA,
			 NANA,0x00,NANA,NANA,NANA,NANA,NANA,NANA,NANA,NANA,
			 NANA,NANA,NANA,NANA,NANA,NANA,NANA,NANA,NANA,NANA,
			 NANA,NANA,NANA,NANA,NANA,0x00,0x00,0x00,0x00,NANA,
			 NANA,NANA,EOT}},
		{0xa, "ACPI",
			{0x30,0x60,0x61,0x70,0xf0,EOT},
			{0x00,0x00,0x00,NANA,NANA,EOT}},
		{EOT}}},
	{0x43, "FDC37B77x", {
		{EOT}}},
	{0x44, "FDC37B78x", {
		{NOLDN, NULL,
			{0x03,0x07,0x20,0x21,0x22,0x23,0x24,0x26,0x27,0x28,
			 0x2b,0x2c,0x2d,0x2e,0x2f,EOT},
			{0x03,NANA,0x44,0x00,0x00,0x00,0x04,MISC,MISC,0x00,
			 NANA,NANA,NANA,NANA,NANA,EOT}},
		{0x0, "Floppy",
			{0x30,0x60,0x61,0x70,0x74,0xf0,0xf1,0xf2,0xf4,0xf5,
			 EOT},
			{0x00,0x03,0xf0,0x06,0x02,0x0e,0x00,0xff,0x00,0x00,
			 EOT}},
		{0x3, "Parallel port",
			{0x30,0x60,0x61,0x70,0x74,0xf0,0xf1,EOT},
			{0x00,0x00,0x00,0x00,0x04,0x3c,0x00,EOT}},
		{0x4, "COM1",
			{0x30,0x60,0x61,0x70,0xf0,EOT},
			{0x00,0x00,0x00,0x00,0x00,EOT}},
		{0x5, "COM2",
			{0x30,0x60,0x61,0x62,0x63,0x70,0x74,0xf0,0xf1,0xf2,
			 EOT},
			{NANA,0x00,0x00,0x00,0x00,0x00,0x04,0x00,0x02,0x03,
			 EOT}},
		{0x6, "Real-time clock (RTC)",
			{0x30,0x62,0x63,0x70,0xf0,EOT},
			{0x00,0x00,0x70,0x00,0x00,EOT}},
		{0x7, "Keyboard",
			{0x30,0x70,0x72,0xf0,EOT},
			{0x00,0x00,0x00,0x00,EOT}},
		{0x8, "Aux I/O",
			{0x30,0xb0,0xb1,0xb2,0xb3,0xb8,0xc0,0xc1,0xc2,0xc3,
			 0xc4,0xc5,0xc6,0xc8,0xca,0xcb,0xcc,0xd0,0xd1,0xd2,
			 0xd3,0xd4,0xd5,0xd6,0xd7,0xe0,0xe1,0xe2,0xe3,0xe4,
			 0xe5,0xe6,0xe7,0xef,0xf0,0xf1,0xf2,0xf3,0xf4,0xf6,
			 0xf9,0xfa,EOT},
			{0x00,NANA,NANA,NANA,NANA,NANA,NANA,0x01,NANA,NANA,
			 NANA,0x00,NANA,NANA,NANA,NANA,NANA,NANA,NANA,NANA,
			 NANA,NANA,NANA,NANA,NANA,NANA,NANA,NANA,NANA,NANA,
			 NANA,NANA,NANA,NANA,NANA,0x00,0x00,0x00,0x00,NANA,
			 NANA,NANA,EOT}},
		{0xa, "ACPI",
			{0x30,0x60,0x61,0x70,0xf0,EOT},
			{0x00,0x00,0x00,NANA,NANA,EOT}},
		{EOT}}},
	{0x47, "FDC37M60x", {	/* TODO: Not yet in sensors-detect */
		{EOT}}},
	{0x4c, "FDC37B72x", {
		{NOLDN, NULL,
			{0x03,0x07,0x20,0x21,0x22,0x23,0x24,0x26,0x27,0x28,
			 0x2b,0x2c,0x2d,0x2e,0x2f,EOT},
			{0x03,NANA,0x4c,0x00,0x00,0x00,0x04,MISC,MISC,0x00,
			 NANA,NANA,NANA,NANA,NANA,EOT}},
		{0x0, "Floppy",
			{0x30,0x60,0x61,0x70,0x74,0xf0,0xf1,0xf2,0xf4,0xf5,
			 EOT},
			{0x00,0x03,0xf0,0x06,0x02,0x0e,0x00,0xff,0x00,0x00,
			 EOT}},
		{0x3, "Parallel port",
			{0x30,0x60,0x61,0x70,0x74,0xf0,0xf1,EOT},
			{0x00,0x00,0x00,0x00,0x04,0x3c,0x00,EOT}},
		{0x4, "COM1",
			{0x30,0x60,0x61,0x70,0xf0,EOT},
			{0x00,0x00,0x00,0x00,0x00,EOT}},
		{0x5, "COM2",
			{0x30,0x60,0x61,0x70,0xf0,0xf1,0xf2,EOT},
			{NANA,0x00,0x00,0x00,0x00,0x02,0x03,EOT}},
		{0x7, "Keyboard",
			{0x30,0x70,0x72,0xf0,EOT},
			{0x00,0x00,0x00,0x00,EOT}},
		{0x8, "Aux I/O",
			{0x30,0xb0,0xb1,0xb2,0xb3,0xb8,0xc0,0xc1,0xc2,0xc3,
			 0xc4,0xc5,0xc6,0xc8,0xca,0xcb,0xcc,0xd0,0xd1,0xd2,
			 0xd3,0xd4,0xd5,0xd6,0xd7,0xe0,0xe1,0xe2,0xe3,0xe4,
			 0xe5,0xe6,0xe7,0xef,0xf0,0xf1,0xf2,0xf3,0xf4,0xf6,
			 0xf9,0xfa,EOT},
			{0x00,NANA,NANA,NANA,NANA,NANA,0x00,0x01,NANA,NANA,
			 NANA,0x00,NANA,NANA,NANA,NANA,NANA,NANA,NANA,NANA,
			 NANA,NANA,NANA,NANA,NANA,NANA,NANA,NANA,NANA,NANA,
			 NANA,NANA,NANA,NANA,NANA,0x00,0x00,0x00,MISC,NANA,
			 NANA,NANA,EOT}},
		{0xa, "ACPI",
			{0x30,0x60,0x61,0x70,0xf0,EOT},
			{0x00,0x00,0x00,NANA,NANA,EOT}},
		{EOT}}},
	{0x4d, "FDC37M81x", {
		{NOLDN, NULL,
			{0x03,0x07,0x20,0x21,0x22,0x23,0x24,0x26,0x27,0x2b,
			 0x2c,0x2d,0x2e,0x2f,EOT},
			{0x03,0x00,0x4d,NANA,0x00,0x00,0x04,MISC,MISC,NANA,
			 NANA,NANA,NANA,NANA,EOT}},
		{0x0, "Floppy",
			{0x30,0x60,0x61,0x70,0x74,0xf0,0xf1,0xf2,0xf4,
			 0xf5,EOT},
			{0x00,0x03,0xf0,0x06,0x02,0x0e,0x00,0xff,0x00,
			 0x00,EOT}},
		{0x3, "Parallel port",
			{0x30,0x60,0x61,0x70,0x74,0xf0,0xf1,EOT},
			{0x00,0x00,0x00,0x00,0x04,0x3c,0x00,EOT}},
		{0x4, "COM1",
			{0x30,0x60,0x61,0x70,0xf0,EOT},
			{0x00,0x00,0x00,0x00,0x00,EOT}},
		{0x5, "COM2",
			{0x30,0x60,0x61,0x62,0x63,0x70,0xf0,0xf1,0xf2,EOT},
			{0x00,0x00,0x00,RSVD,RSVD,0x00,0x00,0x02,0x03,EOT}},
		{0x7, "Keyboard",
			{0x30,0x70,0x72,0xf0,EOT},
			{0x00,0x00,0x00,0x00,EOT}},
		{0x8, "Aux I/O",
			/* Only 0xf6 existing (and reserved) or 0xf6..0xfb? */
			{0x30,0xb4,0xb5,0xb6,0xb7,0xc0,0xc1,0xc2,0xc3,0xc4,
			 0xc5,0xc6,0xc7,0xc8,0xf1,0xf2,0xf3,0xf4,0xf6,0xf7,
			 0xf8,0xf9,0xfa,0xfb,EOT},
			{0x00,NANA,NANA,NANA,NANA,0x02,0x01,NANA,NANA,NANA,
			 NANA,NANA,NANA,NANA,0x00,0x00,0x00,0x00,RSVD,RSVD,
			 RSVD,RSVD,RSVD,RSVD,EOT}},
		{EOT}}},
	{0x51, "LPC47B27x", {
		{NOLDN, NULL,
			{0x03,0x20,0x21,0x22,0x23,0x24,0x26,0x27,0x28,
			 0x2a,0x2b,0x2c,0x2d,0x2e,0x2f,EOT},
			{RSVD,0x51,NANA,0x00,0x00,0x04,MISC,MISC,RSVD,
			 NANA,NANA,NANA,NANA,NANA,NANA,EOT}},
		{0x0, "Floppy",
			{0x30,0x60,0x61,0x70,0x74,0xf0,0xf1,0xf2,0xf4,0xf5,
			 EOT},
			{0x00,0x03,0xf0,0x06,0x02,0x0e,0x00,0xff,0x00,0x00,
			 EOT}},
		{0x3, "Parallel port",
			{0x30,0x60,0x61,0x70,0x74,0xf0,0xf1,EOT},
			{0x00,0x00,0x00,0x00,0x04,0x3c,0x00,EOT}},
		{0x4, "COM1",
			{0x30,0x60,0x61,0x70,0xf0,EOT},
			{0x00,0x00,0x00,0x00,0x00,EOT}},
		{0x5, "COM2",
			{0x30,0x60,0x61,0x62,0x63,0x70,0x74,0xf0,0xf1,0xf2,
			 EOT},
			{NANA,0x00,0x00,0x00,0x00,0x00,0x04,0x00,0x02,0x03,
			 EOT}},
		{0x7, "Keyboard",
			{0x30,0x70,0x72,0xf0,EOT},
			{0x00,0x00,0x00,0x00,EOT}},
		{0x9, "Game port",
			{0x30,0x60,0x61,EOT},
			{0x00,0x00,0x00,EOT}},
		{0xa, "Power-management events (PME)",
			{0x30,0x60,0x61,0xf0,0xf1,EOT},
			{0x00,0x00,0x00,NANA,NANA,EOT}},
		{0xb, "MIDI port (MPU-401)",
			{0x30,0x60,0x61,0x70,EOT},
			{0x00,0x03,0x30,0x05,EOT}},
		{EOT}}},
	{0x52, "LPC47B37x", {
		{EOT}}},
	{0x54, "LPC47U33x", {
		{EOT}}},
	{0x56, "LPC47B34x", {
		{EOT}}},
	{0x57, "LPC47S42x", {
		{EOT}}},
	{0x59, "LPC47M10x/112/13x", {
		{NOLDN, NULL,
			{0x03,0x07,0x20,0x21,0x22,0x23,0x24,0x26,0x27,0x28,
			 0x2a,0x2b,0x2c,0x2d,0x2e,0x2f,EOT},
			{RSVD,0x00,0x59,NANA,0x00,0x00,0x44,MISC,MISC,RSVD,
			 NANA,NANA,NANA,NANA,NANA,NANA,EOT}},
		{0x0, "Floppy",
			{0x30,0x60,0x61,0x70,0x74,0xf0,0xf1,0xf2,0xf4,
			 0xf5,EOT},
			{0x00,0x03,0xf0,0x06,0x02,0x0e,0x00,0xff,0x00,
			 0x00,EOT}},
		{0x3, "Parallel port",
			{0x30,0x60,0x61,0x70,0x74,0xf0,0xf1,EOT},
			{0x00,0x00,0x00,0x00,0x04,0x3c,0x00,EOT}},
		{0x4, "COM1",
			{0x30,0x60,0x61,0x70,0xf0,EOT},
			{0x00,0x00,0x00,0x00,0x00,EOT}},
		{0x5, "COM2",
			{0x30,0x60,0x61,0x62,0x63,0x70,0x74,0xf0,0xf1,
			 0xf2,EOT},
			{NANA,0x00,0x00,RSVD,RSVD,0x00,RSVD,0x00,0x02,
			 0x03,EOT}},
		{0x7, "Keyboard",
			{0x30,0x70,0x72,0xf0,EOT},
			{0x00,0x00,0x00,0x00,EOT}},
		{0x9, "Game port",
			{0x30,0x60,0x61,EOT},
			{0x00,0x00,0x00,EOT}},
		{0xa, "Power Management Events (PME)",
			{0x30,0x60,0x61,0xf0,0xf1,EOT},
			{0x00,0x00,0x00,NANA,RSVD,EOT}},
		{0xb, "MPU-401",
			{0x30,0x60,0x61,0x70,EOT},
			{0x00,0x03,0x30,0x05,EOT}},
		{EOT}}},
	{0x5d, "LPC47B357", {	/* From sensors-detect (no datasheet) */
		{EOT}}},
	{0x5f, "LPC47M14x", {
		{EOT}}},
	{0x60, "LPC47M15x/192/997", {
		{EOT}}},
	{0x62, "LPC47S45x", {
		{EOT}}},
	{0x6b, "LPC47M292", {	/* From sensors-detect */
		{EOT}}},
	{0x6e, "LPC47B387", {	/* TODO: Not yet in sensors-detect */
		/* Found in the HP Compaq Business Desktop d530 Series */
		/* http://thread.gmane.org/gmane.linux.bios/26648 */
		/* We cannot find a public datasheet for this Super I/O. */
		{EOT}}},
	{0x6f, "LPC47B397", {
		{EOT}}},
	{0x74, "LPC47M182", {
		{EOT}}},
	{0x76, "LPC47M584", {	/* From sensors-detect (no datasheet) */
		{EOT}}},
	{0x77, "A8000", {	/* ASUS A8000, a rebranded DME1737(?) */
		{NOLDN, NULL,
			{0x03,0x07,0x20,0x21,0x22,0x23,0x24,0x26,0x27,0x28,
			 0x2a,0x2b,0x2c,0x2d,0x2e,0x2f,EOT},
			{RSVD,0x00,0x77,NANA,0x00,RSVD,0x44,MISC,MISC,RSVD,
			 NANA,NANA,NANA,NANA,NANA,NANA,EOT}},
		{0x0, "Floppy",
			{0x30,0x60,0x61,0x70,0x74,0xf0,0xf1,0xf2,0xf4,
			 0xf5,EOT},
			{0x00,0x03,0xf0,0x06,0x02,0x0e,0x00,0xff,0x00,
			 0x00,EOT}},
		{0x3, "Parallel port",
			{0x30,0x60,0x61,0x70,0x74,0xf0,0xf1,EOT},
			{0x00,0x00,0x00,0x00,0x04,0x3c,0x00,EOT}},
		{0x4, "COM1",
			{0x30,0x60,0x61,0x70,0xf0,EOT},
			{0x00,0x00,0x00,0x00,0x00,EOT}},
		{0x5, "COM2",
			{0x30,0x60,0x61,0x70,0xf0,0xf1,0xf2,EOT},
			{0x00,0x00,0x00,0x00,0x00,0x02,0x03,EOT}},
		{0x7, "Keyboard",
			{0x30,0x70,0x72,0xf0,EOT},
			{0x00,0x00,0x00,0x00,EOT}},
		{0xa, "Runtime registers",
			{0x30,0x60,0x61,0x62,0x63,0xf0,0xf1,0xf2,EOT},
			{0x00,0x00,0x00,0x00,0x00,NANA,RSVD,0x04,EOT}},
		{EOT}}},
	{0x78, "DME1737", {
		{NOLDN, NULL,
			{0x03,0x07,0x20,0x21,0x22,0x23,0x24,0x26,0x27,0x28,
			 0x2a,0x2b,0x2c,0x2d,0x2e,0x2f,EOT},
			{RSVD,0x00,0x77,NANA,0x00,RSVD,0x44,MISC,MISC,RSVD,
			 NANA,NANA,NANA,NANA,NANA,NANA,EOT}},
		{0x0, "Floppy",
			{0x30,0x60,0x61,0x70,0x74,0xf0,0xf1,0xf2,0xf4,
			 0xf5,EOT},
			{0x00,0x03,0xf0,0x06,0x02,0x0e,0x00,0xff,0x00,
			 0x00,EOT}},
		{0x3, "Parallel port",
			{0x30,0x60,0x61,0x70,0x74,0xf0,0xf1,EOT},
			{0x00,0x00,0x00,0x00,0x04,0x3c,0x00,EOT}},
		{0x4, "COM1",
			{0x30,0x60,0x61,0x70,0xf0,EOT},
			{0x00,0x00,0x00,0x00,0x00,EOT}},
		{0x5, "COM2",
			{0x30,0x60,0x61,0x70,0xf0,0xf1,0xf2,EOT},
			{0x00,0x00,0x00,0x00,0x00,0x02,0x03,EOT}},
		{0x7, "Keyboard",
			{0x30,0x70,0x72,0xf0,EOT},
			{0x00,0x00,0x00,0x00,EOT}},
		{0xa, "Runtime registers",
			{0x30,0x60,0x61,0x62,0x63,0xf0,0xf1,0xf2,EOT},
			{0x00,0x00,0x00,0x00,0x00,NANA,RSVD,0x04,EOT}},
		{EOT}}},
	{0x79, "SCH5504", {	/* From sensors-detect (no datasheet) */
		{EOT}}},
#if 0
	{0x7a, "Unknown", {	/* Found in Toshiba Satellite A80-117. */
		{EOT}}},
#endif
	{0x7c, "SCH3112", {
		{EOT}}},
	{0x7d, "SCH3114", {
		{EOT}}},
	{0x7f, "SCH3116", {
		{EOT}}},
	{0x81, "SCH5307", {
		{EOT}}},
	{0x85, "SCH5317", {	/* From sensors-detect */
		{EOT}}},
	{0x90, "SCH4307", {	/* From sensors-detect */
		{EOT}}},

	/* The following Super I/Os use the 0x0d/0x0e ID registers. */
	{0x03, "FDC37C669", {
		/* Init: 0x55, 0x55. Exit: 0xaa. Ports: 0x3f0/0x370. */
		/* Chiprev: 0x02. */
		/* FIXME: There's another 0x03 but found on port 0x20/0x21! */
		{EOT}}},
	{0x04, "FDC37C669FR", {	/* TODO: Not yet in sensors-detect. */
		/* Init: 0x55, 0x55. Exit: 0xaa. Ports: 0x3f0/0x370. */
		{EOT}}},
	{0x13, "LPC47N237", {
		/* Init: 0x55. Exit: 0xaa. Ports: 0x2e/0x4e. */
		{EOT}}},
	{0x28, "FDC37N769", {
		/* Init: 0x55. Exit: 0xaa. Ports: 0x3f0/0x370. */
		{NOLDN, NULL,
			{0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,
			 0x0a,0x0b,0x0c,0x0d,0x0e,0x0f,0x10,0x11,0x12,0x13,
			 0x14,0x15,0x16,0x17,0x18,0x19,0x1a,0x1b,0x1c,0x1d,
			 0x1e,0x1f,0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x27,
			 0x28,0x29,0x2a,0x2b,0x2c,0x2d,0x2e,0x2f,EOT},
			{0x28,0x9c,0x88,0x70,0x00,0x00,0xff,0x00,0x00,0x00,
			 0x00,0x00,0x02,0x28,NANA,0x00,0x00,0x80,RSVD,RSVD,
			 NANA,NANA,NANA,0x03,RSVD,RSVD,RSVD,RSVD,RSVD,RSVD,
			 0x80,0x00,0x3c,RSVD,RSVD,0x00,0x00,0x00,0x00,0x00,
			 0x00,0x00,RSVD,0x00,0x00,0x03,0x00,0x00,EOT}},
		{EOT}}},
	{0x29, "FDC37N3869/FDC37N869", {
		/* Init: 0x55. Exit: 0xaa. Ports: 0x3f0/0x370. */
		{EOT}}},
	{0x5a, "LPC47N227", {
		/* Init: 0x55. Exit: 0xaa. Ports: 0x2e/0x4e. */
		{NOLDN, NULL,
			{0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,
			 0x0a,0x0b,0x0c,0x0d,0x0e,0x0f,0x10,0x11,0x12,0x13,
			 0x14,0x15,0x16,0x17,0x18,0x19,0x1a,0x1b,0x1c,0x1d,
			 0x1e,0x1f,0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x27,
			 0x28,0x29,0x2a,0x2b,0x2c,0x2d,0x2e,0x2f,0x30,0x31,
			 0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,EOT},
			{0x28,0x9c,0x08,0x70,0x00,0x00,0xff,0x00,RSVD,0x00,
			 0x00,0x00,0x02,0x5a,NANA,0x00,0x00,0x80,MISC,0x00,
			 NANA,NANA,NANA,0x03,RSVD,RSVD,RSVD,RSVD,RSVD,RSVD,
			 RSVD,0x00,0x3c,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			 0x00,0x80,0x00,0x00,0x00,0x03,0x00,0x00,0x00,0x00,
			 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,EOT}},
		{EOT}}},
	{0x65, "FDC37C665GT/IR", {
		/* Init: 0x55, 0x55. Exit: 0xaa. Port: 0x3f0. */
		/* Chiprev: 0x02 = FDC37C665GT, 0x82 = FDC37C665IR */
		{EOT}}},
	{0x66, "FDC37C666GT", {
		/* Init: 0x55, 0x55. Exit: 0xaa. Port: 0x3f0. Chiprev: 0x02. */
		{EOT}}},
	{EOT}
};

static void enter_conf_mode_smsc(uint16_t port)
{
	/* Some of the SMSC Super I/Os have an 0x55,0x55 init, some only
	 * require one 0x55. We do 0x55,0x55 for all of them at the moment,
	 * in the assumption that the extra 0x55 won't hurt the other
	 * Super I/Os. This is verified to be true on (at least) the FDC37N769.
	 */
	outb(0x55, port);
	outb(0x55, port);
}

static void exit_conf_mode_smsc(uint16_t port)
{
	outb(0xaa, port);
}

static void probe_idregs_smsc_helper(uint16_t port, uint8_t idreg,
				     uint8_t revreg)
{
	uint8_t id, rev;
	const char *info = (idreg == 0x20) ? "(idregs=0x20/0x21) "
					   : "(idregs=0x0d/0x0e) ";

	probing_for("SMSC", info, port);

	enter_conf_mode_smsc(port);

	id = regval(port, idreg);
	rev = regval(port, revreg);

	if (superio_unknown(reg_table, id)) {
		if (verbose)
			printf(NOTFOUND "id=0x%02x, rev=0x%02x\n", id, rev);
		exit_conf_mode_smsc(port);
		return;
	}

	printf("Found %s %s (id=0x%02x, rev=0x%02x) at 0x%x\n",
	       (id == 0x77 ? "ASUS" : "SMSC"), get_superio_name(reg_table, id),
	       id, rev, port);
	chip_found = 1;

	dump_superio((id == 0x77 ? "ASUS" : "SMSC"), reg_table, port, id);

	exit_conf_mode_smsc(port);
}

void probe_idregs_smsc(uint16_t port)
{
	probe_idregs_smsc_helper(port, DEVICE_ID_REG, DEVICE_REV_REG);
	probe_idregs_smsc_helper(port, DEVICE_ID_REG_OLD, DEVICE_REV_REG_OLD);
}
