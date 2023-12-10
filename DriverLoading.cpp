#include <windows.h>
#include <iostream>
#include <atlstr.h>

void DriverLoading(LPCWSTR lpDriverPath, LPCWSTR lpServiceName)
{
	SC_HANDLE hSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	if (!hSCManager)
	{
		std::cout << "[DriverLoading] OpenManager Fail, LastError: " << GetLastError() << std::endl;
		return;
	}

	SC_HANDLE hSCService = CreateService(
		hSCManager,
		lpServiceName,
		lpServiceName,
		SERVICE_ALL_ACCESS,
		SERVICE_KERNEL_DRIVER,
		SERVICE_DEMAND_START,
		SERVICE_ERROR_IGNORE,
		lpDriverPath,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL);
	if (!hSCService)
	{
		std::cout << "[DriverLoading] CreateService Fail, LastError: " << GetLastError() << std::endl;
		CloseServiceHandle(hSCManager);
		return;
	}

	CloseServiceHandle(hSCManager);
	CloseServiceHandle(hSCService);
	std::cout << "[DriverLoading] Successful" << std::endl;
}

void DriverActivate(LPCWSTR lpServiceName)
{
	SC_HANDLE hSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	if (!hSCManager)
	{
		std::cout << "[DriverActivate] OpenManager Fail, LastError: "<< GetLastError() << std::endl;
		return;
	}

	SC_HANDLE hSCService = OpenService(hSCManager, lpServiceName, SERVICE_START);
	if (!hSCManager)
	{
		CloseServiceHandle(hSCManager);
		std::cout << "[DriverActivate] OpenService Fail, LastError: " << GetLastError() << std::endl;
		return;
	}

	if (!StartService(hSCService, NULL, NULL))
	{
		CloseServiceHandle(hSCManager);
		CloseServiceHandle(hSCService);
		std::cout << "[DriverActivate] StartService Fail, LastError: " << GetLastError() << std::endl;
		return;
	}

	CloseServiceHandle(hSCManager);
	CloseServiceHandle(hSCService);
	std::cout << "[DriverActivate] Successful" << std::endl;
}

void DriverClose(LPCWSTR lpServiceName)
{
	SC_HANDLE hSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	if (!hSCManager)
	{
		std::cout << "[DriverClose] OpenManager Fail, LastError: " << GetLastError() << std::endl;
		return;
	}

	SC_HANDLE hSCService = OpenService(hSCManager, lpServiceName, SERVICE_STOP);
	if (!hSCManager)
	{
		CloseServiceHandle(hSCManager);
		std::cout << "[DriverClose] OpenService Fail, LastError: " << GetLastError() << std::endl;
		return;
	}

	SERVICE_STATUS lpServiceStatus = { 0 };
	if (!ControlService(hSCService, SERVICE_CONTROL_STOP, &lpServiceStatus))
	{
		CloseServiceHandle(hSCManager);
		CloseServiceHandle(hSCService);
		std::cout << "[DriverClose] ControlService Fail, LastError: " << GetLastError() << std::endl;
		return;
	}

	CloseServiceHandle(hSCManager);
	CloseServiceHandle(hSCService);
	std::cout << "[DriverClose] Successful" << std::endl;
}

void DriverUnload(LPCWSTR lpServiceName)
{
	SC_HANDLE hSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	if (!hSCManager)
	{
		std::cout << "[DriverUnload] OpenManager Fail, LastError: " << GetLastError() << std::endl;
		return;
	}

	SC_HANDLE hSCService = OpenService(hSCManager, lpServiceName, SERVICE_STOP | DELETE);
	if (!hSCManager)
	{
		CloseServiceHandle(hSCManager);
		std::cout << "[DriverUnload] OpenService Fail, LastError: " << GetLastError() << std::endl;
		return;
	}
	if (!DeleteService(hSCService))
	{
		CloseServiceHandle(hSCManager);
		CloseServiceHandle(hSCService);
		std::cout << "[DriverClose] DeleteService Fail, LastError: " << GetLastError() << std::endl;
		return;
	}

	CloseServiceHandle(hSCManager);
	CloseServiceHandle(hSCService);
	std::cout << "[DriverUnload] Successful" << std::endl;
}

int main(int argc, char* argv[])
{
	WCHAR argv2[MAX_PATH];
	memset(argv2, 0, sizeof(argv2));
	MultiByteToWideChar(CP_ACP, 0, argv[2], strlen(argv[2]) + 1, argv2, sizeof(argv2) / sizeof(argv2[0]));

	switch (atoi(argv[1]))
	{
	case 1:
		WCHAR argv3[50];
		memset(argv3, 0, sizeof(argv3));
		MultiByteToWideChar(CP_ACP, 0, argv[3], strlen(argv[3]) + 1, argv3, sizeof(argv3) / sizeof(argv3[0]));
		DriverLoading(argv2, argv3);
		break;
	case 2:
		DriverActivate(argv2);
		break;
	case 3:
		DriverClose(argv2);
		break;
	case 4:
		DriverUnload(argv2);
		break;
	default:
		break;
	}

	return 0;
}