#ifndef FUNGUS2D_CORE_H
#define FUNGUS2D_CORE_H

#include "common.h"

namespace Fungus2D
{
	using namespace phoenix;
	
	class core;
	
	

    // world interface used by core timekeeping.
    class world
    {
    private:
        core *m_core;
    public:
              core *get_core();
        const core *get_core() const;
    
        world(core *m_core);
        virtual ~world();
        
        virtual void render() = 0;
        virtual void update(float dt) = 0;
        
    };
    
	class core // timekeeper
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
		world *m_world;
	
	public:
		core(const args &m_args);
		~core();
		
		void set_world(world *m_world);
		
		void restart(const args &m_args);
		void restart(); // restart with the same arguments
		
		const args &get_args() const;

              world *get_world();
        const world *get_world() const;
		
			  RenderSystem &get_rendersystem();
		const RenderSystem &get_rendersystem() const;
		
        void run();
	};
}

#endif
