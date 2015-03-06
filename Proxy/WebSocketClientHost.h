//
// Copyright (C) Microsoft. All rights reserved.
//

#pragma once

#include "Proxy_h.h"
#include "ScriptEngineHost.h"

class WebSocketClientHost :
    public ScriptEngineHost
{
public:
    WebSocketClientHost();

    BEGIN_MSG_MAP(WebSocketClientHost)
        MESSAGE_HANDLER(WM_SET_MESSAGE_HWND, OnSetMessageHwnd)
        MESSAGE_HANDLER(Get_WM_SET_CONNECTION_HWND(), OnSetConnectionHwnd)
        MESSAGE_HANDLER(WM_MESSAGE_SEND, OnMessageSend)
        MESSAGE_HANDLER(WM_COPYDATA, OnCopyData)
        MESSAGE_HANDLER(WM_PROCESSCOPYDATA, OnMessageFromWebKit)
        CHAIN_MSG_MAP(ScriptEngineHost)
    END_MSG_MAP()

    // Window Messages
    LRESULT OnSetMessageHwnd(UINT nMsg, WPARAM wParam, LPARAM lParam, _Inout_ BOOL& /*bHandled*/);
    LRESULT OnSetConnectionHwnd(UINT nMsg, WPARAM wParam, LPARAM lParam, _Inout_ BOOL& /*bHandled*/);
    LRESULT OnMessageSend(UINT nMsg, WPARAM wParam, LPARAM lParam, _Inout_ BOOL& /*bHandled*/);
    LRESULT OnCopyData(UINT nMsg, WPARAM wParam, LPARAM lParam, _Inout_ BOOL& /*bHandled*/);
    LRESULT OnMessageFromWebKit(UINT nMsg, WPARAM wParam, LPARAM lParam, _Inout_ BOOL& /*bHandled*/);

    HRESULT Initialize(_In_ HWND mainHwnd);

private:
    // JavaScript Functions
    JsValueRef postMessageToEngine(JsValueRef callee, bool isConstructCall, JsValueRef* arguments, unsigned short argumentCount);

    // Helper functions
    HRESULT SendMessageToWebKit(_In_ CString& message);

private:
    HWND m_uiThreadHwnd;
    HWND m_serverHwnd;

    map<CString, HWND> m_engineHosts;
    map<CString, vector<CComBSTR>> m_engineMessageQueue;
};

