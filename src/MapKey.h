#include <cstdint>
#include <cstddef>
#include <functional>

class MapKey
{
public:
	MapKey(uint32_t node1, uint32_t node2)
	{
		if(node1 < node2)
		{
			m_node1 = node1;
			m_node2 = node2;
		}
		else
		{
			// node1 should be smaller then node2, if not swap
			m_node1 = node2;
			m_node2 = node1;
		}
	};

	bool operator==(const MapKey & otherKey) const
	{
		return m_node1 == otherKey.m_node1 && m_node2 == otherKey.m_node2;
	}

	size_t getHash() const
	{
		return (static_cast<size_t>(m_node1) << 32) | (m_node2 & 0xffffffffL);
	}

private:
	uint32_t m_node1;
	uint32_t m_node2;
};

// custom specialization of std::hash can be injected in namespace std
namespace std
{
	template<> struct hash<MapKey>
	{
		std::size_t operator()(MapKey const & key) const noexcept
		{
			return key.getHash();
		}
	};
}

