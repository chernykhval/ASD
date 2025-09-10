// Copyright 2024 Chernykh Valentin

#ifndef LIB_POINT3_POINT3_H_
#define LIB_POINT3_POINT3_H_

class Point3 {
private:
	int _x, _y, _z;
public:
	Point3();
	Point3(int x, int y, int z);
	Point3(const Point3& other);

	float distance_to(const Point3&);
};

#endif  // LIB_POINT3_POINT3_H_
