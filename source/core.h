#ifndef FUNGUS2D_CORE_H
#define FUNGUS2D_CORE_H

#include <Phoenix.h>

namespace Fungus2D
{
	using namespace phoenix;

	class core
	{
	public:
		struct args
		{
			Vector2d m_size;
			bool b_fs, b_resize;
			E_RESIZE_BEHAVIOR e_rzb;
		
			args(const Vector2d &m_size = Vector2d(800, 600),
				 bool b_fs = false,
				 bool b_resize = true,
				 E_RESIZE_BEHAVIOR e_rzb = RZB_SCALE):
				m_size(m_size), b_fs(b_fs),
				b_resize(b_resize), e_rzb(e_rzb)
			{}
		};
	private:
		args m_args;
		RenderSystem m_rendersystem;
		Timer m_timer;
	
	public:
		core(const args &m_args);
		~core();
		
		void restart(const args &m_args);
		void restart(); // restart with the same arguments
		
		const args &get_args() const;
		
			  RenderSystem &get_rendersystem();
		const RenderSystem &get_rendersystem() const;
		
			  Timer &get_timer();
		const Timer &get_timer() const;
	};
}

#endif
