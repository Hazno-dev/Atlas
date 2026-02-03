// Hazno - 2026

module Atlas.Game.STU.RTTI;
import Atlas.Common;
import std;

namespace Atlas::STU
{
	STURegistryView::Iter& STURegistryView::Iter::operator++()
	{
		if (!m_current) {
			return *this;
		}

		m_current = m_current->Next;
		return *this;
	}

	STURegistryView::Iter STURegistryView::Iter::operator++(int)
	{
		const Iter tmp = *this;
		++*this;
		return tmp;
	}

	bool STURegistryView::Iter::operator==(const Iter& it) const
	{
		return m_current == it.m_current;
	}

	STURegistryView::Iter::value_type STURegistryView::Iter::operator*() const
	{
		if (!m_current) {
			throw std::out_of_range("Dereferencing invalid STURegistry iterator!");
		}

		return std::pair{m_current->Info, m_current};
	}
}
