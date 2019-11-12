#include "SceneNode.hpp"
#include "CategoryID.hpp"
#include <cassert>

SceneNode::SceneNode():mChildren(), mParent(nullptr)
{
}

void SceneNode::attachChild(Ptr child)
{
	child->mParent = this;
	mChildren.push_back(std::move(child));
}

SceneNode::Ptr SceneNode::detachChild(const SceneNode& node)
{
	auto found = std::find_if(mChildren.begin(), mChildren.end(), [&](Ptr& p) {return p.get() == &node; });
	assert(found != mChildren.end());

	Ptr result = std::move(*found);
	result->mParent = nullptr;
	mChildren.erase(found);
	return result;
}

void SceneNode::update(sf::Time dt)
{
	updateCurrent(dt);
	updateChildren(dt);
}

sf::Vector2f SceneNode::getWorldPosition() const
{
	return getWorldTransform() * sf::Vector2f();
}

sf::Transform SceneNode::getWorldTransform() const
{
	sf::Transform transform = sf::Transform::Identity;
	for (const SceneNode* node = this; node != nullptr; node = node->mParent)
	{
		transform = node->getTransform() * transform;
	}
	return transform;
}

unsigned int SceneNode::getCategory() const
{
	return static_cast<int>(CategoryID::Scene);
}

void SceneNode::onCommand(const Command& command, sf::Time dt)
{
	//Command current node, if the category matches
	//Is this command for me?
	if (command.category & getCategory())
	{
		command.action(*this, dt);
	}
	//Send the command on to the children
	for (Ptr& child : mChildren)
	{
		child->onCommand(command, dt);
	}
}

void SceneNode::updateCurrent(sf::Time dt)
{
	//Do nothing by default
}

void SceneNode::updateChildren(sf::Time dt)
{
	for (const Ptr& child : mChildren)
	{
		child->update(dt);
	}
}

void SceneNode::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	//Apply the transform to the current node
	states.transform *= getTransform();
	//Draw node and the children
	drawCurrent(target, states);
	drawChildren(target, states);
}

void SceneNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	//Do nothing by default
}

void SceneNode::drawChildren(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (const Ptr& child : mChildren)
	{
		child->draw(target, states);
	}
}
