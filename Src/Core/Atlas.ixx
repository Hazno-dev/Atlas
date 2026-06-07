// Hazno - 2026

export module Atlas;
import Atlas.Database;

export namespace Atlas
{
	bool IsInitialized();

	void Initialize(const Context& context);
	void Uninitialize();
}

void test()
{
	auto tet = new Atlas::DB::Instance();
	auto res = tet->Get<Atlas::DB::HashDB, Atlas::DB::HashType::STU>("test");
	tet->GetDatabase<Atlas::DB::HashDB>()->template Get<Atlas::DB::HashType::STU>("test");
}
