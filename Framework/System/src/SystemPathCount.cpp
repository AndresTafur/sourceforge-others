#include "SystemPathCount.hh"



WhiteHawkSystem::SystemPathCount::SystemPathCount(unsigned long long files, unsigned long long folders, unsigned long long links, unsigned long long dev)
{
    this->m_files   = files;
    this->m_folders = folders;
    this->m_link    = links;
    this->m_dev     = dev;
}

unsigned long long WhiteHawkSystem::SystemPathCount::getFilesCount()
{
    return m_files;
}

unsigned long long WhiteHawkSystem::SystemPathCount::getFoldersCount()
{
    return m_folders;
}


unsigned long long WhiteHawkSystem::SystemPathCount::getLinksCount()
{
    return m_link;
}

unsigned long long WhiteHawkSystem::SystemPathCount::getDevicesCount()
{
    return m_dev;
}

unsigned long long WhiteHawkSystem::SystemPathCount::getTotal()
{
    return m_files + m_folders + m_link + m_dev;
}

