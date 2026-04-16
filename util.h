void WriteLog(const std::string& str) {
	static auto file = std::ofstream("plugins/AssettoCorsaCameraEditor_gcp.log");

	file << str;
	file << "\n";
	file.flush();
}

auto GetStringWide(const std::string& string) {
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	return converter.from_bytes(string);
}

auto GetStringNarrow(const std::wstring& string) {
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	return converter.to_bytes(string);
}

extern "C" __declspec(dllexport) bool __fastcall acpGetName(wchar_t* out) { wcscpy_s(out, 256, L"AssettoCorsaCameraEditor"); return true; }
extern "C" __declspec(dllexport) bool __fastcall acpShutdown() { return true; }
extern "C" __declspec(dllexport) bool __fastcall acpOnGui(void*) { return false; }
extern "C" __declspec(dllexport) bool __fastcall acpGetControls(void*) { return false; }
extern "C" __declspec(dllexport) bool __fastcall acpUpdate(void*, float dT) { OnPluginUpdate(dT); return true; }

ACPlugin* pMyPlugin = nullptr;
extern "C" __declspec(dllexport) bool __fastcall acpInit(ACPlugin* plugin) {
	pMyPlugin = plugin;
	WriteLog("Mod initialized");
	return true;
}