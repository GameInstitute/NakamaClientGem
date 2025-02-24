
#pragma once

#include <AzCore/Component/Component.h>
#include <AzCore/Component/TickBus.h>

#include <NakamaClientGem/NakamaInterface.h>

#include <nakama-cpp/Nakama.h>
#include <nakama-cpp/realtime/NRtClientInterface.h>
#include <nakama-cpp/realtime/NRtDefaultClientListener.h>
namespace NakamaClientGem
{
    /*
    * TODO: Register this component in your Gem's AZ::Module interface by inserting the following into the list of m_descriptors:
    *       NakamaComponent::CreateDescriptor(),
    */

    class NakamaComponent
        : public AZ::Component
        , public NakamaRequestBus::Handler
        , public AZ::TickBus::Handler
    {
    public:
        AZ_COMPONENT_DECL(NakamaComponent);

        AZ::u16 m_serverPort = 7350;
        AZStd::string m_serverHost = "127.0.0.1";
        AZStd::string m_serverKey = "defaultKey";

        // Nakama Client Ptr
        Nakama::NClientPtr m_Client;
        Nakama::NRtClientPtr m_RtClient;
        Nakama::NSessionPtr m_Session;
        Nakama::NRtDefaultClientListener m_Listener;

        static void ReflectDataTypes(AZ::ReflectContext* context);

        /*
        * Reflects component data into the reflection contexts, including the serialization, edit, and behavior contexts.
        */
        static void Reflect(AZ::ReflectContext* context);

        /*
        * Specifies the services that this component provides.
        * Other components can declare a dependency on these services. The system uses this
        * information to determine the order of component activation.
        */
        static void GetProvidedServices(AZ::ComponentDescriptor::DependencyArrayType& provided);

        /*
        * Specifies the services that this component cannot operate with.
        * For example, if two components provide a similar service and the system cannot use the
        * services simultaneously, each of those components would specify the other component as
        * an incompatible service.
        * If an entity cannot have multiple instances of this component, include this component's
        * provided service in the list of incompatible services.
        */
        static void GetIncompatibleServices(AZ::ComponentDescriptor::DependencyArrayType& incompatible);

        /*
        * Specifies the services that this component requires.
        * The system activates the required services before it activates this component.
        * It also deactivates the required services after it deactivates this component.
        * If a required service is missing before this component is activated, the system
        * returns an error and does not activate this component.
        */
        static void GetRequiredServices(AZ::ComponentDescriptor::DependencyArrayType& required);

        /*
        * Specifies the services that this component depends on, but does not require.
        * The system activates the dependent services before it activates this component.
        * It also deactivates the dependent services after it deactivates this component.
        * If a dependent service is missing before this component is activated, the system
        * does not return an error and still activates this component.
        */
        static void GetDependentServices(AZ::ComponentDescriptor::DependencyArrayType& dependent);

        // AZTickBus interface implementation
        void OnTick(float deltaTime, AZ::ScriptTimePoint time) override;

#pragma region Authentication
        /**
          * Authenticate a user with a device id.
          *
          * @param id A device identifier usually obtained from a platform API.
          * @param username A username used to create the user. Defaults to empty string.
          * @param create True if the user should be created when authenticated. Defaults to false.
          * @param vars Extra information that will be bundled in the session token.
          */
        virtual void AuthenticateDevice(
            const AZStd::string& id,
            const AZStd::string& username,
            bool create = false,
            const AZStringMap& vars = {}
        ) override;

        /**
         * Authenticate a user with an email and password.
         *
         * @param email The email address of the user.
         * @param password The password for the user.
         * @param username A username used to create the user.
         * @param create True if the user should be created when authenticated.
         * @param vars Extra information that will be bundled in the session token.
         */
        virtual void AuthenticateEmail(
            const AZStd::string& email,
            const AZStd::string& password,
            const AZStd::string& username,
            bool create = false,
            const AZStringMap& vars = {}
        ) override;

        /**
         * Authenticate a user with a Facebook auth token.
         *
         * @param accessToken An OAuth access token from the Facebook SDK.
         * @param username A username used to create the user.
         * @param create True if the user should be created when authenticated.
         * @param importFriends True if the Facebook friends should be imported.
         * @param vars Extra information that will be bundled in the session token.
         */
        virtual void AuthenticateFacebook(
            const AZStd::string& accessToken,
            const AZStd::string& username,
            bool create = false,
            bool importFriends = false,
            const AZStringMap& vars = {}
        ) override;

        /**
         * Authenticate a user with a Google auth token.
         *
         * @param accessToken An OAuth access token from the Google SDK.
         * @param username A username used to create the user.
         * @param create True if the user should be created when authenticated.
         * @param vars Extra information that will be bundled in the session token.
         */
        virtual void AuthenticateGoogle(
            const AZStd::string& accessToken,
            const AZStd::string& username,
            bool create = false,
            const AZStringMap& vars = {}
        ) override;

        /**
         * Authenticate a user with Apple Game Center.
         *
         * @param playerId The player id of the user in Game Center.
         * @param bundleId The bundle id of the Game Center application.
         * @param timestampSeconds The date and time that the signature was created.
         * @param salt A random <c>NSString</c> used to compute the hash and keep it randomized.
         * @param signature The verification signature data generated.
         * @param publicKeyUrl The URL for the public encryption key.
         * @param username A username used to create the user.
         * @param create True if the user should be created when authenticated.
         * @param vars Extra information that will be bundled in the session token.
         */
        virtual void AuthenticateGameCenter(
            const AZStd::string& playerId,
            const AZStd::string& bundleId,
            AZStd::sys_time_t timestampSeconds,
            const AZStd::string& salt,
            const AZStd::string& signature,
            const AZStd::string& publicKeyUrl,
            const AZStd::string& username,
            bool create = false,
            const AZStringMap& vars = {}
        ) override;

        /**
         * Authenticate a user with Apple Sign In.
         *
         * @param token The ID token received from Apple to validate.
         * @param username A username used to create the user.
         * @param create True if the user should be created when authenticated.
         * @param vars Extra information that will be bundled in the session token.
         */
        virtual void AuthenticateApple(
            const AZStd::string& token,
            const AZStd::string& username,
            bool create = false,
            const AZStringMap& vars = {}
        ) override;

        /**
         * Authenticate a user with a custom id.
         *
         * @param id A custom identifier usually obtained from an external authentication service.
         * @param username A username used to create the user.
         * @param create True if the user should be created when authenticated.
         * @param vars Extra information that will be bundled in the session token.
         */
        virtual void AuthenticateCustom(
            const AZStd::string& id,
            const AZStd::string& username,
            bool create = false,
            const AZStringMap& vars = {}
        ) override;

        /**
         * Authenticate a user with a Steam auth token.
         *
         * @param token An authentication token from the Steam network.
         * @param username A username used to create the user.
         * @param create True if the user should be created when authenticated.
         * @param vars Extra information that will be bundled in the session token.
         */
        virtual void AuthenticateSteam(
            const AZStd::string& token,
            const AZStd::string& username,
            bool create = false,
            const AZStringMap& vars = {}
        ) override;

        void authenticateRefresh();
#pragma endregion


#pragma region LinkAccount
        /**
        * Link a Facebook profile to a user account.
        *
        * @param session The session of the user.
        * @param accessToken An OAuth access token from the Facebook SDK.
        * @param importFriends True if the Facebook friends should be imported.
        */
        virtual void linkFacebook(
            const AZStd::string& accessToken,
            bool importFriends
        ) override;

        /**
         * Link an email with password to the user account owned by the session.
         *
         * @param session The session of the user.
         * @param email The email address of the user.
         * @param password The password for the user.
         */
        virtual void linkEmail(
            const AZStd::string& email,
            const AZStd::string& password
        ) override;

        /**
         * Link a device id to the user account owned by the session.
         *
         * @param session The session of the user.
         * @param id A device identifier usually obtained from a platform API.
         */
        virtual void linkDevice(
            const AZStd::string& id
        ) override;

        /**
         * Link a Google profile to a user account.
         *
         * @param session The session of the user.
         * @param accessToken An OAuth access token from the Google SDK.
         */
        virtual void linkGoogle(
            const AZStd::string& accessToken
        ) override;

        /**
         * Link a Game Center profile to a user account.
         *
         * @param session The session of the user.
         * @param playerId The player id of the user in Game Center.
         * @param bundleId The bundle id of the Game Center application.
         * @param timestampSeconds The date and time that the signature was created.
         * @param salt A random <c>NSString</c> used to compute the hash and keep it randomized.
         * @param signature The verification signature data generated.
         * @param publicKeyUrl The URL for the public encryption key.
         */
        virtual void linkGameCenter(
            const AZStd::string& playerId,
            const AZStd::string& bundleId,
            AZ::u64 timestampSeconds,
            const AZStd::string& salt,
            const AZStd::string& signature,
            const AZStd::string& publicKeyUrl
        ) override;

        /**
         * Link an Apple ID to the social profiles on the current user's account.
         *
         * @param session The session of the user.
         * @param token The ID token received from Apple.
         */
        virtual void linkApple(
            const AZStd::string& token
        ) override;

        /**
         * Link a Steam profile to a user account.
         *
         * @param session The session of the user.
         * @param token An authentication token from the Steam network.
         */
        virtual void linkSteam(
            const AZStd::string& token
        ) override;

        /**
         * Link a custom id to the user account owned by the session.
         *
         * @param session The session of the user.
         * @param id A custom identifier usually obtained from an external authentication service.
         */
        virtual void linkCustom(
            const AZStd::string& id
        ) override;

        /**
         * Unlink a Facebook profile from the user account owned by the session.
         *
         * @param session The session of the user.
         * @param accessToken An OAuth access token from the Facebook SDK.
         */
        virtual void unlinkFacebook(
            const AZStd::string& accessToken
        ) override;

        /**
         * Unlink an email with password from the user account owned by the session.
         *
         * @param session The session of the user.
         * @param email The email address of the user.
         * @param password The password for the user.
         */
        virtual void unlinkEmail(
            const AZStd::string& email,
            const AZStd::string& password
        ) override;

        /**
         * Unlink a Google profile from the user account owned by the session.
         *
         * @param session The session of the user.
         * @param accessToken An OAuth access token from the Google SDK.
         */
        virtual void unlinkGoogle(
            const AZStd::string& accessToken
        ) override;

        /**
         * Unlink a Game Center profile from the user account owned by the session.
         *
         * @param session The session of the user.
         * @param playerId The player id of the user in Game Center.
         * @param bundleId The bundle id of the Game Center application.
         * @param timestampSeconds The date and time that the signature was created.
         * @param salt A random <c>NSString</c> used to compute the hash and keep it randomized.
         * @param signature The verification signature data generated.
         * @param publicKeyUrl The URL for the public encryption key.
         */
        virtual void unlinkGameCenter(
            const AZStd::string& playerId,
            const AZStd::string& bundleId,
            AZ::u64 timestampSeconds,
            const AZStd::string& salt,
            const AZStd::string& signature,
            const AZStd::string& publicKeyUrl
        ) override;

        /**
         * Unlink a Apple profile from the user account owned by the session.
         *
         * @param session The session of the user.
         * @param token An Apple authentication token.
         */
        virtual void unlinkApple(
            const AZStd::string& token
        ) override;

        /**
         * Unlink a Steam profile from the user account owned by the session.
         *
         * @param session The session of the user.
         * @param token An authentication token from the Steam network.
         */
        virtual void unlinkSteam(
            const AZStd::string& token
        ) override;

        /**
         * Unlink a device id from the user account owned by the session.
         *
         * @param session The session of the user.
         * @param id A device identifier usually obtained from a platform API.
         */
        virtual void unlinkDevice(
            const AZStd::string& id
        ) override;

        /**
         * Unlink a custom id from the user account owned by the session.
         *
         * @param session The session of the user.
         * @param id A custom identifier usually obtained from an external authentication service.
         */
        virtual void unlinkCustom(
            const AZStd::string& id
        ) override;

        /**
         * Import Facebook friends and add them to the user's account.
         *
         * The server will import friends when the user authenticates with Facebook. This function can be used to be
         * explicit with the import operation.
         *
         * @param session The session of the user.
         * @param token An OAuth access token from the Facebook SDK.
         * @param reset True if the Facebook friend import for the user should be reset.
         */
        virtual void importFacebookFriends(
            const AZStd::string& token,
            bool reset
        ) override;
#pragma endregion

#pragma region Account
        /**
         * Fetch the user account owned by the session.
         *
         * @param session The session of the user.
         */
        virtual void getAccount() override;

        /**
         * Update the current user's account on the server.
         *
         * @param session The session for the user.
         * @param username The new username for the user.
         * @param displayName A new display name for the user.
         * @param avatarUrl A new avatar url for the user.
         * @param langTag A new language tag in BCP-47 format for the user.
         * @param location A new location for the user.
         * @param timezone New timezone information for the user.
         */
        virtual void updateAccount(
            const AZStd::string& username,
            const AZStd::string& displayName,
            const AZStd::string& avatarUrl,
            const AZStd::string& langTag,
            const AZStd::string& location,
            const AZStd::string& timezone
        ) override;

        /**
         * Fetch one or more users by id, usernames, and Facebook ids.
         *
         * @param session The session of the user.
         * @param ids List of user IDs.
         * @param usernames List of usernames.
         * @param facebookIds List of Facebook IDs.
         */
        virtual void getUsers(
            const AZStd::vector<AZStd::string>& ids,
            const AZStd::vector<AZStd::string>& usernames = {},
            const AZStd::vector<AZStd::string>& facebookIds = {}
        ) override;
#pragma endregion

#pragma region Friends
        /**
         * Add one or more friends by id.
         *
         * @param session The session of the user.
         * @param ids The ids of the users to add or invite as friends.
         * @param usernames The usernames of the users to add as friends.
         */
        virtual void addFriends(
            const AZStd::vector<AZStd::string>& ids,
            const AZStd::vector<AZStd::string>& usernames = {}
        ) override;

        /**
         * Delete one more or users by id or username from friends.
         *
         * @param session The session of the user.
         * @param ids the user ids to remove as friends.
         * @param usernames The usernames to remove as friends.
         */
        virtual void deleteFriends(
            const AZStd::vector<AZStd::string>& ids,
            const AZStd::vector<AZStd::string>& usernames = {}
        ) override;

        /**
         * Block one or more friends by id.
         *
         * @param session The session of the user.
         * @param ids The ids of the users to block.
         * @param usernames The usernames of the users to block.
         */
        virtual void blockFriends(
            const AZStd::vector<AZStd::string>& ids,
            const AZStd::vector<AZStd::string>& usernames = {}
        ) override;

        /**
         * List of friends of the current user.
         *
         * @param session The session of the user.
         * @param limit The max number of records to return. Between 1 and 100.
         * @param state The friend state to list.
         * @param cursor An optional next page cursor.
         */
        virtual void listFriends(
            AZ::s32 limit,
            AZ::u8 state,
            const AZStd::string& cursor = ""
        ) override;
#pragma endregion

#pragma region Group
        /**
         * Create a group.
         *
         * @param session The session of the user.
         * @param name The name for the group.
         * @param description A description for the group.
         * @param avatarUrl An avatar url for the group.
         * @param langTag A language tag in BCP-47 format for the group.
         * @param open True if the group should have open membership.
         * @param maxCount Maximum number of group members.
         */
        virtual void createGroup(
            const AZStd::string& name,
            const AZStd::string& description = "",
            const AZStd::string& avatarUrl = "",
            const AZStd::string& langTag = "",
            bool open = false,
            AZ::s32 maxCount = {}
        ) override;

        /**
         * Delete a group by id.
         *
         * @param session The session of the user.
         * @param groupId The group id to to remove.
         */
        virtual void deleteGroup(
            const AZStd::string& groupId
        ) override;

        /**
         * Add one or more users to the group.
         *
         * @param session The session of the user.
         * @param groupId The id of the group to add users into.
         * @param ids The ids of the users to add or invite to the group.
         */
        virtual void addGroupUsers(
            const AZStd::string& groupId,
            const AZStd::vector<AZStd::string>& ids
        ) override;

        /**
         * List all users part of the group.
         *
         * @param session The session of the user.
         * @param groupId The id of the group.
         * @param limit The max number of records to return. Between 1 and 100.
         * @param state The group membership state to list.
         * @param cursor An optional next page cursor.
         */
        virtual void listGroupUsers(
            const AZStd::string& groupId,
            AZ::s32 limit,
            AZ::u8 state,
            const AZStd::string& cursor = ""
        ) override;

        /**
         * Kick one or more users from the group.
         *
         * @param session The session of the user.
         * @param groupId The id of the group.
         * @param ids The ids of the users to kick.
         */
        virtual void kickGroupUsers(
            const AZStd::string& groupId,
            const AZStd::vector<AZStd::string>& ids
        ) override;

        /**
         * Join a group if it has open membership or request to join it.
         *
         * @param session The session of the user.
         * @param groupId The id of the group to join.
         */
        virtual void joinGroup(
            const AZStd::string& groupId
        ) override;

        /**
         * Leave a group by id.
         *
         * @param session The session of the user.
         * @param groupId The id of the group to leave.
         */
        virtual void leaveGroup(
            const AZStd::string& groupId
        ) override;

        /**
         * List groups on the server.
         *
         * @param session The session of the user.
         * @param name The name filter to apply to the group list.
         * @param limit The number of groups to list.
         * @param cursor A cursor for the current position in the groups to list.
         */
        virtual void listGroups(
            const AZStd::string& name,
            AZ::s32 limit = 0,
            const AZStd::string& cursor = ""
        ) override;

        /**
         * List of groups the current user is a member of.
         *
         * @param session The session of the user.
         * @param limit The max number of records to return. Between 1 and 100.
         * @param state The group membership state to list.
         * @param cursor An optional next page cursor.
         */
        virtual void listUserGroups(
            AZ::s32 limit,
            AZ::u8 state,
            const AZStd::string& cursor = ""
        ) override;

        /**
         * List groups a user is a member of.
         *
         * @param session The session of the user.
         * @param userId The id of the user whose groups to list.
         * @param limit The max number of records to return. Between 1 and 100.
         * @param state The group membership state to list.
         * @param cursor An optional next page cursor.
         */
        virtual void listUserGroupsWithId(
            const AZStd::string& userId,
            AZ::s32 limit,
            AZ::u8 state,
            const AZStd::string& cursor = ""
        ) override;

        /**
         * Promote a set of users in a group to the next role up.
         *
         * @param session The session of the user.
         * @param groupId The group ID to promote in.
         * @param ids The ids of the users to promote.
         */
        virtual void promoteGroupUsers(
            const AZStd::string& groupId,
            const AZStd::vector<AZStd::string>& ids
        ) override;

        /**
         * Demote a set of users in a group to the next role down.
         *
         * @param session The session of the user.
         * @param groupId The group ID to demote in.
         * @param ids The ids of the users to demote.
         */
        virtual void demoteGroupUsers(
            const AZStd::string& groupId,
            const AZStd::vector<AZStd::string>& ids
        ) override;

        /**
         * Update a group.
         *
         * The user must have the correct access permissions for the group.
         *
         * @param session The session of the user.
         * @param groupId The id of the group to update.
         * @param name A new name for the group.
         * @param description A new description for the group.
         * @param avatarUrl A new avatar url for the group.
         * @param langTag A new language tag in BCP-47 format for the group.
         * @param open True if the group should have open membership.
         */
        virtual void updateGroup(
            const AZStd::string& groupId,
            const AZStd::string& name,
            const AZStd::string& description,
            const AZStd::string& avatarUrl,
            const AZStd::string& langTag,
            bool open
        ) override;
#pragma endregion

#pragma region Leaderboards
        /**
         * List records from a leaderboard.
         *
         * @param session The session of the user.
         * @param leaderboardId The id of the leaderboard to list.
         * @param ownerIds Record owners to fetch with the list of records.
         * @param limit The number of records to list.
         * @param cursor A cursor for the current position in the leaderboard records to list.
         */
        virtual void listLeaderboardRecords(
            const AZStd::string& leaderboardId,
            const AZStd::vector<AZStd::string>& ownerIds,
            AZ::s32 limit,
            const AZStd::string& cursor
        ) override;

        /**
         * List leaderboard records from a given leaderboard around the owner.
         *
         * @param session The session of the user.
         * @param leaderboardId The id of the leaderboard to list.
         * @param ownerId The owner to retrieve records around.
         * @param limit Max number of records to return. Between 1 and 100.
         */
        virtual void listLeaderboardRecordsAroundOwner(
            const AZStd::string& leaderboardId,
            const AZStd::string& ownerId,
            AZ::s32 limit
        ) override;

        /**
         * Write a record to a leaderboard.
         *
         * @param session The session for the user.
         * @param leaderboardId The id of the leaderboard to write.
         * @param score The score for the leaderboard record.
         * @param subscore The subscore for the leaderboard record.
         * @param metadata The metadata for the leaderboard record.
         */
        virtual void writeLeaderboardRecord(
            const AZStd::string& leaderboardId,
            AZ::s64 score,
            AZ::s64 subscore,
            AZStd::string metadata
        ) override;

        /**
         * Delete a leaderboard record.
         *
         * @param session The session of the user.
         * @param leaderboardId The id of the leaderboard with the record to be deleted.
         */
        virtual void deleteLeaderboardRecord(
            const AZStd::string& leaderboardId
        ) override;
#pragma endregion

#pragma region Tournament
        /**
         * A request to submit a score to a tournament.
         *
         * @param session The session for the user.
         * @param tournamentId The tournament ID to write the record for.
         * @param score The score value to submit.
         * @param subscore  An optional secondary value.
         * @param metadata A JSON object of additional properties.
         */
        virtual void writeTournamentRecord(
            const AZStd::string& tournamentId,
            AZ::s64 score,
            AZ::s64 subscore,
            AZStd::string metadata
        ) override;

        /**
         * List active/upcoming tournaments based on given filters.
         *
         * @param session The session of the user.
         * @param categoryStart The start of the categories to include. Defaults to 0.
         * @param categoryEnd The end of the categories to include. Defaults to 128.
         * @param startTime The start time for tournaments. Defaults to current Unix time.
         * @param endTime The end time for tournaments. Defaults to +1 year from current Unix time.
         * @param limit Max number of records to return. Between 1 and 100.
         * @param cursor A next page cursor for listings.
         */
        virtual void listTournaments(
            AZ::u32 categoryStart,
            AZ::u32 categoryEnd,
            AZ::u32 startTime,
            AZ::u32 endTime,
            AZ::s32 limit,
            const AZStd::string& cursor
        ) override;

        /**
         * List tournament records from a given tournament.
         *
         * @param session The session of the user.
         * @param tournamentId The ID of the tournament to list for.
         * @param limit Max number of records to return. Between 1 and 100.
         * @param cursor A next or previous page cursor.
         * @param ownerIds One or more owners to retrieve records for.
         */
        virtual void listTournamentRecords(
            const AZStd::string& tournamentId,
            AZ::s32 limit,
            const AZStd::string& cursor,
            const AZStd::vector<AZStd::string>& ownerIds = {}
        ) override;

        /**
         * List tournament records from a given tournament around the owner.
         *
         * @param session The session of the user.
         * @param tournamentId The ID of the tournament to list for.
         * @param ownerId The owner to retrieve records around.
         * @param limit Max number of records to return. Between 1 and 100.
         */
        virtual void listTournamentRecordsAroundOwner(
            const AZStd::string& tournamentId,
            const AZStd::string& ownerId,
            AZ::s32 limit
        ) override;

        /**
         * Join a tournament if it has open membership or request to join it.
         *
         * @param session The session of the user.
         * @param tournamentId The id of the tournament to join.
         */
        virtual void joinTournament(
            const AZStd::string& tournamentId
        ) override;
#pragma endregion

#pragma region Matches
        /**
         * Fetch a list of matches active on the server.
         *
         * @param session The session of the user.
         * @param min_size The minimum number of match participants.
         * @param max_size The maximum number of match participants.
         * @param limit The number of matches to list.
         * @param label The label to filter the match list on.
         * @param authoritative <c>true</c> to include authoritative matches.
         */
        virtual void listMatches(
            AZ::s32 min_size,
            AZ::s32 max_size,
            AZ::s32 limit,
            const AZStd::string& label,
            const AZStd::string& query,
            bool authoritative
        ) override;

        /**
         * Create a multiplayer match on the server.
         */
        virtual void createMatch() override;

        /**
         * Join a multiplayer match by ID.
         *
         * @param matchId A match ID.
         */
        virtual void joinMatch(
            const AZStd::string& matchId,
            const AZStringMap& metadata
        ) override;

        /**
         * Join a multiplayer match with a matchmaker.
         *
         * @param token A matchmaker ticket result object.
         */
        virtual void joinMatchByToken(
            const AZStd::string& token
        ) override;

        /**
         * Leave a match on the server.
         *
         * @param matchId The match to leave.
         */
        virtual void leaveMatch(
            const AZStd::string& matchId
        ) override;
        /**
          * Send a state change to a match on the server.
          *
          * When no presences are supplied the new match state will be sent to all presences.
          *
          * @param matchId The Id of the match.
          * @param opCode An operation code for the match state.
          * @param data The new state to send to the match.
          * @param presences The presences in the match to send the state.
          */
        virtual void sendMatchData(
            const AZStd::string& matchId,
            AZ::s64 opCode,
            const AZStd::string& data,
            const AZStd::vector<UserPresence>& presences
        ) override;
#pragma endregion

#pragma region Notifications
        /**
         * List notifications for the user with an optional cursor.
         *
         * @param session The session of the user.
         * @param limit The number of notifications to list.
         * @param cacheableCursor A cursor for the current position in notifications to list.
         */
        virtual void listNotifications(
            AZ::s32 limit,
            const AZStd::string& cacheableCursor
        ) override;

        /**
         * Delete one or more notifications by id.
         *
         * @param session The session of the user.
         * @param notificationIds The notification ids to remove.
         */
        virtual void deleteNotifications(
            const AZStd::vector<AZStd::string>& notificationIds
        ) override;
#pragma endregion

#pragma region Chat
        /**
         * List messages from a chat channel.
         *
         * @param session The session of the user.
         * @param channelId A channel identifier.
         * @param limit The number of chat messages to list.
         * @param cursor A cursor for the current position in the messages history to list.
         * @param forward Fetch messages forward from the current cursor (or the start).
         */
        virtual void listChannelMessages(
            const AZStd::string& channelId,
            AZ::s32 limit,
            const AZStd::string& cursor,
            bool forward
        ) override;
        /**
                * Join a chat channel on the server.
                *
                * @param target The target channel to join.
                * @param type The type of channel to join.
                * @param persistence True if chat messages should be stored.
                * @param hidden True if the user should be hidden on the channel.
                */
        virtual void joinChat(
            const AZStd::string& target,
            AZ::u8 channelType,
            bool persistence,
            bool hidden
        ) override;

        /**
         * Leave a chat channel on the server.
         *
         * @param channelId The channel to leave.
         */
        virtual void leaveChat(
            const AZStd::string& channelId
        ) override;

        /**
         * Send a chat message to a channel on the server.
         *
         * @param channelId The channel to send on.
         * @param content The content of the chat message. Must be a JSON object.
         */
        virtual void writeChatMessage(
            const AZStd::string& channelId,
            const AZStd::string& content
        ) override;

        /**
         * Update a chat message to a channel on the server.
         *
         * @param channelId The ID of the chat channel with the message.
         * @param messageId The ID of the message to update.
         * @param content The content update for the message. Must be a JSON object.
         */
        virtual void updateChatMessage(
            const AZStd::string& channelId,
            const AZStd::string& messageId,
            const AZStd::string& content
        ) override;

        /**
         * Remove a chat message from a channel on the server.
         *
         * @param channelId The chat channel with the message.
         * @param messageId The ID of a chat message to remove.
         */
        virtual void removeChatMessage(
            const AZStd::string& channelId,
            const AZStd::string& messageId
        ) override;
#pragma endregion

#pragma region StorageObjects
        /**
         * List storage objects in a collection which have public read access.
         *
         * @param session The session of the user.
         * @param collection The collection to list over.
         * @param limit The number of objects to list.
         * @param cursor A cursor to paginate over the collection.
         */
        virtual void listStorageObjects(
            const AZStd::string& collection,
            AZ::s32 limit,
            const AZStd::string& cursor
        ) override;

        /**
         * List storage objects in a collection which belong to a specific user and have public read access.
         *
         * @param session The session of the user.
         * @param collection The collection to list over.
         * @param userId The user ID of the user to list objects for.
         * @param limit The number of objects to list.
         * @param cursor A cursor to paginate over the collection.
         */
        virtual void listUsersStorageObjects(
            const AZStd::string& collection,
            const AZStd::string& userId,
            AZ::s32 limit,
            const AZStd::string& cursor
        ) override;

        /**
         * Write objects to the storage engine.
         *
         * @param session The session of the user.
         * @param objects The objects to write.
         */
        virtual void writeStorageObjects(
            const AZStd::vector<StorageObjectWrite>& objects
        ) override;

        /**
         * Read one or more objects from the storage engine.
         *
         * @param session The session of the user.
         * @param objectIds The objects to read.
         */
        virtual void readStorageObjects(
            const AZStd::vector<ReadStorageObjectId>& objectIds
        ) override;

        /**
         * Delete one or more storage objects.
         *
         * @param session The session of the user.
         * @param objectIds The ids of the objects to delete.
         */
        virtual void deleteStorageObjects(
            const AZStd::vector<DeleteStorageObjectId>& objectIds
        ) override;
#pragma endregion

#pragma region Rpc
        /**
         * Execute a server framework function with an input payload on the server.
         *
         * @param session The session of the user.
         * @param id The id of the function to execute on the server.
         * @param payload The payload to send with the function call.
         */
        virtual void rpc(
            const AZStd::string& id,
            const AZStd::string& payload
        ) override;

        /**
         * Execute a server framework function with an input payload on the server.
         *
         * @param http_key The server's runtime HTTP key.
         * @param id The id of the function to execute on the server.
         * @param payload The payload to send with the function call.
         */
        virtual void rpcWithId(
            const AZStd::string& http_key,
            const AZStd::string& id,
            const AZStd::string& payload
        ) override;
        /**
                 * Send an RPC message to the server.
                 *
                 * @param id The ID of the function to execute.
                 * @param payload The string content to send to the server.
                 */
        virtual void rtRpc(
            const AZStd::string& id,
            const AZStd::string& payload
        ) override;
#pragma endregion

#pragma region Matchmaker
        /**
         * Join the matchmaker pool and search for opponents on the server.
         *
         * @param minCount The minimum number of players to compete against.
         * @param maxCount The maximum number of players to compete against.
         * @param query A matchmaker query to search for opponents.
         * @param stringProperties A set of k/v properties to provide in searches.
         * @param numericProperties A set of k/v numeric properties to provide in searches.
         * @param countMultiple An optional multiple of the matched count that must be satisfied.
         */
        virtual void addMatchmaker(
            AZ::s32 minCount,
            AZ::s32 maxCount,
            const AZStd::string& query,
            const AZStringMap& stringProperties,
            const AZStringDoubleMap& numericProperties,
            AZ::s32 countMultiple
        ) override;

        /**
         * Leave the matchmaker pool by ticket.
         *
         * @param ticket The ticket returned by the matchmaker on join. See <c>NMatchmakerTicket.ticket</c>.
         */
        virtual void removeMatchmaker(
            const AZStd::string& ticket
        ) override;
#pragma endregion

#pragma region Party     
        /**
         * Follow one or more users for status updates.
         *
         * @param userIds The user Ids to follow.
         */
        virtual void followUsers(
            const AZStd::vector<AZStd::string>& userIds
        ) override;

        /**
         * Unfollow status updates for one or more users.
         *
         * @param userIds The ids of users to unfollow.
         */
        virtual void unfollowUsers(
            const AZStd::vector<AZStd::string>& userIds
        ) override;

        /**
         * Update the user's status online.
         *
         * @param status The new status of the user.
         */
        virtual void updateStatus(
            const AZStd::string& status
        ) override;

        

        /**
         * Accept a party member's request to join the party.
         *
         * @param partyId The party ID to accept the join request for.
         * @param presence The presence to accept as a party member.
         */
        virtual void acceptPartyMember(
            const AZStd::string& partyId,
            UserPresence& presence
        ) override;

        /**
         * Begin matchmaking as a party.
         * @param partyId Party ID.
         * @param query Filter query used to identify suitable users.
         * @param minCount Minimum total user count to match together.
         * @param maxCount Maximum total user count to match together.
         * @param stringProperties String properties.
         * @param numericProperties Numeric properties.
         * @param countMultiple An optional multiple of the matched count that must be satisfied.
         */
        virtual void addMatchmakerParty(
            const AZStd::string& partyId,
            const AZStd::string& query,
            AZ::s32 minCount,
            AZ::s32 maxCount,
            const AZStringMap& stringProperties,
            const AZStringDoubleMap& numericProperties,
            AZ::s32 countMultiple
        ) override;

        /**
         * End a party, kicking all party members and closing it.
         * @param partyId The ID of the party.
         */
        virtual void closeParty(
            const AZStd::string& partyId
        ) override;

        /**
         * Create a party.
         * @param open Whether or not the party will require join requests to be approved by the party leader.
         * @param maxSize Maximum number of party members.
         */
        virtual void createParty(
            bool open,
            AZ::s32 maxSize
        ) override;

        /**
         * Join a party.
         * @param partyId Party ID.
         */
        virtual void joinParty(
            const AZStd::string& partyId
        ) override;

        /**
         * Leave the party.
         * @param partyId Party ID.
         */
        virtual void leaveParty(
            const AZStd::string& partyId
        ) override;

        /**
         * Request a list of pending join requests for a party.
         * @param partyId Party ID.
         */
        virtual void listPartyJoinRequests(
            const AZStd::string& partyId
        ) override;

        /**
         * Promote a new party leader.
         * @param partyId Party ID.
         * @param partyMember The presence of an existing party member to promote as the new leader.
         */
        virtual void promotePartyMember(
            const AZStd::string& partyId,
            UserPresence& partyMember
        ) override;

        /**
         * Cancel a party matchmaking process using a ticket.
         * @param partyId Party ID.
         * @param ticket The ticket to cancel.
         */
        virtual void removeMatchmakerParty(
            const AZStd::string& partyId,
            const AZStd::string& ticket
        ) override;

        /**
         * Kick a party member, or decline a request to join.
         * @param partyId Party ID to remove/reject from.
         * @param presence The presence to remove or reject.
         */
        virtual void removePartyMember(
            const AZStd::string& partyId,
            UserPresence& presence
        ) override;

        /**
         * Send data to a party.
         * @param partyId Party ID to send to.
         * @param opCode Op code value.
         * @param data The input data to send from the byte buffer, if any.
         */
        virtual void sendPartyData(
            const AZStd::string& partyId,
            AZ::s32 opCode,
            AZStd::string& data
        ) override;
#pragma endregion


        // Callbacks
        void OnConnect();
        void OnDisconnect(const RtClientDisconnectInfo& info);

        void OnAuthenticateSuccess(const Nakama::NSessionPtr& session);
        void OnAuthenticateFailed(const Nakama::NError& error);

        void OnLinkSuccess();
        void OnLinkFailed(const Error& error);

        void OnUnlinkSuccess();
        void OnUnlinkFailed(const Error& error);

        void OnImportFacebookFriendsSuccess();
        void OnImportFacebookFriendsFailed(const Error& error);

        void OnUnauthenticated();

        void OnGetAccountSuccess(const Account& account);
        void OnGetAccountFailed(const Error& error);
        void OnUpdateAccountSuccess(const AZStd::string& username, const AZStd::string& displayName, const AZStd::string& avatarUrl, const AZStd::string& langTag, const AZStd::string& location, const AZStd::string& timezone);
        void OnUpdateAccountFailed(const Error& error);
        void OnGetUsersSuccess(const AZStd::vector<User>& users);
        void OnGetUsersFailed(const Error& error);

        void OnAddFriendsSuccess(const AZStd::vector<AZStd::string>& ids, const AZStd::vector<AZStd::string>& usernames);
        void OnAddFriendsFailed(const Error& error);
        void OnDeleteFriendsSuccess(const AZStd::vector<AZStd::string>& ids, const AZStd::vector<AZStd::string>& usernames);
        void OnDeleteFriendsFailed(const Error& error);
        void OnBlockFriendsSuccess(const AZStd::vector<AZStd::string>& ids, const AZStd::vector<AZStd::string>& usernames);
        void OnBlockFriendsFailed(const Error& error);
        void OnListFriendsSuccess(const AZStd::vector<Friend>& friends, AZ::s32 limit, AZ::u8 state, const AZStd::string& cursor);
        void OnListFriendsFailed(const Error& error);

        void OnCreateGroupSuccess(const Group& group);
        void OnCreateGroupFailed(const Error& error);
        void OnDeleteGroupSuccess(const AZStd::string& groupId);
        void OnDeleteGroupFailed(const Error& error);
        void OnAddGroupUsersSuccess(const AZStd::string& groupId, const AZStd::vector<AZStd::string>& ids);
        void OnAddGroupUsersFailed(const Error& error);
        void OnListGroupUsersSuccess(const GroupUserList& users, const AZStd::string& groupId, AZ::s32 limit, AZ::u8 state, const AZStd::string& cursor);
        void OnListGroupUsersFailed(const Error& error);
        void OnKickGroupUsersSuccess(const AZStd::string& groupId, const AZStd::vector<AZStd::string>& ids);
        void OnKickGroupUsersFailed(const Error& error);
        void OnJoinGroupSuccess(const AZStd::string& groupId);
        void OnJoinGroupFailed(const Error& error);
        void OnLeaveGroupSuccess(const AZStd::string& groupId);
        void OnLeaveGroupFailed(const Error& error);
        void OnListGroupsSuccess(const GroupList& groups, const AZStd::string& name, AZ::s32 limit, const AZStd::string& cursor);
        void OnListGroupsFailed(const Error& error);
        void OnListUserGroupsSuccess(const UserGroupList& groups, AZ::s32 limit, AZ::u8 state, const AZStd::string& cursor);
        void OnListUserGroupsFailed(const Error& error);
        void OnListUserGroupsWithIdSuccess(const UserGroupList& groups, const AZStd::string& userId, AZ::s32 limit, AZ::u8 state, const AZStd::string& cursor);
        void OnListUserGroupsWithIdFailed(const Error& error);
        void OnPromoteGroupUsersSuccess(const AZStd::string& groupId, const AZStd::vector<AZStd::string>& ids);
        void OnPromoteGroupUsersFailed(const Error& error);
        void OnDemoteGroupUsersSuccess(const AZStd::string& groupId, const AZStd::vector<AZStd::string>& ids);
        void OnDemoteGroupUsersFailed(const Error& error);
        void OnUpdateGroupSuccess(const AZStd::string& groupId, const AZStd::string& name, const AZStd::string& description, const AZStd::string& avatarUrl, const AZStd::string& langTag, bool open);
        void OnUpdateGroupFailed(const Error& error);

    protected:
        /*
        * Puts this component into an active state.
        * The system calls this function once during activation of each entity that owns the
        * component. You must override this function. The system calls a component's Activate()
        * function only if all services and components that the component depends on are present
        * and active.
        */
        void Activate() override;

        /*
        * Deactivates this component.
        * The system calls this function when the owning entity is being deactivated. You must
        * override this function. As a best practice, ensure that this function returns this component
        * to a minimal footprint. The order of deactivation is the reverse of activation, so your
        * component is deactivated before the components it depends on.
        *
        * The system always calls a component's Deactivate() function before destroying the component.
        * However, deactivation is not always followed by the destruction of the component. An entity and
        * its components can be deactivated and reactivated without being destroyed. Ensure that your
        * Deactivate() implementation can handle this scenario.
        */
        void Deactivate() override;
    };
} // namespace NakamaClientGem
