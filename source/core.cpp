#include "core.h"

namespace Fungus2D
{
	core::core(const args &m_args):
		m_args(m_args),
		m_rendersystem(m_args.m_size,
					   m_args.b_fs, m_args.b_resize),
		m_timer(m_timer)
	{
		m_rendersystem.setResizeBehavior(m_args.e_rzb);
		m_timer.start();
	}
	
	core::~core() {}
	
	void core::restart(const args &m_args)
	{
		this->m_args = m_args;
	
		m_rendersystem.initialize(m_args.m_size, m_args.b_fs, m_args.b_resize);
		m_rendersystem.setResizeBehavior(m_args.e_rzb);
	}
	
	void core::restart()
	{
		restart(m_args);
	}
	
	const core::args &core::get_args() const
	{
		return m_args;
	}
	
		  RenderSystem &core::get_rendersystem()       {return m_rendersystem;}
	const RenderSystem &core::get_rendersystem() const {return m_rendersystem;}
	
		  Timer &core::get_timer()       {return m_timer;}
	const Timer &core::get_timer() const {return m_timer;}
}
