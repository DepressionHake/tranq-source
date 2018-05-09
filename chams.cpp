#include "Chams.h"
#include "offsets.h"
#include "SDK.h"
#include "Interfaces.h"

void InitKeyValues(KeyValues* kv_, std::string name_)
{
	static auto address = Utilities::Memory::FindPattern1("client.dll", "55 8B EC 51 33 C0 C7 45");
	using Fn = void(__thiscall*)(void* thisptr, const char* name);
	reinterpret_cast< Fn >(address)(kv_, name_.c_str());
}

void LoadFromBuffer(KeyValues* vk_, std::string name_, std::string buffer_)
{
	static auto address = Utilities::Memory::FindPattern1("client.dll", "55 8B EC 83 E4 F8 83 EC 34 53 8B 5D 0C 89 4C 24 04");
	using Fn = void(__thiscall*)(
		void* thisptr, const char* resourceName,
		const char* pBuffer, void* pFileSystem,
		const char* pPathID, void* pfnEvaluateSymbolProc);

	reinterpret_cast< Fn >(address)(
		vk_, name_.c_str(), buffer_.c_str(), nullptr, nullptr, nullptr);
}

IMaterial *CreateMaterial(bool ignorez, bool lit, bool wireframe) //credits to ph0ne
{
	static auto created = 0;

	std::string type = lit ? "VertexLitGeneric" : "UnlitGeneric";

	auto matdata =
		"\"" + type + "\"\
		\n{\
		\n\t\"$basetexture\" \"vgui/white_additive\"\
		\n\t\"$envmap\" \"\"\
		\n\t\"$model\" \"1\"\
		\n\t\"$flat\" \"1\"\
		\n\t\"$nocull\" \"0\"\
		\n\t\"$selfillum\" \"1\"\
		\n\t\"$halflambert\" \"1\"\
		\n\t\"$nofog\" \"0\"\
		\n\t\"$ignorez\" \"" + std::to_string(ignorez) + "\"\
		\n\t\"$znearer\" \"0\"\
		\n\t\"$wireframe\" \"" + std::to_string(wireframe) + "\"\
        \n}\n";

	auto matname = "custom_" + std::to_string(created);
	++created;

	auto keyValues = static_cast< KeyValues* >(malloc(sizeof(KeyValues)));

	InitKeyValues(keyValues, type.c_str());
	LoadFromBuffer(keyValues, matname, matdata);

	auto material =
		interfaces::MaterialSystem->CreateMaterial(matname.c_str(), keyValues);

	material->IncrementReferenceCount();
	return material;
}

void ForceMaterial(Color color, IMaterial* material, bool useColor, bool forceMaterial)
{
	if (useColor)
	{
		float temp[3] =
		{
			color.r(),
			color.g(),
			color.b()
		};

		temp[0] /= 255.f;
		temp[1] /= 255.f;
		temp[2] /= 255.f;


		float alpha = color.a();

		interfaces::RenderView->SetBlend(1.0f);
		interfaces::RenderView->SetColorModulation(temp);
	}

	if (forceMaterial)
		interfaces::ModelRender->ForcedMaterialOverride(material);
	else
		interfaces::ModelRender->ForcedMaterialOverride(NULL);

}

