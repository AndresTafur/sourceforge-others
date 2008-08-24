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

        WhiteHawkSystem::SystemPathCount WhiteHawkSystem::SystemPath::getCount(std::string path)
        {
            struct dirent *red;
            SystemPathCount count;

            if( path.at( path.length()-1) != '/')
                path.append("/");

            DIR *buff = opendir(path.c_str());

            if( !buff)
                return count;

            while( NULL != (red = readdir(buff)) )
	        {
              WhiteHawkSystem::AbstractFile tmp( path + red->d_name);

                    count += tmp;
            }
             closedir(buff);

            return count;
        }




        WhiteHawkSystem::SystemPathCount WhiteHawkSystem::SystemPath::getCount(AbstractFile &objDir)
        {
            SystemPathCount count;
            struct dirent *red;
            DIR *buff;


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

                                count += subCount;
                                count.setFoldersCount( count.getFoldersCount()+1);
                        }

                    }

                    count += tmp;
             }
             closedir(buff);

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
                 throw (Exception("Failed getting current directory","Line 145 : WhiteHawkSystem::SystemPath::getCurrentWDir()"));
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
