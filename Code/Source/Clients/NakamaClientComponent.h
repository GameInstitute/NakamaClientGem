
#pragma once
#include "NakamaClientGem/NakamaClientComponentBus.h"

#include <AzCore/Component/Component.h>
#include <AzCore/Component/TickBus.h>
#include <AzCore/Math/Vector3.h>
#include <AzCore/Math/Quaternion.h>
#include <AzCore/std/containers/map.h>

namespace NakamaClientGem
{
    class NakamaClientComponent
        : public AZ::Component
        , public AZ::TickBus::Handler
        , public NakamaClientComponentRequestBus::Handler
    {
    public:
        AZ_COMPONENT(NakamaClientComponent, "{8AEB84E1-81C3-484B-8CED-DACFC6E86CE8}");

        NakamaClientComponent();
        ~NakamaClientComponent();

        static void Reflect(AZ::ReflectContext* rc);

        // AZ::Component interface implementation
        void Init() override;
        void Activate() override;
        void Deactivate() override;

        static void GetRequiredServices(AZ::ComponentDescriptor::DependencyArrayType& required);
        static void GetProvidedServices(AZ::ComponentDescriptor::DependencyArrayType& provided);
        static void GetIncompatibleServices(AZ::ComponentDescriptor::DependencyArrayType& incompatible);

        // TickBus interface
        void OnTick(float deltaTime, AZ::ScriptTimePoint) override;

    };
}