#pragma once

template<class Type>
class Vector2D
{
private:
	Type x;
	Type y;
public:
	const Type GetX() const { return x; }
	const Type GetY() const { return y; }
	const Vector2D GetVector() const { return Vector2D(x, y); }
	void SetVector2D(const Type X, const Type Y) { x = X; y = Y; }
	void SetX(const Type X) const { x = X; }
	void SetY(const Type Y) const { y = Y; }

	Type PlusEqualsX(const Type& X) { x += X; return x; }
	Type PlusEqualsY(const Type& Y) { y += Y; return y; }
	//Type& PlusEqualsX(const Type& X) { x += X; return this; }
	//Type& PlusEqualsY(const Type& Y) { y += Y; return this; }

	Vector2D operator=(const Vector2D& vec) { x = vec.x; y = vec.y; return Vector2D(x, y); }

	//Vector2D& operator=(const Vector2D& vec) { x = vec.x; y = vec.y; return this; }
	Vector2D& operator+=(const Vector2D& vec) { x += vec.x; y += vec.y; return this; }
	Vector2D& operator-=(const Vector2D& vec) { x -= vec.x; y -= vec.y; return this; }
	Vector2D& operator*=(const Vector2D& vec) { x *= vec.x; y *= vec.y; return this; }
	Vector2D& operator/=(const Vector2D& vec) { if (vec.x != 0 && vec.y != 0) { x /= vec.x; y /= vec.y; } return this; }
	Type operator+=(const Type newType){ y}
	explicit Vector2D() : x(0), y(0) {}
	explicit Vector2D(const Type X, const Type Y) : x(X), y(Y){}
};