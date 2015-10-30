#include <sstream>

#include "hanoi.hpp"


HanoiSolver::HanoiSolver() {
	for (size_t i = 0; i < Tower::MAX_HEIGHT; i++)
		m_towers[0].push(Tower::MAX_HEIGHT - i);
}


HanoiSolver::Tower::Tower() : m_height{0}, m_discs{{0, 0, 0, 0, 0}}
{}


unsigned HanoiSolver::Tower::top() const
{
	if (m_height == 0)
		throw TowerEmptyException();

	return m_discs[m_height - 1];
}


void HanoiSolver::Tower::pop()
{
	if (m_height == 0)
		throw TowerEmptyException();

	m_height--;
}


void HanoiSolver::Tower::push(unsigned value)
{
	if (m_height == MAX_HEIGHT)
		throw TowerFullException();
	else if (!empty() && value > top()) {
		std::stringstream err_buf;
		err_buf << "cannot put larger disc (size " << value << ") above smaller disc (size " << top() << ")";
		throw TowerIntegrityException{err_buf.str()};
	}

	m_discs[m_height++] = value;
}


unsigned HanoiSolver::Tower::operator[](size_t i) const
{
	if (i >= m_height) {
		std::stringstream err_buf;
		err_buf << "disc at requested height " << i << " invalid; tower has height of" << m_height;
		throw std::out_of_range{err_buf.str()};
	}

	return m_discs[i];
}


void HanoiSolver::move(size_t from, size_t to)
{
	if (from >= NUM_TOWERS)
	{
		std::stringstream err_buf;
		err_buf << "invalid tower: " << from;
		throw std::out_of_range{err_buf.str()};
	}
	else if (to >= NUM_TOWERS)
	{
		std::stringstream err_buf;
		err_buf << "invalid tower: " << to;
		throw std::out_of_range{err_buf.str()};
	}

	Tower& source = m_towers[from];
	Tower& dest = m_towers[to];

	unsigned value = source.top();
	dest.push(value);
	source.pop();
}

void HanoiSolver::solve(std::ostream& os)
{
	os << *this << std::endl;
	move_stack(0, NUM_TOWERS - 1, NUM_DISCS, os);
}


void HanoiSolver::move_stack(size_t from, size_t to, size_t num_discs, std::ostream& os)
{
	if (num_discs == 1) {
		move(from, to);
		os << *this << std::endl;
	}
	else
	{
		size_t temp_tower;

		if ((from == 0 && to == 1) || (from == 1 && to == 0))
			temp_tower = 2;
		else if ((from == 0 && to == 2) || (from == 2 && to == 0))
			temp_tower = 1;
		else
			temp_tower = 0;

		move_stack(from, temp_tower, num_discs - 1, os);

		move(from, to);
		os << *this << std::endl;

		move_stack(temp_tower, to, num_discs - 1, os);
	}

}


std::ostream& operator<<(std::ostream& os, const HanoiSolver& solver)
{
	return os << solver.m_towers[0] << std::endl
	          << solver.m_towers[1] << std::endl
	          << solver.m_towers[2] << std::endl;
}


std::ostream& operator<<(std::ostream& os, const HanoiSolver::Tower& tower)
{
	os << "| ";

	for (size_t i = 0; i < tower.height(); i++) {
		os << '[' << tower[i] << ']';
	}

	return os;
}