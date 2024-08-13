#pragma once

#include <string>
#include <memory>
#include "Components.h"
class Entity
{
	friend class EntityManager;

	bool m_active = true;
	size_t m_id = 0;
	std::string m_tag = "default";
	Entity(const size_t dataId, const std::string& dataTag);

public:

	std::shared_ptr<CShape> cShape;
	std::shared_ptr<CTransform> cTransform;

	bool isAlive() const;
	const std::string& tag() const;
	const size_t id() const;
	void destroy();
};

