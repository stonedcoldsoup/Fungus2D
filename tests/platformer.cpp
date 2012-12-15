#include <Fungus2D.h>
#include <event.h>

using namespace Fungus2D;
using namespace phoenix;

class foo
{
public:
    typedef
        publisher_subscriber_set<foo, const std::string &, const util::any_type &>
        named_object_psw;
        
    static named_object_psw::publisher_type m_publisher;
    named_object_psw::subscription_type m_subs[2];
    
    void print_object(const std::string &m_str, const util::any_type &m_obj)
    {
        std::cout << m_str << "=" << m_obj << std::endl;
    }
    
    void print_object_reverse(const std::string &m_str, const util::any_type &m_obj)
    {
        std::cout << m_obj << "=" << m_str << std::endl;
    }
        
    foo()
    {
        m_subs[0] = m_publisher.subscribe(this, &foo::print_object);
        m_subs[1] = m_publisher.subscribe(this, &foo::print_object_reverse);
    }
};

foo::named_object_psw::publisher_type foo::m_publisher;
foo::named_object_psw::writer_type m_writer(foo::m_publisher);

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
	
	{
	    foo m_foo;
	    m_writer("hello", 42);
	}
	m_writer("nowhere", 123);

	core::args m_args;
	core m_core(m_args);
	
	/*RenderSystem &m_rendersystem = m_core.get_rendersystem();
	map m_map;
	player m_player;
	
	while (m_rendersystem.run())
	{
		m_player.update(m_map, (float)m_core.get_timer().getTime());
		m_core.get_timer().reset();
	
		m_map.draw(m_rendersystem);
		m_player.draw(m_rendersystem);
	}*/
	
	return 0;
}
