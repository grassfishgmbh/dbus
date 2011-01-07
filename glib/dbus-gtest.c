/* -*- mode: C; c-file-style: "gnu" -*- */
/* dbus-test.c  Program to run all tests
 *
 * Copyright (C) 2002, 2003  Red Hat Inc.
 *
 * Licensed under the Academic Free License version 2.1
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
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

#include <config.h>
#include "dbus-gtest.h"
#include <stdio.h>
#include <stdlib.h>

#ifdef DBUS_BUILD_TESTS
static void
die (const char *failure)
{
  fprintf (stderr, "Unit test failed: %s\n", failure);
  exit (1);
}
#endif /* DBUS_BUILD_TESTS */

/**
 * An exported symbol to be run in order to execute
 * unit tests. Should not be used by
 * any app other than our test app, this symbol
 * won't exist in some builds of the library.
 * (with --enable-tests=no)
 *
 * @param test_data_dir the directory with test data (test/data normally)
 */
void
dbus_glib_internal_do_not_use_run_tests (const char *test_data_dir)
{
#ifdef DBUS_BUILD_TESTS  
  if (test_data_dir == NULL)
    test_data_dir = g_getenv ("DBUS_TEST_DATA");

  if (test_data_dir != NULL)
    printf ("Test data in %s\n", test_data_dir);
  else
    printf ("No test data!\n");

  printf ("%s: running glib tests\n", "dbus-glib-test");
  if (!_dbus_glib_test (test_data_dir))
    die ("glib");
  
  printf ("%s: running utils tests\n", "dbus-glib-test");
  if (!_dbus_gutils_test (test_data_dir))
    die ("gutils");
  
  printf ("%s: running mainloop integration tests\n", "dbus-glib-test");
  if (!_dbus_gmain_test (test_data_dir))
    die ("gmain");

  printf ("%s: running GObject tests\n", "dbus-glib-test");
  if (!_dbus_gobject_test (test_data_dir))
    die ("gobject");
  
  printf ("%s: completed successfully\n", "dbus-glib-test");
#else
  printf ("Not compiled with unit tests, not running any\n");
#endif
}

