#include <windows.h>

#define FILE_MENU_EXIT 1
#define AUTHOR_LOGIN_BUTTON 2
#define AUTHOR_REGISTER_BUTTON 3
#define LOGIN_BUTTON 4
#define REGISTER_BUTTON 5

HINSTANCE InstanceHandler;
HWND hEmail, hPassword;

class CreateNewMenu {
    private:
        HMENU hMenu;
        HMENU FilePopup;
    public:
        CreateNewMenu(HWND hWnd){
            hMenu = CreateMenu();
            FilePopup = CreateMenu();

            AppendMenu(FilePopup, MF_STRING, NULL, "Search");
            AppendMenu(FilePopup, MF_STRING, FILE_MENU_EXIT, "Exit");
            
            AppendMenu(hMenu, MF_POPUP, (UINT_PTR)FilePopup, "File");
            AppendMenu(hMenu, MF_STRING, NULL, "Help");
            SetMenu(hWnd, hMenu);
        }
};

class LoginControls {
    public:
        LoginControls(HWND hWnd){
            CreateWindowW(L"Static", L"Email: ", WS_VISIBLE | WS_CHILD, 100, 100, 98, 38, hWnd, NULL, NULL, NULL);
            hEmail = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, 200, 100, 98, 38, hWnd, NULL, NULL, NULL);

            CreateWindowW(L"Static", L"Password: ", WS_VISIBLE | WS_CHILD, 100, 140, 98, 38, hWnd, NULL, NULL, NULL);
            hPassword = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, 200, 140, 98, 38, hWnd, NULL, NULL, NULL);

            CreateWindowW(L"Button", L"Login", WS_VISIBLE | WS_CHILD, 200, 200, 98, 38, hWnd, (HMENU)LOGIN_BUTTON, NULL, NULL);
        }
};

class RegisterControls {
    public:
        RegisterControls(HWND hWnd){
            CreateWindowW(L"Static", L"Email: ", WS_VISIBLE | WS_CHILD, 100, 100, 98, 38, hWnd, NULL, NULL, NULL);
            hEmail = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, 200, 100, 98, 38, hWnd, NULL, NULL, NULL);

            CreateWindowW(L"Static", L"Password: ", WS_VISIBLE | WS_CHILD, 100, 140, 98, 38, hWnd, NULL, NULL, NULL);
            hPassword = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, 200, 140, 98, 38, hWnd, NULL, NULL, NULL);

            CreateWindowW(L"Button", L"Register", WS_VISIBLE | WS_CHILD, 200, 200, 98, 38, hWnd, (HMENU)REGISTER_BUTTON, NULL, NULL);
        }
};

class AuthoriseControls {
    public:
        AuthoriseControls(HWND hWnd){
            CreateWindowW(L"Button", L"Login", WS_VISIBLE | WS_CHILD, 200, 100, 100, 38, hWnd, (HMENU)AUTHOR_LOGIN_BUTTON, NULL, NULL);
            CreateWindowW(L"Button", L"Register", WS_VISIBLE | WS_CHILD, 200, 200, 100, 38, hWnd, (HMENU)AUTHOR_REGISTER_BUTTON, NULL, NULL);
        }
};

class MainControls {
    public:
        MainControls(HWND hWnd){
            CreateWindowW(L"Button", L"Search by name: ", WS_VISIBLE | WS_CHILD, 150, 100, 200, 38, hWnd, (HMENU)AUTHOR_LOGIN_BUTTON, NULL, NULL);
            CreateWindowW(L"Button", L"Search by author: ", WS_VISIBLE | WS_CHILD, 150, 200, 200, 38, hWnd, (HMENU)AUTHOR_REGISTER_BUTTON, NULL, NULL);
            CreateWindowW(L"Button", L"Search by genre: ", WS_VISIBLE | WS_CHILD, 150, 300, 200, 38, hWnd, (HMENU)AUTHOR_REGISTER_BUTTON, NULL, NULL);
        }
};

class MainWindow {
    private:
        WNDCLASSW wc = {0};
    public:
        static LRESULT CALLBACK MainWindowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp){
            switch(msg){
                case WM_COMMAND:
                    switch(wp){
                        case FILE_MENU_EXIT:
                            DestroyWindow(hWnd);
                        break;
                    }
                break;
                case WM_CREATE:
                {
                    CreateNewMenu newMenu(hWnd);
                    MainControls newControls(hWnd);
                    break;
                }
                case WM_DESTROY:
                    PostQuitMessage(0);
                break;
                default:
                    DefWindowProcW(hWnd, msg, wp, lp);
            }
        }
        MainWindow(){
            // Define class for our window
            WNDCLASSW wc = {0};
            wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
            wc.hCursor = LoadCursor(NULL, IDC_ARROW);
            wc.hInstance = InstanceHandler;
            wc.lpszClassName = L"MainWindowClass";
            wc.lpfnWndProc = MainWindowProcedure;
            RegisterClassW(&wc);

            CreateWindowW(L"MainWindowClass", L"Library management", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 500, 500,
                 NULL, NULL, NULL, NULL);
        }
};

class LoginWindow {
    private:
        WNDCLASSW wc = {0};
    public:
        static LRESULT CALLBACK LoginWindowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp){
            switch(msg){
                case WM_COMMAND:
                    switch(wp){
                        case FILE_MENU_EXIT:
                            DestroyWindow(hWnd);
                        break;
                        case LOGIN_BUTTON:
                        {
                            char email[100], password[100];
                            GetWindowText(hEmail, email, 100);
                            GetWindowText(hPassword, password, 100);

                            // check if user exists here....

                            MessageBoxW(hWnd, L"You are successfully logged in!", L"Logging in...", MB_OK);
                            ShowWindow(hWnd, SW_HIDE);
                            MainWindow mainWindow;
                            break;
                        }
                    }
                break;
                case WM_CREATE:
                {
                    CreateNewMenu newMenu(hWnd);
                    LoginControls newControls(hWnd);
                    break;
                }
                case WM_DESTROY:
                    PostQuitMessage(0);
                break;
                default:
                    DefWindowProcW(hWnd, msg, wp, lp);
            }
        }
        LoginWindow(){
            // Define class for our window
            WNDCLASSW wc = {0};
            wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
            wc.hCursor = LoadCursor(NULL, IDC_ARROW);
            wc.hInstance = InstanceHandler;
            wc.lpszClassName = L"LoginWindowClass";
            wc.lpfnWndProc = LoginWindowProcedure;
            RegisterClassW(&wc);

            CreateWindowW(L"LoginWindowClass", L"Library management", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 500, 500,
                 NULL, NULL, NULL, NULL);
        }
};

class RegisterWindow {
    private:
        WNDCLASSW wc = {0};
    public:
        static LRESULT CALLBACK RegisterWindowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp){
            switch(msg){
                case WM_COMMAND:
                    switch(wp){
                        case FILE_MENU_EXIT:
                            DestroyWindow(hWnd);
                        break;
                        case REGISTER_BUTTON:
                        {
                            char email[100], password[100];
                            GetWindowText(hEmail, email, 100);
                            GetWindowText(hPassword, password, 100);

                            // add user to database, check if it exists here...

                            MessageBoxW(hWnd, L"You are successfully registered!", L"Registering...", MB_OK);
                            ShowWindow(hWnd, SW_HIDE);
                            MainWindow mainWindow;
                            break;
                        }
                    }
                break;
                case WM_CREATE:
                {
                    CreateNewMenu newMenu(hWnd);
                    RegisterControls newControls(hWnd);
                    break;
                }
                case WM_DESTROY:
                    PostQuitMessage(0);
                break;
                default:
                    DefWindowProcW(hWnd, msg, wp, lp);
            }
        }
        RegisterWindow(){
            // Define class for our window
            WNDCLASSW wc = {0};
            wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
            wc.hCursor = LoadCursor(NULL, IDC_ARROW);
            wc.hInstance = InstanceHandler;
            wc.lpszClassName = L"RegisterWindowClass";
            wc.lpfnWndProc = RegisterWindowProcedure;
            RegisterClassW(&wc);

            CreateWindowW(L"RegisterWindowClass", L"Library management", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 500, 500,
                 NULL, NULL, NULL, NULL);
        }
};

class AuthoriseWindow {
    private:
        WNDCLASSW wc = {0};
    public:
        static LRESULT CALLBACK AuthoriseWindowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp){
            switch(msg){
                case WM_COMMAND:
                    switch(wp){
                        case FILE_MENU_EXIT:
                            DestroyWindow(hWnd);
                        break;

                        case AUTHOR_LOGIN_BUTTON:
                        {
                           ShowWindow(hWnd, SW_HIDE);
                           LoginWindow lWindow;
                            
                           break;
                        }
                        case AUTHOR_REGISTER_BUTTON:
                        {
                           ShowWindow(hWnd, SW_HIDE);
                           RegisterWindow rWindow;
                            
                           break;
                        }
                    }
                break;
                case WM_CREATE:
                {
                    CreateNewMenu newMenu(hWnd);
                    AuthoriseControls newControls(hWnd);
                    break;
                }
                case WM_DESTROY:
                    PostQuitMessage(0);
                break;
                default:
                    DefWindowProcW(hWnd, msg, wp, lp);
            }
        }
        AuthoriseWindow(){
            // Define class for our window
            WNDCLASSW wc = {0};
            wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
            wc.hCursor = LoadCursor(NULL, IDC_ARROW);
            wc.hInstance = InstanceHandler;
            wc.lpszClassName = L"AuthorizeWindowClass";
            wc.lpfnWndProc = AuthoriseWindowProcedure;
            RegisterClassW(&wc);

            CreateWindowW(L"AuthorizeWindowClass", L"Library management", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 500, 500,
                 NULL, NULL, NULL, NULL);
        }
};



// our main function, everything should run from here....
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow){

    InstanceHandler = hInst;
    AuthoriseWindow FirstWindow;

    MSG msg = {0};
    // message handler
    while(GetMessage(&msg, NULL, NULL, NULL)){
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}