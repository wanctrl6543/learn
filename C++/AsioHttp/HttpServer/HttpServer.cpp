#include "HttpServer.h"
#include <iostream>
#include <string>
#include "GlobalDef.h"


	IHttpServer* IHttpServer::Create(IHttpServerNotify*pNotify)
	{
		IHttpServer* pServer = new chttpserver(pNotify);
		return pServer;
	}

	chttpserver::chttpserver(IHttpServerNotify*pNotify)
		: m_pNotify(pNotify)
	{
		g_phttpserver = this;
	}

	chttpserver::~chttpserver()
	{
		g_phttpserver = nullptr;
	}

	void chttpserver::HandleHttpReq(void*handler,const char*api, const char* param, char**pReply)
	{
		std::string cpath(api);
		std::set<std::string>::iterator it = m_setPath.find(cpath);
		if (it != m_setPath.end())
		{
			if (m_pNotify)
			{
				m_pNotify->OnAPItrigger(handler, api, param, pReply);
			}
		}
		
	}

	int32_t chttpserver::StartHttpServer(const char* ip, int32_t port)
	{
		m_strapi = ip;
		m_nport = port;
		if (StartThread())
		{
			return 0;
		}
		return -1;
	}

	void chttpserver::StopHttpServer()
	{
		if (m_pserver)
		{
			m_pserver->stop();
			delete m_pserver;
			m_pserver = nullptr;
		}
		WaitForStop();
	}

	void chttpserver::RegAPIpath(const char* path)
	{
		m_setPath.insert(std::string(path));
	}

	void chttpserver::AsyncReply(void* handler, const char* reply)
	{
		if (m_pserver)
		{
			m_pserver->AsyncReply(handler, reply);
		}
	}

	void chttpserver::ThreadProcMain(void)
	{
		try
		{
			char ch[32] = { 0 };
			_itoa_s(m_nport, ch, 32, 10);
			m_pserver = new http::server2::server(m_strapi, std::string(ch), "/", 10);
			if (m_pserver)
			{
				m_pserver->run();
			}
		}
		catch (std::exception& e)
		{
			std::cerr << "exception: " << e.what() << "\n";			
		}		
	}

