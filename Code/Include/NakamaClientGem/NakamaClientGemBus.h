
#pragma once

#include <NakamaClientGem/NakamaClientGemTypeIds.h>

#include <AzCore/EBus/EBus.h>
#include <AzCore/Interface/Interface.h>

namespace NakamaClientGem
{
    class NakamaClientGemRequests
    {
    public:
        AZ_RTTI(NakamaClientGemRequests, NakamaClientGemRequestsTypeId);
        virtual ~NakamaClientGemRequests() = default;
        // Put your public methods here
    };

    class NakamaClientGemBusTraits
        : public AZ::EBusTraits
    {
    public:
        //////////////////////////////////////////////////////////////////////////
        // EBusTraits overrides
        static constexpr AZ::EBusHandlerPolicy HandlerPolicy = AZ::EBusHandlerPolicy::Single;
        static constexpr AZ::EBusAddressPolicy AddressPolicy = AZ::EBusAddressPolicy::Single;
        //////////////////////////////////////////////////////////////////////////
    };

    using NakamaClientGemRequestBus = AZ::EBus<NakamaClientGemRequests, NakamaClientGemBusTraits>;
    using NakamaClientGemInterface = AZ::Interface<NakamaClientGemRequests>;

} // namespace NakamaClientGem
