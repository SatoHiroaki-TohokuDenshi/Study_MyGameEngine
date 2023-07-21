#pragma once

class SphereCollider {
	float radius_;		//”¼Œa
public:
	SphereCollider();
	SphereCollider(float r);
	~SphereCollider();
	float GetRadius() { return radius_; };
};