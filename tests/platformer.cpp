#include <Fungus2D.h>

using namespace Fungus2D;
using namespace phoenix;

// underground platformer movement rules.
// for now, we will do a speed hacked version of the
// warping idea.

struct tile
{
	enum type_e
	{
		normal_type = 0,
		dark_type,
		type_count
	};
	
	static Color colors[type_count];
	
	type_e e_type;
};

Color tile::colors[type_count] = {Color(60, 80, 60), Color(20, 20, 30)};

#define MAP_WIDTH   20
#define MAP_HEIGHT  15
#define TILE_WIDTH  32
#define TILE_HEIGHT 32

struct map
{
	tile m_tiles[MAP_WIDTH][MAP_HEIGHT];

	map()
	{
		for (int i = 0; i < MAP_WIDTH; ++i)
		{
			for (int j = 0; j < MAP_HEIGHT/2; ++j)
			{
				m_tiles[i][j].e_type = tile::normal_type;
			}
			
			for (int j = MAP_HEIGHT/2; j < MAP_HEIGHT; ++j)
			{
				m_tiles[i][j].e_type = tile::dark_type;
			}
		}
		
		for (int i = 5; i < 10; ++i)
		{
			for (int j = 0; j < MAP_HEIGHT - 2; ++j)
			{
				m_tiles[i][j].e_type = tile::normal_type;
			}
		}
		
		for (int i = 10; i < 15; ++i)
		{
			for (int j = MAP_HEIGHT - 4; j < MAP_HEIGHT - 2; ++j)
			{
				m_tiles[i][j].e_type = tile::normal_type;
			}
		}
		
		// stairs
		for (int i = 5; i < 10; ++i)
		{
			for (int j = MAP_HEIGHT - 2 - (5 - (i - 5)); j < MAP_HEIGHT - 2; ++j)
			{
				m_tiles[i][j].e_type = tile::dark_type;
			}
		}
	}
	
	void draw_tile(RenderSystem &m_rs, int x, int y)
	{
		phoenix::Rectangle m_rect(Vector2d(x * TILE_WIDTH, y * TILE_HEIGHT), Vector2d(TILE_WIDTH, TILE_HEIGHT));
		m_rs.drawRectangle(m_rect,
						   tile::colors[m_tiles[x][y].e_type],
						   tile::colors[m_tiles[x][y].e_type],
						   tile::colors[m_tiles[x][y].e_type],
						   tile::colors[m_tiles[x][y].e_type]);
	}
	
	void draw(RenderSystem &m_rs)
	{
		for (int i = 0; i < MAP_WIDTH; ++i)
		{
			for (int j = 0; j < MAP_HEIGHT; ++j)
				draw_tile(m_rs, i, j);
		}
	}
};

// 9.8 meters per second per second
#define Y_ACCEL (9.8)

struct player
{
	phoenix::Rectangle m_actor, m_proj;
	Vector2d m_velocity;
	
	tile::type_e e_world;
	bool b_grounded, b_jumped;
	int y_ground;
	
	player():
		m_actor(Vector2d(20, 20), Vector2d(TILE_WIDTH - 10, TILE_HEIGHT - 5)),
		m_proj(Vector2d(0,0), Vector2d(TILE_WIDTH - 10, TILE_HEIGHT - 5)),
		m_velocity(0,0),
		e_world(tile::normal_type),
		b_grounded(false),
		b_jumped(false)
	{}
	
	void ground_interact(const map &m_map, int curx, int miny, int maxy, int height)
	{
		if (m_map.m_tiles[curx][miny].e_type != m_map.m_tiles[curx][maxy].e_type)
		{
			m_velocity.setY(0);
			switch (m_map.m_tiles[curx][maxy].e_type)
			{
			case tile::dark_type:
				//if (!b_jumped)
				//{
					m_actor.setY(maxy * TILE_WIDTH - height);
					b_grounded = true;
					y_ground = maxy;
				//}
				break;
			case tile::normal_type:
				m_actor.setY(maxy * TILE_WIDTH - height / 2);
				break;
			};
		}
	}
	
	void collide(const map &m_map)
	{
		int minx, maxx, miny, maxy;
		minx = m_actor.getX() / TILE_WIDTH;
		miny = m_actor.getY() / TILE_WIDTH + m_actor.getHeight() * 0.5f / TILE_WIDTH;
		
		maxx = (m_actor.getX() + m_actor.getWidth())  / TILE_WIDTH;
		maxy = (m_actor.getY() + m_actor.getHeight()) / TILE_HEIGHT;
		
		if (maxx >= MAP_WIDTH) maxx = MAP_WIDTH - 1;
		if (maxy >= MAP_HEIGHT) maxy = MAP_HEIGHT - 1;
		
		if (miny != maxy)
		{
			ground_interact(m_map, minx, miny, maxy, m_actor.getHeight());
			ground_interact(m_map, maxx, miny, maxy, m_actor.getHeight());
		}
		
		minx = m_actor.getX() / TILE_WIDTH;
		maxx = (m_actor.getX() + m_actor.getWidth())  / TILE_WIDTH;
		
		if (minx != maxx)
		{
			int cury = miny;
			if (m_map.m_tiles[minx][cury].e_type != m_map.m_tiles[maxx][cury].e_type)
			{
				m_velocity.setX(0);
				switch (m_map.m_tiles[minx][cury].e_type)
				{
				case tile::dark_type:
					m_actor.setX(maxx * TILE_WIDTH);
					break;
				case tile::normal_type:
					m_actor.setX(maxx * TILE_WIDTH - m_actor.getWidth());
					break;
				};
			}
		}
		
		if (b_grounded)
		{
			int minx, maxx;
			minx = m_actor.getX() / TILE_WIDTH;
			maxx = (m_actor.getX() + m_actor.getWidth())  / TILE_WIDTH;
			
			if (!(m_map.m_tiles[minx][y_ground].e_type == tile::dark_type ||
			      m_map.m_tiles[maxx][y_ground].e_type == tile::dark_type))
				b_grounded = false;
		}
	}
	
	void update(const map &m_map, float dt)
	{
		// bounds checking
		float maxxp = MAP_WIDTH*TILE_WIDTH - m_actor.getWidth();
		float maxyp = MAP_HEIGHT*TILE_HEIGHT - m_actor.getHeight();
	
		if (m_actor.getX() < 0) m_actor.setX(0);
		if (m_actor.getY() < 0) m_actor.setY(0);
		if (m_proj.getX() < 0) m_proj.setX(0);
		if (m_proj.getY() < 0) m_proj.setY(0);
		if (m_actor.getX() > maxxp) m_actor.setX(maxxp);
		if (m_actor.getY() > maxyp) m_actor.setY(maxyp);
		if (m_proj.getX() > maxxp) m_proj.setX(maxxp);
		if (m_proj.getY() > maxyp) m_proj.setY(maxyp);
	
		if (e_world == tile::normal_type)
		{
			// if grounded
			if (b_grounded)
			{
//				m_velocity = Vector2d(0,0);
				
				// move
				if (EventReceiver::Instance()->getKey(PHK_LEFT))
					m_velocity.setX(-150);
				else if (EventReceiver::Instance()->getKey(PHK_RIGHT))
					m_velocity.setX(150);
			
				// integrate
				m_actor.setPosition(m_actor.getPosition() + m_velocity*dt);
				
				collide(m_map);
				
				// jump
				if (EventReceiver::Instance()->getKeyPressed(PHK_UP))
				{
					m_velocity -= Vector2d(0, 300);
					m_velocity.setX(m_velocity.getX() * 0.5);
					b_grounded = false;
					b_jumped = true;
				}
			}
			else // if in the air
			{
				// gravity
				m_velocity += Vector2d(0,Y_ACCEL*dt*dt * 5000.0f);
				
				// integrate
				m_actor.setPosition(m_actor.getPosition() + m_velocity*dt);
				
				collide(m_map);
			}
		}
	}
	
	void draw(RenderSystem &m_rs)
	{
		switch (e_world)
		{
		case tile::dark_type:
		case tile::normal_type:
			m_rs.drawRectangle(m_actor,
						   Color(255, 0, 255),
						   Color(255, 0, 255),
						   Color(255, 0, 255),
						   Color(255, 0, 255));
			break;
		default:
			break;
		};
	}
};

template <typename T>
struct testme
{
	typedef T type;
};

int main()
{
	try
	{
		throw Fungus2D::exception("hi!",
								  Fungus2D::exception::info_type("a", 123),
								  Fungus2D::exception::info_type("b", 321));
	}
	catch (Fungus2D::exception &e)
	{
		std::cout << e;
	}

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
