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

        WhiteHawkUtil::SystemPath::SystemPath(std::string path)
        {
          WhiteHawkUtil::AbstractFile tmp(path);
          eof = false;

          try
          {
            if( tmp.isDirectory())
            {
                if( path.at(path.length()-1) != '/')
                    path.append("/");
                dir = opendir(path.c_str());
                tmp.setFullName(path);
                count = 0;
                this->path = path;
            }
            else
             count = 1;
          }
          catch(WhiteHawkUtil::Exception ex) { ex.print();}

        }

        WhiteHawkUtil::SystemPathCount WhiteHawkUtil::SystemPath::getCount(std::string path)
        {
          WhiteHawkUtil::AbstractFile file(path);

            return getCount(file);
        }




        WhiteHawkUtil::SystemPathCount WhiteHawkUtil::SystemPath::getCount(AbstractFile &objDir)
        {
            SystemPathCount count;
            std::string currPath;
            struct dirent *red;
            DIR *buff;

          try
          {

                if( !objDir.isDirectory())
                    return SystemPathCount(1);

                if( objDir.getFullName().at( objDir.getFullName().length()-1) != '/')
                    objDir.setFullName( objDir.getFullName()+'/' );


                buff = opendir(objDir.getFullName().c_str());

                if( !buff)
                    return count;

                while( NULL != (red = readdir(buff)) )
                {
                    WhiteHawkUtil::AbstractFile tmp( objDir.getFullName() + red->d_name);

                        if(tmp.isDirectory())
                        {
                            if( strcmp(red->d_name,".") != 0 && strcmp(red->d_name,"..") != 0  )
                                if( closedir(buff) == 0)
                                {
                                    currPath = red->d_name;
                                    SystemPathCount subCount = WhiteHawkUtil::SystemPath::getCount(tmp);

                                        count += tmp;
                                        count += subCount;
                                        buff = opendir(objDir.getFullName().c_str());

                                        do
                                        {
                                            red = readdir(buff);

                                            if( red == NULL)
                                                break;

                                        }while( currPath.compare(red->d_name) != 0 );
                                }
                        }
                        else
                            count += tmp;
                }
                closedir(buff);

            }catch(WhiteHawkUtil::Exception ex){ex.print();}

            return count;
        }

        WhiteHawkUtil::SystemPathCount WhiteHawkUtil::SystemPath::getCount()
        {
          SystemPathCount count;

           if( path.at( path.length()-1) != '/')
                path.append("/");

            rewinddir(dir);

            while( NULL != (red = readdir(dir)) )
	        {
              WhiteHawkUtil::AbstractFile tmp( path + red->d_name);

                    count += tmp;
            }
            rewinddir(dir);
            return count;
        }



        std::string WhiteHawkUtil::SystemPath::getPath()
        {
            return path;
        }


        WhiteHawkUtil::AbstractFile WhiteHawkUtil::SystemPath::getCurrentWDir()
        {
          char *buff;
          AbstractFile file;

                buff = getcwd(NULL, 0);
                if( buff )
                {
                    file.setFullName( buff );
                    free(buff);
                    return file;
                }
                else
                 throw (Exception("Failed getting current directory","WhiteHawkUtil::SystemPath::getCurrentWDir()"));
        }

        bool WhiteHawkUtil::SystemPath::setCurrentWDir(AbstractFile dir)
        {
            return chdir(dir.getPath().c_str()) == 0;
        }

        bool WhiteHawkUtil::SystemPath::setCurrentWDir(std::string dir)
        {
            return chdir(dir.c_str()) == 0;
        }


        bool WhiteHawkUtil::SystemPath::isEnd()
        {
               return eof;
        }

        WhiteHawkUtil::AbstractFile WhiteHawkUtil::SystemPath::find(std::string name)
        {
          WhiteHawkUtil::AbstractFile buff;

            for (buff = getNextFile();buff.getName().empty(); buff = getNextFile())
                if ( buff.getName().compare(name) == 0 )
                       return buff;

          return  WhiteHawkUtil::AbstractFile("");
       }


        WhiteHawkUtil::AbstractFile WhiteHawkUtil::SystemPath::getNextFile()
        {
            if( NULL != (red = readdir(dir)) )
            {
	           if( (strcmp(".", red->d_name) != 0) && (strcmp("..", red->d_name) != 0))
	           {
                    WhiteHawkUtil::AbstractFile tmp( path + red->d_name);
                    return tmp;
	           }
            }
            else
                eof = true;
            return  WhiteHawkUtil::AbstractFile("");
        }


        int WhiteHawkUtil::SystemPath::mkdirhier(const char *path)
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
                        throw( Exception("Failed to make directory.","Line 220 : WhiteHawkUtil::SystemPath::mkdirhier()"));
                }
            }

        return 0;
       }


       WhiteHawkUtil::SystemPath::~SystemPath()
       {
            if(red)
             free(red);
       }
