
#pragma once

#include <AzCore/Component/ComponentBus.h>

namespace NakamaClientGem
{
    class NakamaRequests
        : public AZ::ComponentBus
    {
    public:
        AZ_RTTI(NakamaClientGem::NakamaRequests, "{023D49B4-E555-4D02-8AFA-A570E6856427}");

        // Put your public request methods here.
        
        // Put notification events here. Examples:
        // void RegisterEvent(AZ::EventHandler<...> notifyHandler);
        // AZ::Event<...> m_notifyEvent1;
        
    };

    using NakamaRequestBus = AZ::EBus<NakamaRequests>;

} // namespace NakamaClientGem
