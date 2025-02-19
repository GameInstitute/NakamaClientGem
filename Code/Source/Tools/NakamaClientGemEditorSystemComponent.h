
#pragma once

#include <AzToolsFramework/API/ToolsApplicationAPI.h>

#include <Clients/NakamaClientGemSystemComponent.h>

namespace NakamaClientGem
{
    /// System component for NakamaClientGem editor
    class NakamaClientGemEditorSystemComponent
        : public NakamaClientGemSystemComponent
        , protected AzToolsFramework::EditorEvents::Bus::Handler
    {
        using BaseSystemComponent = NakamaClientGemSystemComponent;
    public:
        AZ_COMPONENT_DECL(NakamaClientGemEditorSystemComponent);

        static void Reflect(AZ::ReflectContext* context);

        NakamaClientGemEditorSystemComponent();
        ~NakamaClientGemEditorSystemComponent();

    private:
        static void GetProvidedServices(AZ::ComponentDescriptor::DependencyArrayType& provided);
        static void GetIncompatibleServices(AZ::ComponentDescriptor::DependencyArrayType& incompatible);
        static void GetRequiredServices(AZ::ComponentDescriptor::DependencyArrayType& required);
        static void GetDependentServices(AZ::ComponentDescriptor::DependencyArrayType& dependent);

        // AZ::Component
        void Activate() override;
        void Deactivate() override;
    };
} // namespace NakamaClientGem
