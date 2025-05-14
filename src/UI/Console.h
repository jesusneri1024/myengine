#pragma once
#include <vector>
#include <string>
#include <imgui.h>

class Console
{
public:
    void Clear();
    void AddLog(const char *fmt, ...);
    void Draw(const char *title, bool *p_open = nullptr);
    void ExecCommand(const char *command);

private:
    char InputBuf[256];
    std::vector<std::string> Items;
    std::vector<std::string> History;
    int HistoryPos = -1;

    void AutoScrollToBottom();
    bool ScrollToBottom = false;
};
