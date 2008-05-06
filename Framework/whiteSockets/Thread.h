class Thread
{

public:

	Thread ();


	virtual ~Thread ();

	bool CreateThread ();

	int	IsCreated ()
	{	return (this->hThread != NULL);	}

	DWORD		Timeout;

	HANDLE	GetThreadHandle ()
	{	return this->hThread;	}
	DWORD	GetThreadId ()
	{	return this->hThreadId;	}
	HANDLE	GetMainThreadHandle ()
	{	return this->hMainThread;	}
	DWORD	GetMainThreadId ()
	{	return this->hMainThreadId;	}

protected:

	virtual unsigned long Process (void* parameter);

	DWORD		hThreadId;
	HANDLE		hThread;
	DWORD		hMainThreadId;
	HANDLE		hMainThread;

private:

	static int runProcess (void* Param);

};
