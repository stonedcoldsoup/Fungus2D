#ifndef FUNGUS2D_RESOURCE_H
#define FUNGUS2D_RESOURCE_H

#include "common.h"

namespace Fungus2D
{
	class no_res_save:
		public exception
	{
	public:
		no_res_save(const std::string &m_res_type_name):
			exception(util::make_string("Resources of type ", m_res_type_name, " cannot be saved."),
					  exception::info_type("ResourceTypeName", m_res_type_name))
		{}
		
		no_res_save(exception &prev, const std::string &m_res_type_name):
			exception(prev, util::make_string("Resources of type ", m_res_type_name, " cannot be saved."),
					  exception::info_type("ResourceTypeName", m_res_type_name))
		{}
	};

	template <typename resT>
	struct res_type_def
	{
		typedef resT data_type;
	
		data_type *load_file(const std::string &m_filename)  {return nullptr;}
		data_type *load_memory(void *m_data, size_t m_size)  {return nullptr;}
		data_type *load_object(const util::any_type &m_data) {return nullptr;}
		data_type *load_duplicate(data_type *m_data)         {return nullptr;}
		
		void save_file(const std::string &m_filename, data_type *m_data) {}
	};
	
	template <typename res_type_defT>
	class res
	{
	public:
		typedef res_type_defT res_type_def_type;
		typedef
			typename res_type_def_type::data_type;
			data_type;
	
	private:
		std::string m_name;
		data_type *m_data;
		uint32_t n_refs;
	
		friend class res_manager;
		
		res(const std::string &m_name);
		~res();
	public:
	};
}

#endif
