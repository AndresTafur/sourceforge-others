/*  This file is part of WhiteHawkClamav.

    WhiteHawkClamav is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    WhiteHawkClamav is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with WhiteHawkClamav.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <sys/param.h>
#include "SystemPath.hh"
#include "Exception.hh"

        WhiteHawkSystem::SystemPath::SystemPath(std::string path)
        {
          WhiteHawkSystem::AbstractFile tmp(path);
          eof = false;

          try
          {
            if( tmp.isDirectory())
            {
                if( path.at(path.length()-1) != '/')
                    path.append("/");
                dir = opendir(path.c_str());
                tmp.setPath(path);
                count = 0;
                this->path = path;
            }
            else
             count = 1;
          }
          catch(WhiteHawkSystem::Exception ex) { ex.print();}

        }

        WhiteHawkSystem::SystemPathCount WhiteHawkSystem::SystemPath::getCount(std::string path)
        {
          WhiteHawkSystem::AbstractFile file(path);

            return getCount(file);
        }




        WhiteHawkSystem::SystemPathCount WhiteHawkSystem::SystemPath::getCount(AbstractFile &objDir)
        {
            SystemPathCount count;
            struct dirent *red;
            DIR *buff;

          try
          {

                if( !objDir.isDirectory())
                    return SystemPathCount(1);

                if( objDir.getPath().at( objDir.getPath().length()-1) != '/')
                    objDir.setPath(objDir.getPath() + "/");

                buff = opendir(objDir.getPath().c_str());

                if( !buff)
                    return count;

                while( NULL != (red = readdir(buff)) )
                {
                    WhiteHawkSystem::AbstractFile tmp( objDir.getPath() + red->d_name);

                        if(tmp.isDirectory())
                        {
                            if( strcmp(red->d_name,".") != 0 && strcmp(red->d_name,"..") != 0  )
                            {
                                SystemPathCount subCount = WhiteHawkSystem::SystemPath::getCount(tmp);

                                 count += tmp;
                                 count += subCount;
                            }

                        }
                        else
                            count += tmp;
                }
                closedir(buff);

            }catch(WhiteHawkSystem::Exception ex){ex.print();}

            return count;
        }

        WhiteHawkSystem::SystemPathCount WhiteHawkSystem::SystemPath::getCount()
        {
          SystemPathCount count;

           if( path.at( path.length()-1) != '/')
                path.append("/");

            rewinddir(dir);

            while( NULL != (red = readdir(dir)) )
	        {
              WhiteHawkSystem::AbstractFile tmp( path + red->d_name);

                    count += tmp;
            }
            rewinddir(dir);
            return count;
        }



        std::string WhiteHawkSystem::SystemPath::getPath()
        {
            return path;
        }


        WhiteHawkSystem::AbstractFile WhiteHawkSystem::SystemPath::getCurrentWDir()
        {
          char *buff;
          AbstractFile file;

                buff = getcwd(NULL, 0);
                if( buff )
                {
                    file.setPath( buff );
                    free(buff);
                    return file;
                }
                else
                 throw (Exception("Failed getting current directory","WhiteHawkSystem::SystemPath::getCurrentWDir()"));
        }

        bool WhiteHawkSystem::SystemPath::setCurrentWDir(AbstractFile dir)
        {
            return chdir(dir.getPath().c_str()) == 0;
        }

        bool WhiteHawkSystem::SystemPath::setCurrentWDir(std::string dir)
        {
            return chdir(dir.c_str()) == 0;
        }


        bool WhiteHawkSystem::SystemPath::isEnd()
        {
               return eof;
        }

        WhiteHawkSystem::AbstractFile WhiteHawkSystem::SystemPath::find(std::string name)
        {
          WhiteHawkSystem::AbstractFile buff;

            for (buff = getNextFile();buff.getName().empty(); buff = getNextFile())
                if ( buff.getName().compare(name) == 0 )
                       return buff;

          return  WhiteHawkSystem::AbstractFile("");
       }


        WhiteHawkSystem::AbstractFile WhiteHawkSystem::SystemPath::getNextFile()
        {
            if( NULL != (red = readdir(dir)) )
            {
	           if( (strcmp(".", red->d_name) != 0) && (strcmp("..", red->d_name) != 0))
	           {
                    WhiteHawkSystem::AbstractFile tmp( path + red->d_name);
                    return tmp;
	           }
            }
            else
                eof = true;
            return  WhiteHawkSystem::AbstractFile("");
        }


        int WhiteHawkSystem::SystemPath::mkdirhier(const char *path)
        {
         char src[MAXPATHLEN], dst[MAXPATHLEN] = "";
         char *dirp, *nextp = src;
         int retval = 1;

            strncpy(src, path, sizeof(src));

            if (path[0] == '/')
                strcpy(dst, "/");

            while ((dirp = strsep(&nextp, "/")) != NULL)
            {
                if (*dirp == '\0')
                  continue;

                if (dst[0] != '\0')
                    strcat(dst, "/");
                strcat(dst, dirp);

                if (mkdir(dst, 0777) == -1)
                {
                    if (errno != EEXIST)
                        throw( Exception("Failed to make directory.","Line 220 : WhiteHawkSystem::SystemPath::mkdirhier()"));
                }
            }

        return 0;
       }


       WhiteHawkSystem::SystemPath::~SystemPath()
       {
            if(red)
             free(red);
       }
