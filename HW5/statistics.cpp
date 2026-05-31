#include <iostream>
#include <limits>
#include <cmath>
#include <vector>
#include <algorithm>

class IStatistics {
public:
	virtual ~IStatistics() {}

	virtual void update(double next) = 0;
	virtual double eval() const = 0;
	virtual const char * name() const = 0;
};

class Min : public IStatistics {
public:
	Min() : m_min{std::numeric_limits<double>::max()} {
	}

	void update(double next) override {
		if (next < m_min) {
			m_min = next;
		}
	}

	double eval() const override {
		return m_min;
	}

	const char * name() const override {
		return "min";
	}

private:
	double m_min;
};

class Max: public IStatistics {
	public:
	    Max(): m_max{std::numeric_limits<double>::lowest()} {
		}

		void update(double next) override {
			if (next > m_max) {
				m_max = next;
			}
		}

		double eval() const override {
			return m_max;
		}

		const char * name() const override {
			return "max";
		}

private:
    double m_max;
};

class Mean: public IStatistics {
	public:
	    Mean(): m_mean{0} {
		}

		void update(double next) override {
			counter++;
			m_mean += (next - m_mean) / counter;
		}

		double eval() const override {
			return m_mean;
		}

		const char * name() const override {
			return "mean";
		}

private:
    double m_mean;
	size_t counter{0};
};

class Std: public IStatistics {
	public:
	    Std(): m_std{0} {
		}

		void update(double next) override {
			counter++;
			double delta = (next - m_mean);
			m_mean += (next - m_mean) / counter;
			double delta2 = (next - m_mean);
			m_m2 += delta * delta2;
			m_std = std::sqrt(m_m2 / counter);
		}

		double eval() const override {
			return m_std;
		}

		const char * name() const override {
			return "std";
		}

private:
    double m_mean;
	double m_m2{0};
	double m_std;
	size_t counter{0};
};

class Percentile: public IStatistics {
	public:
	    Percentile(double percentile, const char* name):
		    m_percentile{percentile}, m_name{name} {
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

		const char * name() const override {
			return m_name;
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
