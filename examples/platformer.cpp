#include <Fungus2D.h>

int main()
{
	core::args m_args;
	core m_core(m_args);
	
	RenderSystem &m_rendersystem = m_core.get_rendersystem();
	map m_map;
	player m_player;
	
	while (m_rendersystem.run())
	{
		m_player.update(m_map, (float)m_core.get_timer().getTime());
		m_core.get_timer().reset();
	
		m_map.draw(m_rendersystem);
		m_player.draw(m_rendersystem);
	}
	
	return 0;
}
