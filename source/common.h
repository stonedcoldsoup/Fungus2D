#ifndef FUNGUS2D_COMMON_H
#define FUNGUS2D_COMMON_H

#include <Phoenix.h>

#define FUNGUSUTIL_HAVE_gettimeofday
#include <fungus_booster/fungus_booster.h>

namespace Fungus2D
{
	// helpful namespace aliases
	namespace util = fungus_util;
	namespace conc = fungus_concurrency;
	namespace net  = fungus_net;
	
	namespace detail
	{
		template <typename containerT, typename... infoT>
		class list_unroller;
		
		template <typename containerT, typename infoT, typename... infoU>
		class list_unroller<containerT, infoT, infoU...>
		{
		public:
			static inline void __build_list(containerT &m, const infoT &infoV, infoU&&... infoW)
			{
				m.push_back(infoV);
				list_unroller<containerT, infoU...>::__build_list(m, std::forward<infoU>(infoW)...);
			}
		};
		
		template <typename containerT>
		class list_unroller<containerT>
		{
		public:
			static inline void __build_list(containerT &m) {}
		};
	}
	
	class exception:
		public std::exception
	{
	public:
		typedef
			std::pair<std::string, util::any_type>
			info_type;
	private:
		struct data
		{
			std::string m_what;
			std::vector<info_type> m_info;
		};
		
		std::list<data> m_data;
	
		template <typename... infoT>
		struct info_list_unroller:
			detail::list_unroller<std::vector<info_type>, infoT...>
		{};
	public:
		exception(const exception &e):
			m_data(e.m_data)
		{}
		
		exception(exception &&e):
			m_data(std::move(e.m_data))
		{}
		
		exception &operator =(const exception &e)
		{
			std::copy(e.m_data.begin(), e.m_data.end(), std::back_inserter(m_data));
			return *this;
		}
		
		exception &operator =(exception &&e)
		{
			m_data.swap(e.m_data);
			return *this;
		}
	
		template <typename... infoT>
		exception(const std::string &m_what, infoT&&... infoV)
		{
			data m_datum;
			m_datum.m_what = m_what;
			info_list_unroller<infoT...>::__build_list(m_datum.m_info, std::forward<infoT>(infoV)...);
			
			m_data.push_back(std::move(m_datum));
		}
		
		template <typename... infoT>
		exception(exception &prev, const std::string &m_what, infoT&&... infoV)
		{
			data m_datum;
			m_datum.m_what = m_what;
			info_list_unroller<infoT...>::__build_list(m_datum.m_info, std::forward<infoT>(infoV)...);
			
			m_data.push_front(std::move(m_datum));
			m_data.splice(m_data.end(), prev.m_data);
		}
		
		virtual ~exception() throw() {}
		
		virtual const char *what() const throw()
		{
			if (m_data.empty())
				return "";
			else
				return m_data.front().m_what.c_str();
		}
		
		virtual std::vector<info_type> info() const throw()
		{
			if (m_data.empty())
				return std::vector<info_type>();
			else
				return m_data.front().m_info;
		}
		
		virtual bool empty() const throw() {return m_data.empty();}
		
		// return false when no data is left.
		virtual bool pop() throw()
		{
			m_data.pop_front();
			return !m_data.empty();
		}
		
		friend inline void operator <<(std::ostream &m_os, const exception &_e);
	};
	
	inline void operator <<(std::ostream &m_os, const Fungus2D::exception &_e)
	{
		exception e(_e);
		m_os << "EXCEPTION" << std::endl;
		while (!e.empty())
		{
			m_os << " ... caused by ..." << std::endl
				 << "    what=" << e.what() << std::endl;
			
			for (const auto &m_info: e.info())
				m_os << "    " << m_info.first << " = " << m_info.second << std::endl;
			
			e.pop();
		}
	}
}

#endif
