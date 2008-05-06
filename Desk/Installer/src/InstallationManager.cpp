

class InstallationManager : public wxThread
{
public:

	InstallationManager() : wxThread(wxTHREAD_JOINABLE)
	{
		wxThread::Create();
	}



	void* Entry()
	{
		path.Prepend( wxT("mount ") );
		path.Append( wxT(" /mnt/root"));
		popen(path.ToAscii(),"r");
		mkdir("/mnt/root/apps",   S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
		mkdir("/mnt/root/bin",    S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
		mkdir("/mnt/root/sbin",   S_IRWXU | S_IRWXG | S_IROTH );
		mkdir("/mnt/root/lib",    S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
		mkdir("/mnt/root/include",S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
		mkdir("/mnt/root/dev",    S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
		mkdir("/mnt/root/root",   S_IRWXU | S_IRWXG | S_IXOTH);
		mkdir("/mnt/root/home",   S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

		while(true)
		{
			fprintf(stderr,"[ho]");
			this->Sleep(750);
		}
	}


	void setPath(wxString path)
	{
		this->path = path;
	}

protected:
long progress;
wxString path;
};
