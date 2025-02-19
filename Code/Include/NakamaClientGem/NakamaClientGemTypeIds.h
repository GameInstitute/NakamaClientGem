
#pragma once

namespace NakamaClientGem
{
    // System Component TypeIds
    inline constexpr const char* NakamaClientGemSystemComponentTypeId = "{1C629636-AFAC-4747-93A6-2818789989A2}";
    inline constexpr const char* NakamaClientGemEditorSystemComponentTypeId = "{AA45F5D6-739E-417B-AD0B-E62465FC8842}";

    // Module derived classes TypeIds
    inline constexpr const char* NakamaClientGemModuleInterfaceTypeId = "{9E6249F4-F38C-49BE-8236-CA03DB253932}";
    inline constexpr const char* NakamaClientGemModuleTypeId = "{C64F50D1-23ED-4600-89A5-90D6BDD8D95B}";
    // The Editor Module by default is mutually exclusive with the Client Module
    // so they use the Same TypeId
    inline constexpr const char* NakamaClientGemEditorModuleTypeId = NakamaClientGemModuleTypeId;

    // Interface TypeIds
    inline constexpr const char* NakamaClientGemRequestsTypeId = "{5663757C-19CA-42CE-A48B-4AA7462F3DCE}";
} // namespace NakamaClientGem
