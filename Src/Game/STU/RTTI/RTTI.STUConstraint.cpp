// Hazno - 2026

module Atlas.Game.STU.RTTI;

namespace Atlas::STU
{
	const char* STUConstraintTypeToString(const STUConstraintType type)
	{
		switch (type) {
			case STU_ConstraintType_Primitive:
				return "Primitive";
			case STU_ConstraintType_BsList_Primitive:
				return "List: Primitive";
			case STU_ConstraintType_Object:
				return "Object";
			case STU_ConstraintType_BsList_Object:
				return "List: Object";
			case STU_ConstraintType_InlinedObject:
				return "InlinedObject";
			case STU_ConstraintType_BsList_InlinedObject:
				return "List: InlinedObject";
			case STU_ConstraintType_Map:
				return "Map";
			case STU_ConstraintType_Enum:
				return "Enum";
			case STU_ConstraintType_BsList_Enum:
				return "List: Enum";
			case STU_ConstraintType_NonSTUResourceRef:
				return "NonSTUResourceRef";
			case STU_ConstraintType_BsList_NonSTUResourceRef:
				return "List: NonSTUResourceRef";
			case STU_ConstraintType_ResourceRef:
				return "ResourceRef";
			case STU_ConstraintType_BsList_ResourceRef:
				return "List: ResourceRef";
			default:
				return ("Unknown: " + std::to_string(type)).c_str();
		}
	}

	int64 STUConstraint::ExGetSTUType()
	{
		return this->GetSTUHashWithTypeFlag() & 0xFFFFFFFF;
	}

	STUConstraintType STUConstraint::ExToConstraintType()
	{
		return static_cast<STUConstraintType>(this->GetSTUHashWithTypeFlag() >> 32 & 0xFFFFFFFF);
	}

	bool STUConstraint::ExIsPrimitive()
	{
		const auto type = ExToConstraintType();
		//return type == STU_ConstraintType_Primitive && Statics::Primitive::all.contains(type);
		return false;
	}

	bool STUConstraint::ExIsList()
	{
		const auto type = ExToConstraintType();
		return
				type == STU_ConstraintType_BsList_Primitive ||
				type == STU_ConstraintType_BsList_Object ||
				type == STU_ConstraintType_BsList_InlinedObject ||
				type == STU_ConstraintType_BsList_Enum ||
				type == STU_ConstraintType_BsList_ResourceRef ||
				type == STU_ConstraintType_BsList_NonSTUResourceRef;
	}
}
