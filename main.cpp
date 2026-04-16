#include <windows.h>
#include <format>
#include <codecvt>
#include <filesystem>
#include "toml++/toml.hpp"
#include "nya_commonhooklib.h"

#include "nya_commonmath.h"

#include "ac.h"

void OnPluginUpdate(double dT);
#include "util.h"

void OnPluginUpdate(double dT) {
	auto filename = std::format("plugins/CameraEditor/{}.toml", GetStringNarrow(pMyPlugin->carAvatar->unixName.c_str()));

	static double fTimer = 0;
	fTimer += dT;
	if (fTimer >= 0.5) {
		if (std::filesystem::exists(filename)) {
			try {
				auto config = toml::parse_file(filename);
			}
			catch (const toml::parse_error& err) {
				MessageBoxA(nullptr, std::format("Failed to parse {}: {}", filename, err.what()).c_str(), "nya?!~", MB_ICONERROR);
				return;
			}

			auto file = toml::parse_file(filename);

			auto car = pMyPlugin->carAvatar;
			auto cam = &pMyPlugin->sim->cameraManager->cameraDrivable->drivableCameraPositions[pMyPlugin->sim->focusedCarIndex];
			cam->bonnetCameraPitch /= 0.01745329;
			cam->bumperCameraPitch /= 0.01745329;
			cam->bonnetCameraPitch = file["GRAPHICS"]["BONNET_CAMERA_PITCH"].value_or(cam->bonnetCameraPitch);
			cam->bumperCameraPitch = file["GRAPHICS"]["BUMPER_CAMERA_PITCH"].value_or(cam->bumperCameraPitch);
			cam->bonnetCameraPitch *= 0.01745329;
			cam->bumperCameraPitch *= 0.01745329;

			cam->bonnetCameraPos.x = file["GRAPHICS"]["BONNET_CAMERA_POS"][0].value_or(cam->bonnetCameraPos.x);
			cam->bonnetCameraPos.y = file["GRAPHICS"]["BONNET_CAMERA_POS"][1].value_or(cam->bonnetCameraPos.y);
			cam->bonnetCameraPos.z = file["GRAPHICS"]["BONNET_CAMERA_POS"][2].value_or(cam->bonnetCameraPos.z);
			cam->bumperCameraPos.x = file["GRAPHICS"]["BUMPER_CAMERA_POS"][0].value_or(cam->bumperCameraPos.x);
			cam->bumperCameraPos.y = file["GRAPHICS"]["BUMPER_CAMERA_POS"][1].value_or(cam->bumperCameraPos.y);
			cam->bumperCameraPos.z = file["GRAPHICS"]["BUMPER_CAMERA_POS"][2].value_or(cam->bumperCameraPos.z);
			car->driverEyesPosition.x = file["GRAPHICS"]["DRIVEREYES"][0].value_or(car->driverEyesPosition.x);
			car->driverEyesPosition.y = file["GRAPHICS"]["DRIVEREYES"][1].value_or(car->driverEyesPosition.y);
			car->driverEyesPosition.z = file["GRAPHICS"]["DRIVEREYES"][2].value_or(car->driverEyesPosition.z);
			cam->dashCameraPos.x = file["DASH_CAM"]["POS"][0].value_or(cam->dashCameraPos.x);
			cam->dashCameraPos.y = file["DASH_CAM"]["POS"][1].value_or(cam->dashCameraPos.y);
			cam->dashCameraPos.z = file["DASH_CAM"]["POS"][2].value_or(cam->dashCameraPos.z);
		}
		fTimer -= 0.5;
	}
}

BOOL WINAPI DllMain(HINSTANCE, DWORD fdwReason, LPVOID) {
	switch(fdwReason) {
		case DLL_PROCESS_ATTACH: {
			if (NyaHookLib::GetEntryPoint() != 0x15AE310) {
				MessageBoxA(nullptr, "Unsupported game version! Make sure you're using the latest x64 Steam release (.exe size of 22890776 bytes)", "nya?!~", MB_ICONERROR);
				return TRUE;
			}
		} break;
		default:
			break;
	}
	return TRUE;
}