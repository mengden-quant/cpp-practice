#include <iostream>
#include <limits>
#include <cmath>
#include <vector>
#include <algorithm>

class IStatistics {
public:
    explicit IStatistics(const char* statistic_name, double value = 0.0)
	    : m_name{statistic_name}, m_value{value} {};
	virtual ~IStatistics() {}

	virtual void update(double next) = 0;
	virtual double eval() const = 0;
	const char * name() {return m_name;}

protected:
    const char* m_name;
	double m_value;
};

class Min : public IStatistics {
public:
	Min() : IStatistics{"min", std::numeric_limits<double>::max()} {
	}

	void update(double next) override {
		if (next < m_value) {
			m_value = next;
		}
	}

	double eval() const override {
		return m_value;
	}
};

class Max: public IStatistics {
	public:
	    Max(): IStatistics{"max", std::numeric_limits<double>::lowest()} {
		}

		void update(double next) override {
			if (next > m_value) {
				m_value = next;
			}
		}

		double eval() const override {
			return m_value;
		}
};

class Mean: public IStatistics {
	public:
	    Mean(): IStatistics{"mean", 0.0}, counter{0} {
		}

		void update(double next) override {
			counter++;
			m_value += (next - m_value) / counter;
		}

		double eval() const override {
			return m_value;
		}

private:
	size_t counter;
};

class Std: public IStatistics {
	public:
	    Std(): IStatistics{"std", 0.0}, m_mean{0.0}, m_m2{0.0}, counter{0} {
		}

		void update(double next) override {
			counter++;
			double delta = (next - m_mean);
			m_mean += (next - m_mean) / counter;
			double delta2 = (next - m_mean);
			m_m2 += delta * delta2;
			m_value = std::sqrt(m_m2 / counter);
		}

		double eval() const override {
			return m_value;
		}

private:
    double m_mean;
	double m_m2;
	size_t counter;
};

class Percentile: public IStatistics {
	public:
	    Percentile(double percentile, const char* name):
		    IStatistics{name}, m_percentile{percentile}, m_name{name} {
		}

		void update(double next) override {
			m_values.push_back(next);
		}

		double eval() const override {
			if (m_values.empty()) {
				return 0.0;
			}
			std::vector<double> sorted_values = m_values;
			std::sort(sorted_values.begin(), sorted_values.end());
			const size_t index = static_cast<size_t>(
				std::ceil(m_percentile * (sorted_values.size() - 1)));
			return sorted_values[index];
		}

private:
    double m_percentile;
	const char* m_name;
	std::vector<double> m_values;
};

int main() {

	const size_t statistics_count = 6;
	IStatistics *statistics[statistics_count];

	statistics[0] = new Min{};
	statistics[1] = new Max{};
	statistics[2] = new Mean{};
	statistics[3] = new Std{};
	statistics[4] = new Percentile{0.90, "pct90"};
	statistics[5] = new Percentile{0.95, "pct95"};

	double val = 0;
	size_t input_count = 0;
	while (std::cin >> val) {
		++input_count;
		for (size_t i = 0; i < statistics_count; ++i) {
			statistics[i]->update(val);
		}
	}

	// Handle invalid input data
	if (!std::cin.eof() && !std::cin.good()) {
		std::cerr << "Invalid input data\n";
		return 1;
	}

	if (input_count == 0) {
		return 0;
    }

	// Print results if any
	for (size_t i = 0; i < statistics_count; ++i) {
		std::cout << statistics[i]->name()
		          << " = "
			      << statistics[i]->eval()
				  << std::endl;
	}

	// Clear memory - delete all objects created by new
	for (size_t i = 0; i < statistics_count; ++i) {
		delete statistics[i];
	}

	return 0;
}
