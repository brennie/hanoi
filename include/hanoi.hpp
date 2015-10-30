#ifndef INCLUDE_HANOI_HPP
#define INCLUDE_HANOI_HPP

#include <array>
#include <exception>
#include <ostream>
#include <string>


class SolverException : public std::runtime_error {
public:
	using std::runtime_error::runtime_error;
};


class TowerIntegrityException : public SolverException {
public:
	using SolverException::SolverException;
};


class TowerEmptyException : public SolverException {
public:
	TowerEmptyException() : SolverException{"tower is empty"}
	{};
};


class TowerFullException : public SolverException {
public:
	TowerFullException() : SolverException{"tower is full"}
	{};
};


class HanoiSolver
{
public:
	const static size_t NUM_TOWERS = 3;

	const static size_t NUM_DISCS = 5;

	HanoiSolver();

	void solve(std::ostream& os);

private:
	class Tower {
	public:
		const static size_t MAX_HEIGHT = NUM_DISCS;

		Tower();

		unsigned top() const;
		void pop();
		void push(unsigned value);

		inline size_t height() const { return m_height; }
		inline bool empty() const { return m_height == 0; }

		unsigned operator[](size_t i) const;

	private:
		size_t m_height;
		std::array<unsigned, NUM_DISCS> m_discs;
	};

	void move(size_t from, size_t to);
	void move_stack(size_t from, size_t to, size_t num_discs, std::ostream& os);

	std::array<Tower, NUM_TOWERS> m_towers;

	friend std::ostream& operator<<(std::ostream&, const HanoiSolver& );
	friend std::ostream& operator<<(std::ostream&, const HanoiSolver::Tower&);
};

#endif
