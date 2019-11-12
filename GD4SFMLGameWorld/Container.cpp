#include "Container.hpp"

GUI::Container::Container()
	:mChildren()
	,mSelectedChild(-1)
{
}

void GUI::Container::pack(Component::Ptr component)
{
	mChildren.push_back(component);
	if (!hasSelection() && component->isSelectable())
	{
		select(mChildren.size() - 1);
	}
}

bool GUI::Container::isSelectable() const
{
	return false;
}

void GUI::Container::handleEvent(const sf::Event& event)
{
}

void GUI::Container::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
}

bool GUI::Container::hasSelection() const
{
	return false;
}

void GUI::Container::select(std::size_t index)
{
}

void GUI::Container::selectNext()
{
}

void GUI::Container::selectPrevious()
{
}
