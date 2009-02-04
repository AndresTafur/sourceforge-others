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

#include "SystemPathCount.hh"



WhiteHawkUtil::SystemPathCount::SystemPathCount(unsigned long long files, unsigned long long folders, unsigned long long links, unsigned long long fifo, unsigned long long blkdev, unsigned long long chardev)
{
    this->m_files   = files;
    this->m_folders = folders;
    this->m_link    = links;
    this->m_blkdev  = blkdev;
    this->m_chardev = chardev;
    this->m_fifo    = fifo;
}

void WhiteHawkUtil::SystemPathCount::setFilesCount(unsigned long long count)
{
    m_files = count;

}

void WhiteHawkUtil::SystemPathCount::setFoldersCount(unsigned long long count)
{
    m_files = count;
}


void WhiteHawkUtil::SystemPathCount::setLinksCount(unsigned long long count)
{
    m_link = count;
}


void WhiteHawkUtil::SystemPathCount::setFIFOCount(unsigned long long count)
{
    m_fifo = count;
}

void WhiteHawkUtil::SystemPathCount::setCharDevicesCount(unsigned long long count)
{
    m_chardev = count;
}

void WhiteHawkUtil::SystemPathCount::setBlockDevicesCount(unsigned long long count)
{
    m_blkdev = count;
}

unsigned long long WhiteHawkUtil::SystemPathCount::getFilesCount()
{
    return m_files;
}

unsigned long long WhiteHawkUtil::SystemPathCount::getFoldersCount()
{
    return m_folders;
}


unsigned long long WhiteHawkUtil::SystemPathCount::getLinksCount()
{
    return m_link;
}

unsigned long long WhiteHawkUtil::SystemPathCount::getFIFOCount()
{
    return m_fifo;
}

unsigned long long WhiteHawkUtil::SystemPathCount::getCharDevicesCount()
{
    return m_chardev;
}

unsigned long long WhiteHawkUtil::SystemPathCount::getBlockDevicesCount()
{
    return m_blkdev;
}


unsigned long long WhiteHawkUtil::SystemPathCount::getDevicesCount()
{
    return m_chardev + m_blkdev;
}

unsigned long long WhiteHawkUtil::SystemPathCount::getTotalCount()
{
    return m_files + m_folders + m_link + m_chardev + m_blkdev + m_fifo;
}

void WhiteHawkUtil::SystemPathCount::operator += (WhiteHawkUtil::FileInfo obj)
{
    if( obj.isLink())
        m_link++;
    else if( obj.isDirectory())
        m_folders++;
    else if( obj.isCharDevice())
        m_chardev++;
    else if( obj.isBlockDevice() )
        m_blkdev++;
    else if( obj.isFIFO())
        m_fifo++;
    else if( obj.isFile())
        m_files++;
}


void WhiteHawkUtil::SystemPathCount::operator -= (WhiteHawkUtil::FileInfo obj)
{
    if( obj.isLink())
        m_link--;
    else if( obj.isDirectory())
        m_folders--;
    else if( obj.isCharDevice())
        m_chardev--;
    else if( obj.isBlockDevice() )
        m_blkdev--;
    else if( obj.isFIFO())
        m_fifo--;
    else if( obj.isFile())
        m_files--;
}



void WhiteHawkUtil::SystemPathCount::operator += (WhiteHawkUtil::SystemPathCount obj)
{
    this->m_files   += obj.getFilesCount();
    this->m_folders += obj.getFoldersCount();
    this->m_link    += obj.getLinksCount();
    this->m_chardev += obj.getCharDevicesCount();
    this->m_blkdev  += obj.getBlockDevicesCount();
    this->m_fifo    += obj.getFIFOCount();
}


void WhiteHawkUtil::SystemPathCount::operator -= (WhiteHawkUtil::SystemPathCount obj)
{
    this->m_files   -= obj.getFilesCount();
    this->m_folders -= obj.getFoldersCount();
    this->m_link    -= obj.getLinksCount();
    this->m_chardev -= obj.getCharDevicesCount();
    this->m_blkdev  -= obj.getBlockDevicesCount();
    this->m_fifo    -= obj.getFIFOCount();
}
