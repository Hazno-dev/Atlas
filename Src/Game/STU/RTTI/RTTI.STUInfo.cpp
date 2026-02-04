// Hazno - 2026

module Atlas.Game.STU.RTTI;
import Atlas.Process;

namespace Atlas::STU
{
	STUArgumentInfoView STUInfo::RangeArgs(const bool includeParents) const
	{
		return STUArgumentInfoView::Create(this, includeParents);
	}

	STUInfoView STUInfo::RangeSiblings() const
	{
		return STUInfoView::Create<SiblingsTraverse>(this->Sibling);
	}

	STUInfoView STUInfo::RangeChildren() const
	{
		return STUInfoView::Create<SiblingsTraverse>(this->Child);
	}

	STUInfoView STUInfo::RangeDescendants() const
	{
		return STUInfoView::Create<ChildrenTraverse | SiblingsTraverse>(this->Child);
	}

	STUInfoView STUInfo::RangeParents() const
	{
		return STUInfoView::Create<ParentsTraverse>(this->Parent);
	}

	STUInfoView STUInfo::RangeAncestors() const
	{
		return STUInfoView::Create<ParentsTraverse | SiblingsTraverse>(this->Parent);
	}

	bool STUInfo::ExAssignableToHash(const uint64 assign) const
	{
		auto stu = this;
		while (stu) {
			if (stu->Hash == assign) {
				return true;
			}

			stu = stu->Parent;
		}

		return false;
	}

	bool STUInfo::ExAssignableToHashes(const std::initializer_list<uint64> assign) const
	{
		for (const auto hash : assign) {
			if (ExAssignableToHash(hash)) {
				return true;
			}
		}

		return false;
	}

	bool STUInfo::ExAssignableToRTTI(const uint64 assign) const
	{
		auto stu = this;
		while (stu) {
			if (Process::GetProcessModule().RVA(stu->RTTI_Info) == assign) {
				return true;
			}

			stu = stu->Parent;
		}

		return false;
	}

	STUArgumentInfo* STUInfo::ExArgByHash(const uint32 hash, const bool search_parents) const
	{
		for (const auto [info, arg] : this->RangeArgs(search_parents)) {
			if (arg->Hash == hash) {
				return arg;
			}
		}

		return nullptr;
	}
}
