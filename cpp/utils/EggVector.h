#include <cmath>
#include <cstddef>
#include <iostream>
#include <vector>

namespace egg {
	template <typename T = int>
	struct Vector2 {
		union {
			T x;
			T a;
			T u;
			T first;
		};

		union {
			T y;
			T b;
			T v;
			T second;
		};

		Vector2() : x(0), y(0) {}
		Vector2(T _x, T _y) : x(_x), y(_y) {}

		/**
		* Adds two vectors
		* @param other second operand
		* @return result of element-wise addition
		*/
		Vector2<T> add(const Vector2<T>& other) const { return Vector2<T>(x + other.x, y + other.y); }
		Vector2<T> operator+(const Vector2<T>& other) const { return Vector2<T>(x + other.x, y + other.y); }
		void operator+=(const Vector2<T>& other) {
			x += other.x;
			y += other.y;
		}

		/**
		* Subtracts two vectors
		* @param other second operand
		* @return result of element-wise subtraction
		*/
		Vector2<T> subtract(const Vector2<T>& other) const { return Vector2<T>(x - other.x, y - other.y); }
		Vector2<T> operator-(const Vector2<T>& other) const { return Vector2<T>(x - other.x, y - other.y); }
		void operator-=(const Vector2<T>& other) {
			x -= other.x;
			y -= other.y; 
		}

		/**
		* Scales a vector
		* @param scalar value
		* @return result of scalar multiplication
		*/
		Vector2<T> scale(const T& s) const { return Vector2<T>(x * s, y * s); }
		Vector2<T> operator*(const T& s) const { return Vector2<T>(x * s, y * s); }

		/**
		* Multiplies two vectors element-wise
		* @param other second operand
		* @return result of element-wise multiplication 
		*/
		Vector2<T> multiply(const Vector2<T>& other) const { return Vector2<T>(x * other.x, y * other.y); }
		Vector2<T> operator*(const Vector2<T>& other) const { return Vector2<T>(x * other.x, y * other.y); }

		/**
		* Divides a vector by a scalar 
		* @param scalar divisor
		* @return result of scaling
		*/
		Vector2<T> divide(const T& s) const { return Vector2<T>(x / s, y / s); }
		Vector2<T> operator/(const T& s) const { return Vector2<T>(x / s, y / s); }

		/**
		* Multiplies two vectors element-wise
		* @param other second operand
		* @return result of element-wise multiplication 
		*/
		Vector2<T> divide(const Vector2<T>& other) const { return Vector2<T>(x / other.x, y / other.y); }
		Vector2<T> operator/(const Vector2<T>& other) const { return Vector2<T>(x / other.x, y / other.y); }

		bool equals(const Vector2<T>& other) const { return x == other.x && y == other.y; }
		bool operator==(const Vector2<T>& other) const { return x == other.x && y == other.y; }

		bool not_equals(const Vector2<T>& other) const { return !equals(other); }
		bool operator!=(const Vector2<T>& other) const { return !equals(other); }

		bool lessThan(const Vector2<T>& other) const { return x < other.x && y < other.y; }
		bool operator<(const Vector2<T>& other) const { return x < other.x && y < other.y; }

		bool lessThanOrEqualTo(const Vector2<T>& other) const { return x <= other.x && y <= other.y; }
		bool operator<=(const Vector2<T>& other) const { return x <= other.x && y <= other.y; }

		bool greaterThan(const Vector2<T>& other) const { return x > other.x && y > other.y; }
		bool operator>(const Vector2<T>& other) const { return x > other.x && y > other.y; }

		bool greaterThanOrEqualTo(const Vector2<T>& other) const { return x >= other.x && y >= other.y; }
		bool operator>=(const Vector2<T>& other) const { return x >= other.x && y >= other.y; }

		template <typename R>
		R mag() const {
			return std::sqrt(std::pow(static_cast<R>(x), 2), std::pow(static_cast<R>(y), 2));
		}

		void print(std::string end = "\n") {
			std::cout << "(" << x << ", " << y << ")" << end;
		}

		std::array<Vector2<T>, 4> getNeighbors() {
			return std::array<Vector2<T>, 4>({Vector2<T>(x, y - 1), Vector2<T>(x + 1, y), Vector2<T>(x, y + 1), Vector2<T>(x - 1, y)});
		}

		template <typename W>
		std::size_t getIndex(W width) {
			return y * width + x;
		}
	};

	typedef egg::Vector2<int> Vector2i;
	typedef egg::Vector2<std::size_t> Vector2s;
	typedef egg::Vector2<float> Vector2f;
	typedef egg::Vector2<double> Vector2d;
}
