/*
 * Seven Kingdoms 2: The Fryhtan War
 *
 * Copyright 1999 Enlight Software Ltd.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

//Filename    : ODIR.CPP
//Description : Object Directory

#include <stdlib.h>
#include <string.h>
#include <odir.h>

#ifdef NO_WINDOWS
#include <dirent.h>
#include <ctype.h>
#include <sys/stat.h>
#endif

#include <dbglog.h>

DBGLOG_DEFAULT_CHANNEL(Directory);

//----------- Define static function ------------//

static int sort_file_function( const void *a, const void *b );


//------- Begin of function Directory::Directory -------//

Directory::Directory(const boost::filesystem::path& base)
	: DynArray( sizeof(FileInfo), 20 ), base(base)
{
}

//-------- End of function Directory::Directory -------//


//------- Begin of function Directory::read -------//
//
// Read in the file list of the specified file spec.
//
// <char*> fileSpec = the file spec of the directory
// [int]   sortName = sort the file list by file name
//                    (default : 0)
//
// return : <int> the no. of files matched the file spec.
//
int Directory::read(const char *fileSpec, int sortName)
{
   FileInfo fileInfo;
   MSG("Listing Directory %s sortName=%d\n", fileSpec, sortName);

   struct stat file_stat;
   stat(fileSpec, &file_stat);

   strncpy(fileInfo.name, fileSpec, sizeof(fileInfo.name));

   fileInfo.size = file_stat.st_size;
   fileInfo.time.dwLowDateTime = 0;
   fileInfo.time.dwHighDateTime = 0;

   linkin( &fileInfo );

   return size();       // DynArray::size()
}
//-------- End of function Directory::read -------//


//------ Begin of function sort_file_function ------//
//
static int sort_file_function( const void *a, const void *b )
{
	return strcmpi( ((FileInfo*)a)->name, ((FileInfo*)b)->name );
}
//------- End of function sort_file_function ------//
