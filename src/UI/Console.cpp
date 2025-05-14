#include "Console.h"
#include <cstdarg>
#include <cstdio>

void Console::Clear()
{
    Items.clear();
}

void Console::AddLog(const char *fmt, ...)
{
    char buf[1024];
    va_list args;
    va_start(args, fmt);
    vsnprintf(buf, sizeof(buf), fmt, args);
    va_end(args);
    Items.emplace_back(buf);
    ScrollToBottom = true;
}

void Console::ExecCommand(const char *command)
{
    AddLog("# %s", command);
    History.push_back(command);
    HistoryPos = -1;

    // Aquí puedes agregar comandos personalizados
    if (strcmp(command, "clear") == 0)
        Clear();
    else if (strcmp(command, "help") == 0)
        AddLog("Comandos: clear, help");
    else
        AddLog("Comando desconocido: '%s'", command);
}

void Console::AutoScrollToBottom()
{
    if (ScrollToBottom)
        ImGui::SetScrollHereY(1.0f);
    ScrollToBottom = false;
}

void Console::Draw(const char *title, bool *p_open)
{
    if (!ImGui::Begin(title, p_open))
    {
        ImGui::End();
        return;
    }

    if (ImGui::Button("Clear"))
        Clear();
    ImGui::SameLine();
    if (ImGui::Button("Help"))
        ExecCommand("help");

    ImGui::Separator();

    ImGui::BeginChild("ScrollRegion", ImVec2(0, -ImGui::GetFrameHeightWithSpacing()), false,
                      ImGuiWindowFlags_HorizontalScrollbar);

    for (const auto &item : Items)
        ImGui::TextUnformatted(item.c_str());

    AutoScrollToBottom();

    ImGui::EndChild();
    ImGui::Separator();

    // Input text
    if (ImGui::InputText("Input", InputBuf, IM_ARRAYSIZE(InputBuf), ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_CallbackHistory, [](ImGuiInputTextCallbackData *data) -> int
                         {
                             auto* console = (Console*)data->UserData;
                             if (data->EventFlag == ImGuiInputTextFlags_CallbackHistory)
                             {
                                 if (data->EventKey == ImGuiKey_UpArrow)
                                 {
                                     if (console->HistoryPos == -1 && !console->History.empty())
                                         console->HistoryPos = (int)console->History.size() - 1;
                                     else if (console->HistoryPos > 0)
                                         console->HistoryPos--;

                                     data->DeleteChars(0, data->BufTextLen);
                                     data->InsertChars(0, console->History[console->HistoryPos].c_str());
                                 }
                                 else if (data->EventKey == ImGuiKey_DownArrow)
                                 {
                                     if (console->HistoryPos != -1)
                                         console->HistoryPos++;
                                     if (console->HistoryPos >= (int)console->History.size())
                                         console->HistoryPos = -1;

                                     const char* historyEntry = (console->HistoryPos >= 0)
                                                                     ? console->History[console->HistoryPos].c_str()
                                                                     : "";
                                     data->DeleteChars(0, data->BufTextLen);
                                     data->InsertChars(0, historyEntry);
                                 }
                             }
                             return 0; }, (void *)this))
    {
        ExecCommand(InputBuf);
        strcpy(InputBuf, "");
    }

    ImGui::End();
}
