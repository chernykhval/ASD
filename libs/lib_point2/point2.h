// Copyright 2024 Chernykh Valentin

#ifndef LIB_POINT2_POINT2_H_
#define LIB_POINT2_POINT2_H_

class Point2 {
private:
	int _x, _y;
public:
	Point2();
	Point2(int x, int y);
	Point2(const Point2& other);

	float distance_to(const Point2&);
};

#endif  // LIB_POINT_POINT2_H_

