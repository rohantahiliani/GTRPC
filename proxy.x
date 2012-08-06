struct wd_in {
	size_t size;
	size_t len;
	string data<10240>;
};


program ProxyServer
{
	version ProxyV1
	{  
		wd_in fetchPage(string) = 1;  
	} = 1;  
} = 99;
