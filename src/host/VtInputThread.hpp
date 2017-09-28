/*++
Copyright (c) Microsoft Corporation

Module Name:
- VtInputThread.hpp

Abstract:
- Defines methods that wrap the thread that reads VT input from a pipe and
  feeds it into the console's input buffer.

Author(s):
- Mike Griese (migrie) 15 Aug 2017
--*/
#pragma once

#include "..\terminal\parser\StateMachine.hpp"

namespace Microsoft
{
    namespace Console
    {
        class VtInputThread
        {
        public:
            VtInputThread(_In_ HANDLE hPipe);
            ~VtInputThread();

            HRESULT Start();
            static DWORD StaticVtInputThreadProc(_In_ LPVOID lpParameter);

        private:
            HRESULT _HandleRunInput(_In_reads_(cch) const char* const charBuffer, _In_ const int cch);
            DWORD _InputThread();

            wil::unique_hfile _hFile;
            wil::unique_handle _hThread;
            DWORD _dwThreadId;

            StateMachine* _pInputStateMachine;
        };
    }
};