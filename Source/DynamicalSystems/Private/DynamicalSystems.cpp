#include "DynamicalSystems.h"

#include "Core.h"
#include "IPluginManager.h"
#include "RustyDynamics.h"

#include "WindowsHWrapper.h"
#include <windows.h>

#define LOCTEXT_NAMESPACE "FDynamicalSystemsModule"

extern "C" void ffi_log(const char* log)
{
	UE_LOG(LogTemp, Warning, TEXT("[Rust] %s"), UTF8_TO_TCHAR(log));
}

void FDynamicalSystemsModule::StartupModule()
{
	auto VenicePlugin = IPluginManager::Get().FindPlugin("Venice");
	if (VenicePlugin.IsValid()) {
		FString VeniceBaseDir = VenicePlugin->GetBaseDir();
		const int BufferSize =
			65535;  // Limit according to
					// http://msdn.microsoft.com/en-us/library/ms683188.aspx
		TCHAR OldPath[BufferSize];
		GetEnvironmentVariableW(L"PATH", OldPath, BufferSize);
		FPlatformProcess::AddDllDirectory(
			*FPaths::Combine(*VeniceBaseDir, TEXT("gstreamer/1.0/x86_64/bin")));
		SetEnvironmentVariable(
			L"GST_PLUGIN_PATH",
			*FPaths::Combine(*VeniceBaseDir, TEXT("gstreamer/1.0/x86_64/lib")));
		
		TArray<FString> Paths;
		Paths.Add(FString(OldPath));
		Paths.Add(FPaths::Combine(*VeniceBaseDir, TEXT("gstreamer/1.0/x86_64/bin")));
		FString Path = FString::Join(Paths, TEXT(";"));
		SetEnvironmentVariable(L"PATH", *Path);
	}

	// Get the base directory of this plugin
	FString BaseDir = IPluginManager::Get().FindPlugin("DynamicalSystems")->GetBaseDir();

	// Add on the relative location of the third party dll and load it
	FString LibraryPath;
#if PLATFORM_WINDOWS
	LibraryPath = FPaths::Combine(*BaseDir, TEXT("Source/ThirdParty/RustyDynamics/target/Debug/RustyDynamics.dll"));
#elif PLATFORM_MAC
    LibraryPath = FPaths::Combine(*BaseDir, TEXT("Source/ThirdParty/RustyDynamics/target/Debug/libRustyDynamics.dylib"));
#endif // PLATFORM_WINDOWS

	RustyDynamicsHandle = !LibraryPath.IsEmpty() ? FPlatformProcess::GetDllHandle(*LibraryPath) : nullptr;

	if (RustyDynamicsHandle)
	{
		rb_log_fn(ffi_log);
	}
	else
	{
		//FMessageDialog::Open(EAppMsgType::Ok, LOCTEXT("ThirdPartyLibraryError", "Failed to load example third party library"));
	}
}

void FDynamicalSystemsModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	// Free the dll handle
	FPlatformProcess::FreeDllHandle(RustyDynamicsHandle);
	RustyDynamicsHandle = nullptr;
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FDynamicalSystemsModule, DynamicalSystems)
