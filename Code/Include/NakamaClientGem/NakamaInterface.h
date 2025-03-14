
#pragma once

#include <AzCore/Component/ComponentBus.h>
#include <AzCore/RTTI/BehaviorContext.h>
#include "NakamaClientDataTypes.h"

namespace NakamaClientGem
{
    class NakamaRequests
        : public AZ::ComponentBus
    {
    public:
        AZ_RTTI(NakamaClientGem::NakamaRequests, "{023D49B4-E555-4D02-8AFA-A570E6856427}");

        // Put your public request methods here.

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
        ) = 0;

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
        ) = 0;

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
        ) = 0;

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
        ) = 0;

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
        ) = 0;

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
        ) = 0;

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
        ) = 0;

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
        ) = 0;

#pragma endregion Authentication

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
        ) = 0;

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
        ) = 0;

        /**
         * Link a device id to the user account owned by the session.
         *
         * @param session The session of the user.
         * @param id A device identifier usually obtained from a platform API.
         */
        virtual void linkDevice(
            const AZStd::string& id
        ) = 0;

        /**
         * Link a Google profile to a user account.
         *
         * @param session The session of the user.
         * @param accessToken An OAuth access token from the Google SDK.
         */
        virtual void linkGoogle(
            const AZStd::string& accessToken
        ) = 0;

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
        ) = 0;

        /**
         * Link an Apple ID to the social profiles on the current user's account.
         *
         * @param session The session of the user.
         * @param token The ID token received from Apple.
         */
        virtual void linkApple(
            const AZStd::string& token
        ) = 0;

        /**
         * Link a Steam profile to a user account.
         *
         * @param session The session of the user.
         * @param token An authentication token from the Steam network.
         */
        virtual void linkSteam(
            const AZStd::string& token
        ) = 0;

        /**
         * Link a custom id to the user account owned by the session.
         *
         * @param session The session of the user.
         * @param id A custom identifier usually obtained from an external authentication service.
         */
        virtual void linkCustom(
            const AZStd::string& id
        ) = 0;

        /**
         * Unlink a Facebook profile from the user account owned by the session.
         *
         * @param session The session of the user.
         * @param accessToken An OAuth access token from the Facebook SDK.
         */
        virtual void unlinkFacebook(
            const AZStd::string& accessToken
        ) = 0;

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
        ) = 0;

        /**
         * Unlink a Google profile from the user account owned by the session.
         *
         * @param session The session of the user.
         * @param accessToken An OAuth access token from the Google SDK.
         */
        virtual void unlinkGoogle(
            const AZStd::string& accessToken
        ) = 0;

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
        ) = 0;

        /**
         * Unlink a Apple profile from the user account owned by the session.
         *
         * @param session The session of the user.
         * @param token An Apple authentication token.
         */
        virtual void unlinkApple(
            const AZStd::string& token
        ) = 0;

        /**
         * Unlink a Steam profile from the user account owned by the session.
         *
         * @param session The session of the user.
         * @param token An authentication token from the Steam network.
         */
        virtual void unlinkSteam(
            const AZStd::string& token
        ) = 0;

        /**
         * Unlink a device id from the user account owned by the session.
         *
         * @param session The session of the user.
         * @param id A device identifier usually obtained from a platform API.
         */
        virtual void unlinkDevice(
            const AZStd::string& id
        ) = 0;

        /**
         * Unlink a custom id from the user account owned by the session.
         *
         * @param session The session of the user.
         * @param id A custom identifier usually obtained from an external authentication service.
         */
        virtual void unlinkCustom(
            const AZStd::string& id
        ) = 0;

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
        ) = 0;
#pragma endregion

#pragma region Account
        /**
         * Fetch the user account owned by the session.
         *
         * @param session The session of the user.
         */
        virtual void getAccount() = 0;

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
        ) = 0;

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
        ) = 0;
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
        ) = 0;

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
        ) = 0;

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
        ) = 0;

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
        ) = 0;
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
        ) = 0;

        /**
         * Delete a group by id.
         *
         * @param session The session of the user.
         * @param groupId The group id to to remove.
         */
        virtual void deleteGroup(
            const AZStd::string& groupId
        ) = 0;

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
        ) = 0;

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
        ) = 0;

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
        ) = 0;

        /**
         * Join a group if it has open membership or request to join it.
         *
         * @param session The session of the user.
         * @param groupId The id of the group to join.
         */
        virtual void joinGroup(
            const AZStd::string& groupId
        ) = 0;

        /**
         * Leave a group by id.
         *
         * @param session The session of the user.
         * @param groupId The id of the group to leave.
         */
        virtual void leaveGroup(
            const AZStd::string& groupId
        ) = 0;

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
        ) = 0;

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
        ) = 0;

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
        ) = 0;

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
        ) = 0;

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
        ) = 0;

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
        ) = 0;
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
        ) = 0;

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
        ) = 0;

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
        ) = 0;

        /**
         * Delete a leaderboard record.
         *
         * @param session The session of the user.
         * @param leaderboardId The id of the leaderboard with the record to be deleted.
         */
        virtual void deleteLeaderboardRecord(
            const AZStd::string& leaderboardId
        ) = 0;
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
        ) = 0;

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
        ) = 0;

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
        ) = 0;

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
        ) = 0;

        /**
         * Join a tournament if it has open membership or request to join it.
         *
         * @param session The session of the user.
         * @param tournamentId The id of the tournament to join.
         */
        virtual void joinTournament(
            const AZStd::string& tournamentId
        ) = 0;
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
        ) = 0;
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
        ) = 0;

        /**
         * Delete one or more notifications by id.
         *
         * @param session The session of the user.
         * @param notificationIds The notification ids to remove.
         */
        virtual void deleteNotifications(
            const AZStd::vector<AZStd::string>& notificationIds
        ) = 0;
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
        ) = 0;
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
        ) = 0;

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
        ) = 0;

        /**
         * Write objects to the storage engine.
         *
         * @param session The session of the user.
         * @param objects The objects to write.
         */
        virtual void writeStorageObjects(
            const AZStd::vector<StorageObjectWrite>& objects
        ) = 0;

        /**
         * Read one or more objects from the storage engine.
         *
         * @param session The session of the user.
         * @param objectIds The objects to read.
         */
        virtual void readStorageObjects(
            const AZStd::vector<ReadStorageObjectId>& objectIds
        ) = 0;

        /**
         * Delete one or more storage objects.
         *
         * @param session The session of the user.
         * @param objectIds The ids of the objects to delete.
         */
        virtual void deleteStorageObjects(
            const AZStd::vector<DeleteStorageObjectId>& objectIds
        ) = 0;
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
        ) = 0;

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
        ) = 0;
#pragma endregion

#pragma region RealtimeClient
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
        ) = 0;

        /**
         * Leave a chat channel on the server.
         *
         * @param channelId The channel to leave.
         */
        virtual void leaveChat(
            const AZStd::string& channelId
        ) = 0;

        /**
         * Send a chat message to a channel on the server.
         *
         * @param channelId The channel to send on.
         * @param content The content of the chat message. Must be a JSON object.
         */
        virtual void writeChatMessage(
            const AZStd::string& channelId,
            const AZStd::string& content
        ) = 0;

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
        ) = 0;

        /**
         * Remove a chat message from a channel on the server.
         *
         * @param channelId The chat channel with the message.
         * @param messageId The ID of a chat message to remove.
         */
        virtual void removeChatMessage(
            const AZStd::string& channelId,
            const AZStd::string& messageId
        ) = 0;

        /**
         * Create a multiplayer match on the server.
         */
        virtual void createMatch() = 0;

        /**
         * Join a multiplayer match by ID.
         *
         * @param matchId A match ID.
         */
        virtual void joinMatch(
            const AZStd::string& matchId,
            const AZStringMap& metadata
        ) = 0;

        /**
         * Join a multiplayer match with a matchmaker.
         *
         * @param token A matchmaker ticket result object.
         */
        virtual void joinMatchByToken(
            const AZStd::string& token
        ) = 0;

        /**
         * Leave a match on the server.
         *
         * @param matchId The match to leave.
         */
        virtual void leaveMatch(
            const AZStd::string& matchId
        ) = 0;

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
        ) = 0;

        /**
         * Leave the matchmaker pool by ticket.
         *
         * @param ticket The ticket returned by the matchmaker on join. See <c>NMatchmakerTicket.ticket</c>.
         */
        virtual void removeMatchmaker(
            const AZStd::string& ticket
        ) = 0;

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
        ) = 0;

        /**
         * Follow one or more users for status updates.
         *
         * @param userIds The user Ids to follow.
         */
        virtual void followUsers(
            const AZStd::vector<AZStd::string>& userIds
        ) = 0;

        /**
         * Unfollow status updates for one or more users.
         *
         * @param userIds The ids of users to unfollow.
         */
        virtual void unfollowUsers(
            const AZStd::vector<AZStd::string>& userIds
        ) = 0;

        /**
         * Update the user's status online.
         *
         * @param status The new status of the user.
         */
        virtual void updateStatus(
            const AZStd::string& status
        ) = 0;

        /**
         * Send an RPC message to the server.
         *
         * @param id The ID of the function to execute.
         * @param payload The string content to send to the server.
         */
        virtual void rtRpc(
            const AZStd::string& id,
            const AZStd::string& payload
        ) = 0;

        /**
         * Accept a party member's request to join the party.
         *
         * @param partyId The party ID to accept the join request for.
         * @param presence The presence to accept as a party member.
         */
        virtual void acceptPartyMember(
            const AZStd::string& partyId,
            const UserPresence& presence
        ) = 0;

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
        ) = 0;

        /**
         * End a party, kicking all party members and closing it.
         * @param partyId The ID of the party.
         */
        virtual void closeParty(
            const AZStd::string& partyId
        ) = 0;

        /**
         * Create a party.
         * @param open Whether or not the party will require join requests to be approved by the party leader.
         * @param maxSize Maximum number of party members.
         */
        virtual void createParty(
            bool open,
            AZ::s32 maxSize
        ) = 0;

        /**
         * Join a party.
         * @param partyId Party ID.
         */
        virtual void joinParty(
            const AZStd::string& partyId
        ) = 0;

        /**
         * Leave the party.
         * @param partyId Party ID.
         */
        virtual void leaveParty(
            const AZStd::string& partyId
        ) = 0;

        /**
         * Request a list of pending join requests for a party.
         * @param partyId Party ID.
         */
        virtual void listPartyJoinRequests(
            const AZStd::string& partyId
        ) = 0;

        /**
         * Promote a new party leader.
         * @param partyId Party ID.
         * @param partyMember The presence of an existing party member to promote as the new leader.
         */
        virtual void promotePartyMember(
            const AZStd::string& partyId,
            const UserPresence& partyMember
        ) = 0;

        /**
         * Cancel a party matchmaking process using a ticket.
         * @param partyId Party ID.
         * @param ticket The ticket to cancel.
         */
        virtual void removeMatchmakerParty(
            const AZStd::string& partyId,
            const AZStd::string& ticket
        ) = 0;

        /**
         * Kick a party member, or decline a request to join.
         * @param partyId Party ID to remove/reject from.
         * @param presence The presence to remove or reject.
         */
        virtual void removePartyMember(
            const AZStd::string& partyId,
            const UserPresence& presence
        ) = 0;

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
        ) = 0;
#pragma endregion



        // Put notification events here. Examples:
        // void RegisterEvent(AZ::EventHandler<...> notifyHandler);
        // AZ::Event<...> m_notifyEvent1;

    };

    using NakamaRequestBus = AZ::EBus<NakamaRequests>;

    class NakamaListenerNotifications
        : public AZ::EBusTraits
    {
    public:
        AZ_RTTI(NakamaClientGem::NakamaListenerNotifications, "{254B173E-E851-4579-856F-B325C967D107}");

        static const AZ::EBusHandlerPolicy HandlerPolicy = AZ::EBusHandlerPolicy::Multiple;

        // Listener
        virtual void OnConnect() = 0;
        virtual void OnDisconnect(const RtClientDisconnectInfo& info) = 0;
        virtual void OnRtError(const RtError& error) = 0;
        virtual void OnChannelMessage(const ChannelMessage& message) = 0;
        virtual void OnChannelPresence(const ChannelPresenceEvent& presenceEvent) = 0;
        virtual void OnMatchmakerMatched(const MatchmakerMatched& matched) = 0;
        virtual void OnMatchData(const MatchData& matchData) = 0;
        virtual void OnMatchPresence(const MatchPresenceEvent& matchPresence) = 0;
        virtual void OnNotifications(const NotificationList& notifications) = 0;
        virtual void OnParty(const Party& party) = 0;
        virtual void OnPartyClosed(const PartyClose& partyClosed) = 0;
        virtual void OnPartyData(const PartyData& partyData) = 0;
        virtual void OnPartyJoinRequest(const PartyJoinRequest& partyJoinRequest) = 0;
        virtual void OnPartyLeader(const PartyLeader& partyLeader) = 0;
        virtual void OnPartyMatchmakerTicket(const PartyMatchmakerTicket& partyMatchmakerTicket) = 0;
        virtual void OnPartyPresence(const PartyPresenceEvent& partyPresence) = 0;
        virtual void OnStatusPresence(const StatusPresenceEvent& presenceEvent) = 0;
        virtual void OnStreamPresence(const StreamPresenceEvent& presenceEvent) = 0;
        virtual void OnStreamData(const StreamData& data) = 0;

        virtual void OnError(const Error& error) = 0;

        virtual void OnAuthenticateSuccess(const AZStd::string& username,const AZStd::string& userId) = 0;
        virtual void OnAuthenticateFailed(AZ::s8 code, const AZStd::string& message) = 0;

        virtual void OnLinkSuccess() = 0;
        virtual void OnLinkFailed(const Error& error) = 0;

        virtual void OnUnlinkSuccess() = 0;
        virtual void OnUnlinkFailed(const Error& error) = 0;

        virtual void OnImportFacebookFriendsSuccess() = 0;
        virtual void OnImportFacebookFriendsFailed(const Error& error) = 0;

        virtual void OnUnauthenticated() = 0;
    };

    using NakamaListenerNotificationBus = AZ::EBus<NakamaListenerNotifications>;

    class NakamaListenerNotificationHandler
        : public NakamaListenerNotificationBus::Handler
        , public AZ::BehaviorEBusHandler {
    public:
        AZ_EBUS_BEHAVIOR_BINDER(
            NakamaListenerNotificationHandler,
            "{9B3ABC85-8E49-44C7-9BF1-D2CC119DB8BF}",
            AZ::SystemAllocator, OnConnect, OnDisconnect, OnRtError, OnChannelMessage, OnChannelPresence, OnMatchmakerMatched, OnMatchData, OnMatchPresence, OnNotifications, OnParty, OnPartyClosed, OnPartyData, OnPartyJoinRequest, OnPartyLeader, OnPartyMatchmakerTicket, OnPartyPresence, OnStatusPresence, OnStreamPresence, OnStreamData, OnError,
            OnAuthenticateSuccess, OnAuthenticateFailed, OnLinkSuccess, OnLinkFailed, OnUnauthenticated, OnUnlinkSuccess, OnUnlinkFailed, OnImportFacebookFriendsSuccess, OnImportFacebookFriendsFailed
        );

        // �¼�ӳ��
        void OnConnect() override 
        {
            Call(FN_OnConnect);
        }

        void OnDisconnect(const RtClientDisconnectInfo& info) override 
        {
            Call(FN_OnDisconnect, info);
        }

        void OnRtError(const RtError& error) override 
        {
            Call(FN_OnRtError, error);
        }
        void OnChannelMessage(const ChannelMessage& message) override 
        {
            Call(FN_OnChannelMessage, message);
        }
        void OnChannelPresence(const ChannelPresenceEvent& presenceEvent) override 
        {
            Call(FN_OnChannelPresence, presenceEvent);
        }
        void OnMatchmakerMatched(const MatchmakerMatched& matched) override 
        {
            Call(FN_OnMatchmakerMatched, matched);
        }
        void OnMatchData(const MatchData& matchData) override 
        {
            Call(FN_OnMatchData, matchData);
        }
        void OnMatchPresence(const MatchPresenceEvent& matchPresence) override 
        {
            Call(FN_OnMatchPresence, matchPresence);
        }
        void OnNotifications(const NotificationList& notifications) override
        {
            Call(FN_OnNotifications, notifications);
        }
        void OnParty(const Party& party) override 
        {
            Call(FN_OnParty, party);
        }
        void OnPartyClosed(const PartyClose& partyClosed) override 
        {
            Call(FN_OnPartyClosed, partyClosed);
        }
        void OnPartyData(const PartyData& partyData) override 
        {
            Call(FN_OnPartyData, partyData);
        }
        void OnPartyJoinRequest(const PartyJoinRequest& partyJoinRequest) override 
        {
            Call(FN_OnPartyJoinRequest, partyJoinRequest);
        }
        void OnPartyLeader(const PartyLeader& partyLeader) override 
        {
            Call(FN_OnPartyLeader, partyLeader);
        }
        void OnPartyMatchmakerTicket(const PartyMatchmakerTicket& partyMatchmakerTicket) override 
        {
            Call(FN_OnPartyMatchmakerTicket, partyMatchmakerTicket);
        }
        void OnPartyPresence(const PartyPresenceEvent& partyPresence) override 
        {
            Call(FN_OnPartyPresence, partyPresence);
        }
        void OnStatusPresence(const StatusPresenceEvent& presenceEvent) override
        {
            Call(FN_OnStatusPresence, presenceEvent);
        }
        void OnStreamPresence(const StreamPresenceEvent& presenceEvent) override 
        {
            Call(FN_OnStreamPresence, presenceEvent);
        }
        void OnStreamData(const StreamData& data) override 
        {
            Call(FN_OnStreamData, data);
        }

        void OnError(const Error& error) override
        {
            Call(FN_OnError, error);
        }

        void OnAuthenticateSuccess(const AZStd::string& username, const AZStd::string& userId) override 
        {
            Call(FN_OnAuthenticateSuccess, username, userId);
        }
        void OnAuthenticateFailed(AZ::s8 code, const AZStd::string& message) override 
        { 
            Call(FN_OnAuthenticateFailed, code, message);
        }

        void OnLinkSuccess() override
        {
            Call(FN_OnLinkSuccess);
        }
        void OnLinkFailed(const Error& error) override
        {
            Call(FN_OnLinkFailed, error);
        }
        
        void OnUnauthenticated() override
        {
            Call(FN_OnUnauthenticated);
        }

        void OnUnlinkSuccess() override
        {
            Call(FN_OnUnlinkSuccess);
        }
        void OnUnlinkFailed(const Error& error) override
        {
            Call(FN_OnUnlinkFailed, error);
        }

        void OnImportFacebookFriendsSuccess() override
        {
            Call(FN_OnImportFacebookFriendsSuccess);
        }
        void OnImportFacebookFriendsFailed(const Error& error) override
        {
            Call(FN_OnImportFacebookFriendsFailed, error);
        }
    };

    class NakamaAccountNotifications
        : public AZ::EBusTraits
    {
    public:
        AZ_RTTI(NakamaClientGem::NakamaAccountNotifications, "{8BB9582B-9DB0-4F13-B72E-5A983A1340AF}");

        static const AZ::EBusHandlerPolicy HandlerPolicy = AZ::EBusHandlerPolicy::Multiple;

        virtual void OnGetAccountSuccess(const Account& account) = 0;
        virtual void OnGetAccountFailed(const Error& error) = 0;
        virtual void OnUpdateAccountSuccess(const AZStd::string& username, const AZStd::string& displayName, const AZStd::string& avatarUrl, const AZStd::string& langTag, const AZStd::string& location, const AZStd::string& timezone) = 0;
        virtual void OnUpdateAccountFailed(const Error& error) = 0;
        virtual void OnGetUsersSuccess(const AZStd::vector<User>& users) = 0;
        virtual void OnGetUsersFailed(const Error& error) = 0;
    };
    using NakamaAccountNotificationBus = AZ::EBus<NakamaAccountNotifications>;
    class NakamaAccountNotificationHandler
        : public NakamaAccountNotificationBus::Handler
        , public AZ::BehaviorEBusHandler {
    public:
        AZ_EBUS_BEHAVIOR_BINDER(
            NakamaAccountNotificationHandler,
            "{04C68A75-B0C1-4EFA-A8FF-D6DE2300F032}",
            AZ::SystemAllocator, OnGetAccountSuccess, OnGetAccountFailed, OnUpdateAccountSuccess, OnUpdateAccountFailed, OnGetUsersSuccess, OnGetUsersFailed);

        void OnGetAccountSuccess(const Account& account) override
        {
            Call(FN_OnGetAccountSuccess, account);
        }
        void OnGetAccountFailed(const Error& error) override
        {
            Call(FN_OnGetAccountFailed, error);
        }

        void OnUpdateAccountSuccess(const AZStd::string& username, const AZStd::string& displayName, const AZStd::string& avatarUrl, const AZStd::string& langTag, const AZStd::string& location, const AZStd::string& timezone) override
        {
            Call(FN_OnUpdateAccountSuccess, username, displayName, avatarUrl, langTag, location, timezone);
        }
        void OnUpdateAccountFailed(const Error& error) override
        {
            Call(FN_OnUpdateAccountFailed, error);
        }
        void OnGetUsersSuccess(const AZStd::vector<User>& users) override
        {
            Call(FN_OnGetUsersSuccess, users);
        }
        void OnGetUsersFailed(const Error& error) override
        {
            Call(FN_OnGetUsersFailed, error);
        }
    };

    class NakamaFriendsNotifications
        : public AZ::EBusTraits
    {
    public:
        AZ_RTTI(NakamaClientGem::NakamaFriendsNotifications, "{B095B68D-96A9-4D89-9C71-2ED54F3FD620}");

        static const AZ::EBusHandlerPolicy HandlerPolicy = AZ::EBusHandlerPolicy::Multiple;

        virtual void OnAddFriendsSuccess(const AZStd::vector<AZStd::string>& ids, const AZStd::vector<AZStd::string>& usernames) = 0;
        virtual void OnAddFriendsFailed(const Error& error) = 0;
        virtual void OnDeleteFriendsSuccess(const AZStd::vector<AZStd::string>& ids, const AZStd::vector<AZStd::string>& usernames) = 0;
        virtual void OnDeleteFriendsFailed(const Error& error) = 0;
        virtual void OnBlockFriendsSuccess(const AZStd::vector<AZStd::string>& ids, const AZStd::vector<AZStd::string>& usernames) = 0;
        virtual void OnBlockFriendsFailed(const Error& error) = 0;
        virtual void OnListFriendsSuccess(const AZStd::vector<Friend>& friends, AZ::s32 limit, AZ::u8 state, const AZStd::string& cursor) = 0;
        virtual void OnListFriendsFailed(const Error& error) = 0;
    };
    using NakamaFriendsNotificationBus = AZ::EBus<NakamaFriendsNotifications>;
    class NakamaFriendsNotificationHandler
        : public NakamaFriendsNotificationBus::Handler
        , public AZ::BehaviorEBusHandler {
    public:
        AZ_EBUS_BEHAVIOR_BINDER(
            NakamaFriendsNotificationHandler,
            "{2DB70277-1C75-44FB-8BB6-2E5321E94A46}",
            AZ::SystemAllocator, OnAddFriendsSuccess, OnAddFriendsFailed, OnDeleteFriendsSuccess, OnDeleteFriendsFailed, OnBlockFriendsSuccess, OnBlockFriendsFailed, OnListFriendsSuccess, OnListFriendsFailed);

        void OnAddFriendsSuccess(const AZStd::vector<AZStd::string>& ids, const AZStd::vector<AZStd::string>& usernames) override
        {
            Call(FN_OnAddFriendsSuccess, ids, usernames);
        }
        void OnAddFriendsFailed(const Error& error) override
        {
            Call(FN_OnAddFriendsFailed, error);
        }
        void OnDeleteFriendsSuccess(const AZStd::vector<AZStd::string>& ids, const AZStd::vector<AZStd::string>& usernames) override
        {
            Call(FN_OnDeleteFriendsSuccess, ids, usernames);
        }
        void OnDeleteFriendsFailed(const Error& error) override
        {
            Call(FN_OnDeleteFriendsFailed, error);
        }
        void OnBlockFriendsSuccess(const AZStd::vector<AZStd::string>& ids, const AZStd::vector<AZStd::string>& usernames) override
        {
            Call(FN_OnBlockFriendsSuccess, ids, usernames);
        }
        void OnBlockFriendsFailed(const Error& error) override
        {
            Call(FN_OnBlockFriendsFailed, error);
        }
        void OnListFriendsSuccess(const AZStd::vector<Friend>& friends, AZ::s32 limit, AZ::u8 state, const AZStd::string& cursor) override
        {
            Call(FN_OnListFriendsSuccess, friends, limit, state, cursor);
        }
        void OnListFriendsFailed(const Error& error) override
        {
            Call(FN_OnListFriendsFailed, error);
        }
    };

    class NakamaGroupsNotifications
        : public AZ::EBusTraits
    {
    public:
        AZ_RTTI(NakamaClientGem::NakamaGroupsNotifications, "{280F9CCC-E893-4DEC-9D88-1D464E808735}");

        static const AZ::EBusHandlerPolicy HandlerPolicy = AZ::EBusHandlerPolicy::Multiple;

        virtual void OnCreateGroupSuccess(const Group& group) = 0;
        virtual void OnCreateGroupFailed(const Error& error) = 0;
        virtual void OnDeleteGroupSuccess(const AZStd::string& groupId) = 0;
        virtual void OnDeleteGroupFailed(const Error& error) = 0;
        virtual void OnAddGroupUsersSuccess(const AZStd::string& groupId, const AZStd::vector<AZStd::string>& ids) = 0;
        virtual void OnAddGroupUsersFailed(const Error& error) = 0;
        virtual void OnListGroupUsersSuccess(const GroupUserList& users, const AZStd::string& groupId, AZ::s32 limit, AZ::u8 state, const AZStd::string& cursor) = 0;
        virtual void OnListGroupUsersFailed(const Error& error) = 0;
        virtual void OnKickGroupUsersSuccess(const AZStd::string& groupId, const AZStd::vector<AZStd::string>& ids) = 0;
        virtual void OnKickGroupUsersFailed(const Error& error) = 0;
        virtual void OnJoinGroupSuccess(const AZStd::string& groupId) = 0;
        virtual void OnJoinGroupFailed(const Error& error) = 0;
        virtual void OnLeaveGroupSuccess(const AZStd::string& groupId) = 0;
        virtual void OnLeaveGroupFailed(const Error& error) = 0;
        virtual void OnListGroupsSuccess(const GroupList& groups, const AZStd::string& name, AZ::s32 limit, const AZStd::string& cursor) = 0;
        virtual void OnListGroupsFailed(const Error& error) = 0;
        virtual void OnListUserGroupsSuccess(const UserGroupList& groups, AZ::s32 limit, AZ::u8 state, const AZStd::string& cursor) = 0;
        virtual void OnListUserGroupsFailed(const Error& error) = 0;
        virtual void OnListUserGroupsWithIdSuccess(const UserGroupList& groups, const AZStd::string& userId, AZ::s32 limit, AZ::u8 state, const AZStd::string& cursor) = 0;
        virtual void OnListUserGroupsWithIdFailed(const Error& error) = 0;
        virtual void OnPromoteGroupUsersSuccess(const AZStd::string& groupId, const AZStd::vector<AZStd::string>& ids) = 0;
        virtual void OnPromoteGroupUsersFailed(const Error& error) = 0;
        virtual void OnDemoteGroupUsersSuccess(const AZStd::string& groupId, const AZStd::vector<AZStd::string>& ids) = 0;
        virtual void OnDemoteGroupUsersFailed(const Error& error) = 0;
        virtual void OnUpdateGroupSuccess(const AZStd::string& groupId, const AZStd::string& name, const AZStd::string& description, const AZStd::string& avatarUrl, const AZStd::string& langTag, bool open) = 0;
        virtual void OnUpdateGroupFailed(const Error& error) = 0;
    };
    using NakamaGroupsNotificationBus = AZ::EBus<NakamaGroupsNotifications>;
    class NakamaGroupsNotificationHandler
        : public NakamaGroupsNotificationBus::Handler
        , public AZ::BehaviorEBusHandler {
    public:
        AZ_EBUS_BEHAVIOR_BINDER(
            NakamaGroupsNotificationHandler,
            "{52EF4651-DBEE-40FD-9CE7-DE7D8BC83FED}",
        AZ::SystemAllocator, OnCreateGroupSuccess, OnCreateGroupFailed, OnDeleteGroupSuccess, OnDeleteGroupFailed, OnAddGroupUsersSuccess, OnAddGroupUsersFailed, OnListGroupUsersSuccess, OnListGroupUsersFailed, OnKickGroupUsersSuccess, OnKickGroupUsersFailed, OnJoinGroupSuccess, OnJoinGroupFailed, OnLeaveGroupSuccess, OnLeaveGroupFailed, OnListGroupsSuccess, OnListGroupsFailed, OnListUserGroupsSuccess, OnListUserGroupsFailed, OnListUserGroupsWithIdSuccess, OnListUserGroupsWithIdFailed, OnPromoteGroupUsersSuccess, OnPromoteGroupUsersFailed, OnDemoteGroupUsersSuccess, OnDemoteGroupUsersFailed, OnUpdateGroupSuccess, OnUpdateGroupFailed);


        void OnCreateGroupSuccess(const Group& group) override
        {
            Call(FN_OnCreateGroupSuccess, group);
        }
        void OnCreateGroupFailed(const Error& error) override
        {
            Call(FN_OnCreateGroupFailed, error);
        }
        void OnDeleteGroupSuccess(const AZStd::string& groupId) override
        {
            Call(FN_OnDeleteGroupSuccess, groupId);
        }
        void OnDeleteGroupFailed(const Error& error) override
        {
            Call(FN_OnDeleteGroupFailed, error);
        }
        void OnAddGroupUsersSuccess(const AZStd::string& groupId, const AZStd::vector<AZStd::string>& ids) override
        {
            Call(FN_OnAddGroupUsersSuccess, groupId, ids);
        }
        void OnAddGroupUsersFailed(const Error& error) override
        {
            Call(FN_OnAddGroupUsersFailed, error);
        }
        void OnListGroupUsersSuccess(const GroupUserList& users, const AZStd::string& groupId, AZ::s32 limit, AZ::u8 state, const AZStd::string& cursor) override
        {
            Call(FN_OnListGroupUsersSuccess, users, groupId, limit, state, cursor);
        }
        void OnListGroupUsersFailed(const Error& error) override
        {
            Call(FN_OnListGroupUsersFailed, error);
        }
        void OnKickGroupUsersSuccess(const AZStd::string& groupId, const AZStd::vector<AZStd::string>& ids) override
        {
            Call(FN_OnKickGroupUsersSuccess, groupId, ids);
        }
        void OnKickGroupUsersFailed(const Error& error) override
        {
            Call(FN_OnKickGroupUsersFailed, error);
        }
        void OnJoinGroupSuccess(const AZStd::string& groupId) override
        {
            Call(FN_OnJoinGroupSuccess, groupId);
        }
        void OnJoinGroupFailed(const Error& error) override
        {
            Call(FN_OnJoinGroupFailed, error);
        }
        void OnLeaveGroupSuccess(const AZStd::string& groupId) override
        {
            Call(FN_OnLeaveGroupSuccess, groupId);
        }
        void OnLeaveGroupFailed(const Error& error) override
        {
            Call(FN_OnLeaveGroupFailed, error);
        }
        void OnListGroupsSuccess(const GroupList& groups, const AZStd::string& name, AZ::s32 limit, const AZStd::string& cursor) override
        {
            Call(FN_OnListGroupsSuccess, groups, name, limit, cursor);
        }
        void OnListGroupsFailed(const Error& error) override
        {
            Call(FN_OnListGroupsFailed, error);
        }
        void OnListUserGroupsSuccess(const UserGroupList& groups, AZ::s32 limit, AZ::u8 state, const AZStd::string& cursor) override
        {
            Call(FN_OnListUserGroupsSuccess, groups, limit, state, cursor);
        }
        void OnListUserGroupsFailed(const Error& error) override
        {
            Call(FN_OnListUserGroupsFailed, error);
        }
        void OnListUserGroupsWithIdSuccess(const UserGroupList& groups, const AZStd::string& userId, AZ::s32 limit, AZ::u8 state, const AZStd::string& cursor) override
        {
            Call(FN_OnListUserGroupsWithIdSuccess, groups, userId, limit, state, cursor);
        }
        void OnListUserGroupsWithIdFailed(const Error& error) override
        {
            Call(FN_OnListUserGroupsWithIdFailed, error);
        }
        void OnPromoteGroupUsersSuccess(const AZStd::string& groupId, const AZStd::vector<AZStd::string>& ids) override
        {
            Call(FN_OnPromoteGroupUsersSuccess, groupId, ids);
        }
        void OnPromoteGroupUsersFailed(const Error& error) override
        {
            Call(FN_OnPromoteGroupUsersFailed, error);
        }
        void OnDemoteGroupUsersSuccess(const AZStd::string& groupId, const AZStd::vector<AZStd::string>& ids) override
        {
            Call(FN_OnDemoteGroupUsersSuccess, groupId, ids);
        }
        void OnDemoteGroupUsersFailed(const Error& error) override
        {
            Call(FN_OnDemoteGroupUsersFailed, error);
        }
        void OnUpdateGroupSuccess(const AZStd::string& groupId, const AZStd::string& name, const AZStd::string& description, const AZStd::string& avatarUrl, const AZStd::string& langTag, bool open) override
        {
            Call(FN_OnUpdateGroupSuccess, groupId, name, description, avatarUrl, langTag, open);
        }
        void OnUpdateGroupFailed(const Error& error) override
        {
            Call(FN_OnUpdateGroupFailed, error);
        }
    };

    class NakamaLeaderboardsNotifications
        : public AZ::EBusTraits
    {
    public:
        AZ_RTTI(NakamaClientGem::NakamaLeaderboardsNotifications, "{F912E45B-32D2-4E40-ACA7-D82FC1EA8656}");

        static const AZ::EBusHandlerPolicy HandlerPolicy = AZ::EBusHandlerPolicy::Multiple;

        virtual void OnListLeaderboardRecordsSuccess(const LeaderboardRecordList& records, const AZStd::string& leaderboardId, const AZStd::vector<AZStd::string>& ownerIds, AZ::s32 limit, const AZStd::string& cursor) = 0;
        virtual void OnListLeaderboardRecordsFailed(const Error& error) = 0;
        virtual void OnListLeaderboardRecordsAroundOwnerSuccess(const LeaderboardRecordList& records, const AZStd::string& leaderboardId, const AZStd::string& ownerId, AZ::s32 limit) = 0;
        virtual void OnListLeaderboardRecordsAroundOwnerFailed(const Error& error) = 0;
        virtual void OnWriteLeaderboardRecordSuccess(const LeaderboardRecord& record, const AZStd::string& leaderboardId, AZ::s64 score, AZ::s64 subscore, AZStd::string metadata) = 0;
        virtual void OnWriteLeaderboardRecordFailed(const Error& error) = 0;
        virtual void OnDeleteLeaderboardRecordSuccess(const AZStd::string& leaderboardId) = 0;
        virtual void OnDeleteLeaderboardRecordFailed(const Error& error) = 0;
    };
    using NakamaLeaderboardsNotificationBus = AZ::EBus<NakamaLeaderboardsNotifications>;
    class NakamaLeaderboardsNotificationHandler
        : public NakamaLeaderboardsNotificationBus::Handler
        , public AZ::BehaviorEBusHandler {
    public:
        AZ_EBUS_BEHAVIOR_BINDER(
            NakamaLeaderboardsNotificationHandler,
            "{EAEDBEBD-11CA-43A5-A9D8-39A3F6330DA6}",
            AZ::SystemAllocator, OnListLeaderboardRecordsSuccess, OnListLeaderboardRecordsFailed, OnListLeaderboardRecordsAroundOwnerSuccess, OnListLeaderboardRecordsAroundOwnerFailed, OnWriteLeaderboardRecordSuccess, OnWriteLeaderboardRecordFailed, OnDeleteLeaderboardRecordSuccess, OnDeleteLeaderboardRecordFailed);


        void OnListLeaderboardRecordsSuccess(const LeaderboardRecordList& records, const AZStd::string& leaderboardId, const AZStd::vector<AZStd::string>& ownerIds, AZ::s32 limit, const AZStd::string& cursor) override
        {
            Call(FN_OnListLeaderboardRecordsSuccess, records, leaderboardId, ownerIds, limit, cursor);
        }
        void OnListLeaderboardRecordsFailed(const Error& error) override
        {
            Call(FN_OnListLeaderboardRecordsFailed, error);
        }
        void OnListLeaderboardRecordsAroundOwnerSuccess(const LeaderboardRecordList& records, const AZStd::string& leaderboardId, const AZStd::string& ownerId, AZ::s32 limit) override
        {
            Call(FN_OnListLeaderboardRecordsAroundOwnerSuccess, records, leaderboardId, ownerId, limit);
        }
        void OnListLeaderboardRecordsAroundOwnerFailed(const Error& error) override
        {
            Call(FN_OnListLeaderboardRecordsAroundOwnerFailed, error);
        }
        void OnWriteLeaderboardRecordSuccess(const LeaderboardRecord& record, const AZStd::string& leaderboardId, AZ::s64 score, AZ::s64 subscore, AZStd::string metadata) override
        {
            Call(FN_OnWriteLeaderboardRecordSuccess, record, leaderboardId, score, subscore, metadata);
        }
        void OnWriteLeaderboardRecordFailed(const Error& error) override
        {
            Call(FN_OnWriteLeaderboardRecordFailed, error);
        }
        void OnDeleteLeaderboardRecordSuccess(const AZStd::string& leaderboardId) override
        {
            Call(FN_OnDeleteLeaderboardRecordSuccess, leaderboardId);
        }
        void OnDeleteLeaderboardRecordFailed(const Error& error) override
        {
            Call(FN_OnDeleteLeaderboardRecordFailed, error);
        }
    };

    class NakamaTournamentsNotifications
        : public AZ::EBusTraits
    {
    public:
        AZ_RTTI(NakamaClientGem::NakamaTournamentsNotifications, "{556EE110-E0C0-4446-A69D-738CA04635B9}");

        static const AZ::EBusHandlerPolicy HandlerPolicy = AZ::EBusHandlerPolicy::Multiple;

        virtual void OnWriteTournamentRecordSuccess(const LeaderboardRecord& record) = 0;
        virtual void OnWriteTournamentRecordFailed(const Error& error) = 0;
        virtual void OnListTournamentsSuccess(const TournamentList& tournaments, AZ::u32 categoryStart, AZ::u32 categoryEnd, AZ::u32 startTime, AZ::u32 endTime, AZ::s32 limit, const AZStd::string& cursor) = 0;
        virtual void OnListTournamentsFailed(const Error& error) = 0;
        virtual void OnListTournamentRecordsSuccess(const TournamentRecordList& records, const AZStd::string& tournamentId, AZ::s32 limit, const AZStd::string& cursor, const AZStd::vector<AZStd::string>& ownerIds) = 0;
        virtual void OnListTournamentRecordsFailed(const Error& error) = 0;
        virtual void OnListTournamentRecordsAroundOwnerSuccess(const TournamentRecordList& records, const AZStd::string& tournamentId, const AZStd::string& ownerId, AZ::s32 limit) = 0;
        virtual void OnListTournamentRecordsAroundOwnerFailed(const Error& error) = 0;
        virtual void OnJoinTournamentSuccess(const AZStd::string& tournamentId) = 0;
        virtual void OnJoinTournamentFailed(const Error& error) = 0;
    };
    using NakamaTournamentsNotificationBus = AZ::EBus<NakamaTournamentsNotifications>;
    class NakamaTournamentsNotificationHandler
        : public NakamaTournamentsNotificationBus::Handler
        , public AZ::BehaviorEBusHandler {
    public:
        AZ_EBUS_BEHAVIOR_BINDER(
            NakamaTournamentsNotificationHandler,
            "{30A1E048-513C-485E-8D0F-1EA379450C0B}",
            AZ::SystemAllocator, OnWriteTournamentRecordSuccess, OnWriteTournamentRecordFailed, OnListTournamentsSuccess, OnListTournamentsFailed, OnListTournamentRecordsSuccess, OnListTournamentRecordsFailed, OnListTournamentRecordsAroundOwnerSuccess, OnListTournamentRecordsAroundOwnerFailed, OnJoinTournamentSuccess, OnJoinTournamentFailed);

        void OnWriteTournamentRecordSuccess(const LeaderboardRecord& record) override
        {
            Call(FN_OnWriteTournamentRecordSuccess, record);
        }
        void OnWriteTournamentRecordFailed(const Error& error) override
        {
            Call(FN_OnWriteTournamentRecordFailed, error);
        }
        void OnListTournamentsSuccess(const TournamentList& tournaments, AZ::u32 categoryStart, AZ::u32 categoryEnd, AZ::u32 startTime, AZ::u32 endTime, AZ::s32 limit, const AZStd::string& cursor) override
        {
            Call(FN_OnListTournamentsSuccess, tournaments, categoryStart, categoryEnd, startTime, endTime, limit, cursor);
        }
        void OnListTournamentsFailed(const Error& error) override
        {
            Call(FN_OnListTournamentsFailed, error);
        }
        void OnListTournamentRecordsSuccess(const TournamentRecordList& records, const AZStd::string& tournamentId, AZ::s32 limit, const AZStd::string& cursor, const AZStd::vector<AZStd::string>& ownerIds) override
        {
            Call(FN_OnListTournamentRecordsSuccess, records, tournamentId, limit, cursor, ownerIds);
        }
        void OnListTournamentRecordsFailed(const Error& error) override
        {
            Call(FN_OnListTournamentRecordsFailed, error);
        }
        void OnListTournamentRecordsAroundOwnerSuccess(const TournamentRecordList& records, const AZStd::string& tournamentId, const AZStd::string& ownerId, AZ::s32 limit) override
        {
            Call(FN_OnListTournamentRecordsAroundOwnerSuccess, records, tournamentId, ownerId, limit);
        }
        void OnListTournamentRecordsAroundOwnerFailed(const Error& error) override
        {
            Call(FN_OnListTournamentRecordsAroundOwnerFailed, error);
        }
        void OnJoinTournamentSuccess(const AZStd::string& tournamentId) override
        {
            Call(FN_OnJoinTournamentSuccess, tournamentId);
        }
        void OnJoinTournamentFailed(const Error& error) override
        {
            Call(FN_OnJoinTournamentFailed, error);
        }
    };

    class NakamaMatchesNotifications
        : public AZ::EBusTraits
    {
    public:
        AZ_RTTI(NakamaClientGem::NakamaMatchesNotifications, "{6BDF262A-BD27-4A3B-8743-A01C4447300D}");

        static const AZ::EBusHandlerPolicy HandlerPolicy = AZ::EBusHandlerPolicy::Multiple;

        virtual void OnRtClientNotConnected() = 0;
        virtual void OnListMatchesSuccess(const MatchList& matchList, AZ::s32 min_size, AZ::s32 max_size, AZ::s32 limit, const AZStd::string& label, const AZStd::string& query, bool authoritative) = 0;
        virtual void OnListMatchesFailed(const Error& error) = 0;
        virtual void OnCreateMatchSuccess(const Match& match) = 0;
        virtual void OnCreateMatchFailed(const RtError& error) = 0;
        virtual void OnJoinMatchSuccess(const Match& match) = 0;
        virtual void OnJoinMatchFailed(const RtError& error) = 0;
        virtual void OnJoinMatchByTokenSuccess(const Match& match) = 0;
        virtual void OnJoinMatchByTokenFailed(const RtError& error) = 0;
        virtual void OnLeaveMatchSuccess(const AZStd::string& matchId) = 0;
        virtual void OnLeaveMatchFailed(const RtError& error) = 0;
    };
    using NakamaMatchesNotificationBus = AZ::EBus<NakamaMatchesNotifications>;
    class NakamaMatchesNotificationHandler
        : public NakamaMatchesNotificationBus::Handler
        , public AZ::BehaviorEBusHandler {
    public:
        AZ_EBUS_BEHAVIOR_BINDER(
            NakamaMatchesNotificationHandler,
            "{F57649CC-57F5-42C2-99B8-EA79F77D41D9}",
            AZ::SystemAllocator, OnRtClientNotConnected, OnListMatchesSuccess, OnListMatchesFailed, OnCreateMatchSuccess, OnCreateMatchFailed, OnJoinMatchSuccess, OnJoinMatchFailed, OnJoinMatchByTokenSuccess, OnJoinMatchByTokenFailed, OnLeaveMatchSuccess, OnLeaveMatchFailed);

		void OnRtClientNotConnected() override
		{
			Call(FN_OnRtClientNotConnected);
		}
        void OnListMatchesSuccess(const MatchList& matchList, AZ::s32 min_size, AZ::s32 max_size, AZ::s32 limit, const AZStd::string& label, const AZStd::string& query, bool authoritative) override
		{
			Call(FN_OnListMatchesSuccess, matchList, min_size, max_size, limit, label, query, authoritative);
		}
        void OnListMatchesFailed(const Error& error) override
        {
			Call(FN_OnListMatchesFailed, error);
        }
        void OnCreateMatchSuccess(const Match& match) override
        {
			Call(FN_OnCreateMatchSuccess, match);
        }
        void OnCreateMatchFailed(const RtError& error) override
        {
			Call(FN_OnCreateMatchFailed, error);
        }
        void OnJoinMatchSuccess(const Match& match) override
        {
			Call(FN_OnJoinMatchSuccess, match);
        }
        void OnJoinMatchFailed(const RtError& error) override
        {
			Call(FN_OnJoinMatchFailed, error);
        }
        void OnJoinMatchByTokenSuccess(const Match& match) override
		{
			Call(FN_OnJoinMatchByTokenSuccess, match);
		}
        void OnJoinMatchByTokenFailed(const RtError& error) override
        {
			Call(FN_OnJoinMatchByTokenFailed, error);
        }
        void OnLeaveMatchSuccess(const AZStd::string& matchId) override
        {
			Call(FN_OnLeaveMatchSuccess, matchId);
        }
        void OnLeaveMatchFailed(const RtError& error) override
        {
            Call(FN_OnLeaveMatchFailed, error);
        }
    };

    class NakamaNotificationsNotifications
        : public AZ::EBusTraits
    {
    public:
        AZ_RTTI(NakamaClientGem::NakamaNotificationsNotifications, "{EC4E654C-0D78-4535-B966-C284BC8DC715}");

        static const AZ::EBusHandlerPolicy HandlerPolicy = AZ::EBusHandlerPolicy::Multiple;

        virtual void OnListNotificationsSuccess(const NotificationList& notifications, AZ::s32 limit, const AZStd::string& cacheableCursor) = 0;
        virtual void OnListNotificationsFailed(const Error& error) = 0;
        virtual void OnDeleteNotificationsSuccess(const AZStd::vector<AZStd::string>& notificationIds) = 0;
        virtual void OnDeleteNotificationsFailed(const Error& error) = 0;
    };
    using NakamaNotificationsNotificationBus = AZ::EBus<NakamaNotificationsNotifications>;
    class NakamaNotificationsNotificationHandler
        : public NakamaNotificationsNotificationBus::Handler
        , public AZ::BehaviorEBusHandler {
    public:
        AZ_EBUS_BEHAVIOR_BINDER(
            NakamaNotificationsNotificationHandler,
            "{6AB0487E-2AA6-4B8C-B198-3E2CE1F31331}",
            AZ::SystemAllocator, OnListNotificationsSuccess, OnListNotificationsFailed, OnDeleteNotificationsSuccess, OnDeleteNotificationsFailed);

        void OnListNotificationsSuccess(const NotificationList& notifications, AZ::s32 limit, const AZStd::string& cacheableCursor) override
        {
            Call(FN_OnListNotificationsSuccess, notifications, limit, cacheableCursor);
        }
		void OnListNotificationsFailed(const Error& error) override
		{
			Call(FN_OnListNotificationsFailed, error);
		}
        void OnDeleteNotificationsSuccess(const AZStd::vector<AZStd::string>& notificationIds) override
        {
			Call(FN_OnDeleteNotificationsSuccess, notificationIds);
        }
        void OnDeleteNotificationsFailed(const Error& error) override
        {
			Call(FN_OnDeleteNotificationsFailed, error);
        }
    };

    class NakamaChatNotifications
        : public AZ::EBusTraits
    {
    public:
        AZ_RTTI(NakamaClientGem::NakamaChatNotifications, "{F4F44426-D4B8-4A3D-8D5E-7F65BD3E35BE}");

        static const AZ::EBusHandlerPolicy HandlerPolicy = AZ::EBusHandlerPolicy::Multiple;

        virtual void OnListChannelMessagesSuccess(const ChannelMessageList& messageList) = 0;
        virtual void OnListChannelMessagesFailed(const Error& error) = 0;
        virtual void OnJoinChatSuccess(const Channel& channel) = 0;
        virtual void OnJoinChatFailed(const RtError& error) = 0;
        virtual void OnLeaveChatSuccess(const AZStd::string& channelId) = 0;
        virtual void OnLeaveChatFailed(const RtError& error) = 0;
        virtual void OnWriteChatMessageSuccess(const ChannelMessageAck& ack) = 0;
        virtual void OnWriteChatMessageFailed(const RtError& error) = 0;
        virtual void OnUpdateChatMessageSuccess(const ChannelMessageAck& ack) = 0;
        virtual void OnUpdateChatMessageFailed(const RtError& error) = 0;
        virtual void OnRemoveChatMessageSuccess(const ChannelMessageAck& ack) = 0;
        virtual void OnRemoveChatMessageFailed(const RtError& error) = 0;
    };
    using NakamaChatNotificationBus = AZ::EBus<NakamaChatNotifications>;
    class NakamaChatNotificationHandler
        : public NakamaChatNotificationBus::Handler
        , public AZ::BehaviorEBusHandler {
    public:
        AZ_EBUS_BEHAVIOR_BINDER(
            NakamaChatNotificationHandler,
            "{E1BCB48C-463C-4B06-AC84-9F73F3E842D0}",
            AZ::SystemAllocator, OnListChannelMessagesSuccess, OnListChannelMessagesFailed, OnJoinChatSuccess, OnJoinChatFailed, OnLeaveChatSuccess, OnLeaveChatFailed, OnWriteChatMessageSuccess, OnWriteChatMessageFailed, OnUpdateChatMessageSuccess, OnUpdateChatMessageFailed, OnRemoveChatMessageSuccess, OnRemoveChatMessageFailed);

        void OnListChannelMessagesSuccess(const ChannelMessageList& messageList) override
        {
            Call(FN_OnListChannelMessagesSuccess, messageList);
        }
		void OnListChannelMessagesFailed(const Error& error) override
		{
			Call(FN_OnListChannelMessagesFailed, error);
		}
		void OnJoinChatSuccess(const Channel& channel) override
		{
			Call(FN_OnJoinChatSuccess, channel);
		}
		void OnJoinChatFailed(const RtError& error) override
		{
			Call(FN_OnJoinChatFailed, error);
		}
		void OnLeaveChatSuccess(const AZStd::string& channelId) override
		{
			Call(FN_OnLeaveChatSuccess, channelId);
		}
		void OnLeaveChatFailed(const RtError& error) override
		{
			Call(FN_OnLeaveChatFailed, error);
		}
		void OnWriteChatMessageSuccess(const ChannelMessageAck& ack) override
		{
			Call(FN_OnWriteChatMessageSuccess, ack);
		}
		void OnWriteChatMessageFailed(const RtError& error) override
		{
			Call(FN_OnWriteChatMessageFailed, error);
		}
		void OnUpdateChatMessageSuccess(const ChannelMessageAck& ack) override
		{
			Call(FN_OnUpdateChatMessageSuccess, ack);
		}
		void OnUpdateChatMessageFailed(const RtError& error) override
		{
			Call(FN_OnUpdateChatMessageFailed, error);
		}
		void OnRemoveChatMessageSuccess(const ChannelMessageAck& ack) override
		{
			Call(FN_OnRemoveChatMessageSuccess, ack);
		}
		void OnRemoveChatMessageFailed(const RtError& error) override
		{
			Call(FN_OnRemoveChatMessageFailed, error);
		}
    };

    class NakamaStorageObjectsNotifications
        : public AZ::EBusTraits
    {
    public:
        AZ_RTTI(NakamaClientGem::NakamaStorageObjectsNotifications, "{368A4B50-AC04-4A2A-B52F-EAB84B7D2CE1}");

        static const AZ::EBusHandlerPolicy HandlerPolicy = AZ::EBusHandlerPolicy::Multiple;

        virtual void OnListStorageObjectsSuccess(const StorageObjectList& objectList) = 0;
        virtual void OnListStorageObjectsFailed(const Error& error) = 0;
        virtual void OnListUsersStorageObjectsSuccess(const StorageObjectList& objectList) = 0;
        virtual void OnListUsersStorageObjectsFailed(const Error& error) = 0;
        virtual void OnWriteStorageObjectsSuccess(const AZStd::vector<StorageObjectAck>& objectAcks) = 0;
        virtual void OnWriteStorageObjectsFailed(const Error& error) = 0;
        virtual void OnReadStorageObjectsSuccess(const AZStd::vector<StorageObject>& objects) = 0;
        virtual void OnReadStorageObjectsFailed(const Error& error) = 0;
        virtual void OnDeleteStorageObjectsSuccess(const AZStd::vector<DeleteStorageObjectId>& objectIds) = 0;
        virtual void OnDeleteStorageObjectsFailed(const Error& error) = 0;
    };
    using NakamaStorageObjectsNotificationBus = AZ::EBus<NakamaStorageObjectsNotifications>;
    class NakamaStorageObjectsNotificationHandler
        : public NakamaStorageObjectsNotificationBus::Handler
        , public AZ::BehaviorEBusHandler {
    public:
        AZ_EBUS_BEHAVIOR_BINDER(
            NakamaStorageObjectsNotificationHandler,
            "{4035B7AE-E793-4016-9805-B6D3F621611E}",
            AZ::SystemAllocator, OnListStorageObjectsSuccess, OnListStorageObjectsFailed, OnListUsersStorageObjectsSuccess, OnListUsersStorageObjectsFailed, OnWriteStorageObjectsSuccess, OnWriteStorageObjectsFailed, OnReadStorageObjectsSuccess, OnReadStorageObjectsFailed, OnDeleteStorageObjectsSuccess, OnDeleteStorageObjectsFailed);

        void OnListStorageObjectsSuccess(const StorageObjectList& objectList) override
        {
			Call(FN_OnListStorageObjectsSuccess, objectList);
        }
        void OnListStorageObjectsFailed(const Error& error) override
        {
			Call(FN_OnListStorageObjectsFailed, error);
        }
        void OnListUsersStorageObjectsSuccess(const StorageObjectList& objectList) override
        {
			Call(FN_OnListUsersStorageObjectsSuccess, objectList);
        }
        void OnListUsersStorageObjectsFailed(const Error& error) override
        {
			Call(FN_OnListUsersStorageObjectsFailed, error);
        }
        void OnWriteStorageObjectsSuccess(const AZStd::vector<StorageObjectAck>& objectAcks) override
        {
			Call(FN_OnWriteStorageObjectsSuccess, objectAcks);
        }
        void OnWriteStorageObjectsFailed(const Error& error) override
        {
			Call(FN_OnWriteStorageObjectsFailed, error);
        }
        void OnReadStorageObjectsSuccess(const AZStd::vector<StorageObject>& objects) override
        {
			Call(FN_OnReadStorageObjectsSuccess, objects);
        }
        void OnReadStorageObjectsFailed(const Error& error) override
        {
			Call(FN_OnReadStorageObjectsFailed, error);
        }
        void OnDeleteStorageObjectsSuccess(const AZStd::vector<DeleteStorageObjectId>& objectIds) override
        {
			Call(FN_OnDeleteStorageObjectsSuccess, objectIds);
        }
        void OnDeleteStorageObjectsFailed(const Error& error) override
        {
			Call(FN_OnDeleteStorageObjectsFailed, error);
        }
    };

    class NakamaRpcNotifications
        : public AZ::EBusTraits
    {
    public:
        AZ_RTTI(NakamaClientGem::NakamaRpcNotifications, "{D0AB1B01-30BB-461E-AA1D-8350E2D1F5D5}");

        static const AZ::EBusHandlerPolicy HandlerPolicy = AZ::EBusHandlerPolicy::Multiple;

        virtual void OnRpcSuccess(const Rpc& rpc) = 0;
        virtual void OnRpcFailed(const Error& error) = 0;
        virtual void OnRpcWithIdSuccess(const Rpc& rpc) = 0;
        virtual void OnRpcWithIdFailed(const Error& error) = 0;
        virtual void OnRtRpcSuccess(const Rpc& rpc) = 0;
        virtual void OnRtRpcFailed(const RtError& error) = 0;
    };
    using NakamaRpcNotificationBus = AZ::EBus<NakamaRpcNotifications>;
    class NakamaRpcNotificationHandler
        : public NakamaRpcNotificationBus::Handler
        , public AZ::BehaviorEBusHandler {
    public:
        AZ_EBUS_BEHAVIOR_BINDER(
            NakamaRpcNotificationHandler,
            "{F00F49BE-52BA-489A-9D34-8AB3586C8A89}",
            AZ::SystemAllocator, OnRpcSuccess, OnRpcFailed, OnRpcWithIdSuccess, OnRpcWithIdFailed, OnRtRpcSuccess, OnRtRpcFailed);

        void OnRpcSuccess(const Rpc& rpc) override
        {
            Call(FN_OnRpcSuccess, rpc);
        }
        void OnRpcFailed(const Error& error) override
        {
			Call(FN_OnRpcFailed, error);
        }
        void OnRpcWithIdSuccess(const Rpc& rpc) override
        {
            Call(FN_OnRpcWithIdSuccess, rpc);
        }
        void OnRpcWithIdFailed(const Error& error) override
        {
            Call(FN_OnRpcWithIdFailed, error);
        }
		void OnRtRpcSuccess(const Rpc& rpc) override
		{
			Call(FN_OnRtRpcSuccess, rpc);
		}
        void OnRtRpcFailed(const RtError& error) override
        {
            Call(FN_OnRtRpcFailed, error);
        }
    };

    class NakamaMatchmakerNotifications
        : public AZ::EBusTraits
    {
    public:
        AZ_RTTI(NakamaClientGem::NakamaMatchmakerNotifications, "{3106A3C0-DF4E-4477-A659-2CFC2C1F6DDF}");

        static const AZ::EBusHandlerPolicy HandlerPolicy = AZ::EBusHandlerPolicy::Multiple;

        virtual void OnAddMatchmakerSuccess(const AZStd::string& ticket) = 0;
        virtual void OnAddMatchmakerFailed(const RtError& error) = 0;
        virtual void OnRemoveMatchmakerSuccess(const AZStd::string& ticket) = 0;
        virtual void OnRemoveMatchmakerFailed(const RtError& error) = 0;
    };
    using NakamaMatchmakerNotificationBus = AZ::EBus<NakamaMatchmakerNotifications>;
    class NakamaMatchmakerNotificationHandler
        : public NakamaMatchmakerNotificationBus::Handler
        , public AZ::BehaviorEBusHandler {
    public:
        AZ_EBUS_BEHAVIOR_BINDER(
            NakamaMatchmakerNotificationHandler,
            "{A43A3233-E5E5-4DAB-AC07-AD8C3E7D268A}",
            AZ::SystemAllocator, OnAddMatchmakerSuccess, OnAddMatchmakerFailed, OnRemoveMatchmakerSuccess, OnRemoveMatchmakerFailed);

        void OnAddMatchmakerSuccess(const AZStd::string& ticket) override
        {
			Call(FN_OnAddMatchmakerSuccess, ticket);
        }
        void OnAddMatchmakerFailed(const RtError& error) override
        {
			Call(FN_OnAddMatchmakerFailed, error);
        }
        void OnRemoveMatchmakerSuccess(const AZStd::string& ticket) override
        {
			Call(FN_OnRemoveMatchmakerSuccess, ticket);
        }
        void OnRemoveMatchmakerFailed(const RtError& error) override
        {
			Call(FN_OnRemoveMatchmakerFailed, error);
        }
    };

    class NakamaPartyNotifications
        : public AZ::EBusTraits
    {
    public:
        AZ_RTTI(NakamaClientGem::NakamaPartyNotifications, "{C21A0FE9-71FF-41BD-B714-F3B7A715F36F}");

        static const AZ::EBusHandlerPolicy HandlerPolicy = AZ::EBusHandlerPolicy::Multiple;

        virtual void OnFollowUsersSuccess(const AZStd::vector<UserPresence>& presences) = 0;
        virtual void OnFollowUsersFailed(const RtError& error) = 0;
        virtual void OnUnfollowUsersSuccess(const AZStd::vector<AZStd::string>& userIds) = 0;
        virtual void OnUnfollowUsersFailed(const RtError& error) = 0;
        virtual void OnUpdateStatusSuccess(const AZStd::string& status) = 0;
        virtual void OnUpdateStatusFailed(const RtError& error) = 0;
        virtual void OnAcceptPartyMemberSuccess(const AZStd::string& partyId, const UserPresence& presence) = 0;
        virtual void OnAcceptPartyMemberFailed(const RtError& error) = 0;
        virtual void OnAddMatchmakerPartySuccess(const PartyMatchmakerTicket& ticket) = 0;
        virtual void OnAddMatchmakerPartyFailed(const RtError& error) = 0;
        virtual void OnClosePartySuccess(const AZStd::string& partyId) = 0;
        virtual void OnClosePartyFailed(const RtError& error) = 0;
        virtual void OnCreatePartySuccess(const Party& party) = 0;
        virtual void OnCreatePartyFailed(const RtError& error) = 0;
        virtual void OnJoinPartySuccess(const AZStd::string& partyId) = 0;
        virtual void OnJoinPartyFailed(const RtError& error) = 0;
        virtual void OnLeavePartySuccess(const AZStd::string& partyId) = 0;
        virtual void OnLeavePartyFailed(const RtError& error) = 0;
        virtual void OnListPartyJoinRequestsSuccess(const PartyJoinRequest& request) = 0;
        virtual void OnListPartyJoinRequestsFailed(const RtError& error) = 0;
        virtual void OnPromotePartyMemberSuccess(const AZStd::string& partyId, const UserPresence& partyMember) = 0;
        virtual void OnPromotePartyMemberFailed(const RtError& error) = 0;
        virtual void OnRemoveMatchmakerPartySuccess(const AZStd::string& partyId, const AZStd::string& ticket) = 0;
        virtual void OnRemoveMatchmakerPartyFailed(const RtError& error) = 0;
        virtual void OnRemovePartyMemberSuccess(const AZStd::string& partyId, const UserPresence& partyMember) = 0;
        virtual void OnRemovePartyMemberFailed(const RtError& error) = 0;
    };
    using NakamaPartyNotificationBus = AZ::EBus<NakamaPartyNotifications>;
    class NakamaPartyNotificationHandler
        : public NakamaPartyNotificationBus::Handler
        , public AZ::BehaviorEBusHandler {
    public:
        AZ_EBUS_BEHAVIOR_BINDER(
            NakamaPartyNotificationHandler,
            "{2E8ACED1-A2A2-4DC2-92A0-5AE1DCD72C05}",
            AZ::SystemAllocator, OnFollowUsersSuccess, OnFollowUsersFailed, OnUnfollowUsersSuccess, OnUnfollowUsersFailed, OnUpdateStatusSuccess, OnUpdateStatusFailed, OnAcceptPartyMemberSuccess, OnAcceptPartyMemberFailed, OnAddMatchmakerPartySuccess, OnAddMatchmakerPartyFailed, OnClosePartySuccess, OnClosePartyFailed, OnCreatePartySuccess, OnCreatePartyFailed, OnJoinPartySuccess, OnJoinPartyFailed, OnLeavePartySuccess, OnLeavePartyFailed, OnListPartyJoinRequestsSuccess, OnListPartyJoinRequestsFailed, OnPromotePartyMemberSuccess, OnPromotePartyMemberFailed, OnRemoveMatchmakerPartySuccess, OnRemoveMatchmakerPartyFailed, OnRemovePartyMemberSuccess, OnRemovePartyMemberFailed);

        void OnFollowUsersSuccess(const AZStd::vector<UserPresence>& presences) override
        {
            Call(FN_OnFollowUsersSuccess, presences);
        }
        void OnFollowUsersFailed(const RtError& error) override
        {
            Call(FN_OnFollowUsersFailed, error);
        }
		void OnUnfollowUsersSuccess(const AZStd::vector<AZStd::string>& userIds) override
		{
			Call(FN_OnUnfollowUsersSuccess, userIds);
		}
		void OnUnfollowUsersFailed(const RtError& error) override
		{
			Call(FN_OnUnfollowUsersFailed, error);
		}
		void OnUpdateStatusSuccess(const AZStd::string& status) override
		{
			Call(FN_OnUpdateStatusSuccess, status);
		}
		void OnUpdateStatusFailed(const RtError& error) override
		{
			Call(FN_OnUpdateStatusFailed, error);
		}
		void OnAcceptPartyMemberSuccess(const AZStd::string& partyId, const UserPresence& presence) override
		{
			Call(FN_OnAcceptPartyMemberSuccess, partyId, presence);
		}
		void OnAcceptPartyMemberFailed(const RtError& error) override
		{
			Call(FN_OnAcceptPartyMemberFailed, error);
		}
		void OnAddMatchmakerPartySuccess(const PartyMatchmakerTicket& ticket) override
		{
			Call(FN_OnAddMatchmakerPartySuccess, ticket);
		}
		void OnAddMatchmakerPartyFailed(const RtError& error) override
		{
			Call(FN_OnAddMatchmakerPartyFailed, error);
		}
		void OnClosePartySuccess(const AZStd::string& partyId) override
		{
			Call(FN_OnClosePartySuccess, partyId);
		}
		void OnClosePartyFailed(const RtError& error) override
		{
			Call(FN_OnClosePartyFailed, error);
		}
		void OnCreatePartySuccess(const Party& party) override
		{
			Call(FN_OnCreatePartySuccess, party);
		}
		void OnCreatePartyFailed(const RtError& error) override
		{
			Call(FN_OnCreatePartyFailed, error);
		}
		void OnJoinPartySuccess(const AZStd::string& partyId) override
		{
			Call(FN_OnJoinPartySuccess, partyId);
		}
		void OnJoinPartyFailed(const RtError& error) override
		{
			Call(FN_OnJoinPartyFailed, error);
		}
		void OnLeavePartySuccess(const AZStd::string& partyId) override
		{
			Call(FN_OnLeavePartySuccess, partyId);
		}   
		void OnLeavePartyFailed(const RtError& error) override
		{
			Call(FN_OnLeavePartyFailed, error);
		}
		void OnListPartyJoinRequestsSuccess(const PartyJoinRequest& request) override
		{
			Call(FN_OnListPartyJoinRequestsSuccess, request);
		}
		void OnListPartyJoinRequestsFailed(const RtError& error) override
		{
			Call(FN_OnListPartyJoinRequestsFailed, error);
		}
		void OnPromotePartyMemberSuccess(const AZStd::string& partyId, const UserPresence& partyMember) override
		{
			Call(FN_OnPromotePartyMemberSuccess, partyId, partyMember);
		}
		void OnPromotePartyMemberFailed(const RtError& error) override
		{
			Call(FN_OnPromotePartyMemberFailed, error);
		}
		void OnRemoveMatchmakerPartySuccess(const AZStd::string& partyId, const AZStd::string& ticket) override
		{
			Call(FN_OnRemoveMatchmakerPartySuccess, partyId, ticket);
		}
		void OnRemoveMatchmakerPartyFailed(const RtError& error) override
		{
			Call(FN_OnRemoveMatchmakerPartyFailed, error);
		}
		void OnRemovePartyMemberSuccess(const AZStd::string& partyId, const UserPresence& partyMember) override
		{
			Call(FN_OnRemovePartyMemberSuccess, partyId, partyMember);
		}
		void OnRemovePartyMemberFailed(const RtError& error) override
		{
			Call(FN_OnRemovePartyMemberFailed, error);
		}
    };
} // namespace NakamaClientGem
