struct wd_in {
	u_int size;
	u_int len;
	string data<300000>;
};

program ProxyServer
{
	version ProxyV1
	{  
		wd_in fetchPage(string) = 1;  
	} = 1;  
} = 99;
