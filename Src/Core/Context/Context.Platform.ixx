// Hazno - 2026

export module Atlas.Context:Platform;

import Atlas.Common;
import std;

export namespace Atlas
{
	enum class Platform
	{
		Unknown		= 0,

		BNet		= 1 << 0,
		Steam 		= 1 << 1,
		PC			= BNet | Steam,

		NX			= 1 << 2,
		NX2			= 1 << 3,
		Switch 		= NX | NX2,

		PS4			= 1 << 4,
		PS5			= 1 << 5,
		Playstation = PS4 | PS5,

		XSX 		= 1 << 6,
		XSS			= 1 << 7,
		Xbox		= XSX | XSS,

		IOS			= 1 << 8,
		Android		= 1 << 9,
		Mobile = IOS | Android,
	};
}